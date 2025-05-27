#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define MAX_CHILD 200

int main(int argc, char *argv[]){
    if (argc < 2) {
        fprintf(stderr, "Please insert Parent PID\n");
        return 1;
    }

    int parentPID = atoi(argv[1]);    // 인자를 정수형으로 변환하여 부모 PID로 사용.
    int processPids[MAX_CHILD], processCnt = 0;
    processPids[processCnt++] = parentPID;     // 부모 프로세스도 검사 대상에 포함.

    // 부모 PID의 자식 프로세스 목록을 가져오기 위한 ps 명령어 문자열 생성.
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "ps --no-headers -o pid --ppid %d", parentPID);

    FILE *fp = popen(cmd, "r");   // 위 명령어를 실행하여 자식 PID 목록을 읽어옴.
    if (!fp) {
        perror("popen");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        int pid = atoi(line);  // 문자열을 정수 PID로 변환.
        if (pid > 0 && processCnt < MAX_CHILD) {
            processPids[processCnt++] = pid;  // 유효한 PID이면 배열에 추가.
        }
    }
    pclose(fp);

    // confession.txt 파일 삭제 (초기화)
    remove("confession.txt");

    // 모든 대상 프로세스들에게 SIGUSR1 전송
    for (int i = 0; i < processCnt; i++) {
        kill(processPids[i], SIGUSR1);
        usleep(300000);  // 파일에 기록할 시간 확보 
    }

    // 모든 프로세스가 기록을 완료할 시간을 추가로 대기
    sleep(1);

    // confession.txt를 읽어서 결과를 분석
    FILE *cf = fopen("confession.txt", "r");
    if (!cf) {
        perror("fopen confession.txt");
        return 1;
    }

    // 각 줄은 해당 프로세스가 기록한 것으로 추리
    char *res[MAX_CHILD];
    int resCnt = 0;
    while (resCnt < processCnt && fgets(line, sizeof(line), cf)) {
        int len = strlen(line);
        if (len > 0 && line[len-1] == '\n')
            line[len-1] = '\0';
        res[resCnt++] = strdup(line);
    }
    fclose(cf);

    // "!!!"가 기록된 경우 마피아 프로세스로 간주
    int mafiaCnt = 0, mafiaPids[MAX_CHILD];
    for (int i = 0; i < resCnt; i++) {
        if (strcmp(res[i], "!!!") == 0) {
            mafiaPids[mafiaCnt++] = processPids[i];
        }
        free(res[i]);
    }

    // 최종 결과 출력
    printf("mafia = %d\n", mafiaCnt);
    printf("citizen = %d\n", processCnt - mafiaCnt);
    printf("=== mafia list ===\n\n");
    for (int i = 0; i < mafiaCnt; i++) {
        printf("%d\n", mafiaPids[i]);
    }

    return 0;
}
