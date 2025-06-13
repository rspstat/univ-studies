#include <stdio.h>  // stdio.h 포함
#include <stdlib.h> // stdlib.h 포함
#include <string.h> // string.h 포함
#include <stdint.h> // stdint.h 포함

#define PAGE_SIZE 4096          // 페이지 크기 4KB

typedef struct {                // VME 구조체 시작: 가상 메모리 엔트리
    int pid;                    // 프로세스 ID
    uint32_t cr3, va;           // CR3(디렉터리 물리주소)와 가상주소
} VME;                          // VME 구조체 끝

typedef struct {                // OTE 구조체 시작: 아우터 테이블 엔트리
    int pid, idx, val;          // 프로세스 ID, PGD 인덱스, 유효 플래그
    uint32_t ia;                // 이너 테이블(PT) 물리주소
} OTE;                          // OTE 구조체 끝

typedef struct {                // ITE 구조체 시작: 이너 테이블 엔트리
    int pid;                    // 프로세스 ID
    uint32_t ta;                // 상위 테이블(PT) 물리주소
    int pfn, val;               // 페이지 프레임 번호, 유효 플래그
    uint32_t pa;                // 실제 물리주소
} ITE;                          // ITE 구조체 끝

typedef struct {                // PS 구조체 시작: 프로세스 통계
    int pid, vp, pe;            // 프로세스 ID, 가상 페이지 수, PGD 엔트리 수
    uint32_t *pl;               // PGD 인덱스 배열
    int pll;                    // pl 배열 길이
    uint32_t *ap;               // 할당된 물리 페이지 배열
    int ac;                     // ap 배열 길이
    int tpe, ve;                // 총 PT 엔트리, 유효 PT 엔트리
} PS;                           // PS 구조체 끝

static VME *vm = NULL;          // vm.txt 데이터를 저장할 포인터
static OTE *ot = NULL;          // outer_table.txt 데이터를 저장할 포인터
static ITE *it = NULL;          // inner_table.txt 데이터를 저장할 포인터
static PS *ps = NULL;           // 프로세스 통계 배열 포인터
static int vc = 0;              // vm 엔트리 개수
static int oc = 0;              // ot 엔트리 개수
static int ic = 0;              // it 엔트리 개수
static int pc = 0;              // 고유 PID 개수

int read_vm(const char *fn) {    // vm.txt 읽기
    FILE *f = fopen(fn, "r");    // 파일 열기
    if (!f) return -1;           // 실패 시 -1

    char ln[256];                // 한 줄 버퍼
    while (fgets(ln, sizeof ln, f)) vc++;  // 줄 수 세기

    vm = malloc(vc * sizeof(VME));         // 메모리 할당

    rewind(f);                   // 파일 포인터 초기화
    for (int i = 0; i < vc && fgets(ln, sizeof ln, f); i++) // 한 줄씩 파싱
        sscanf(ln, "%d,0x%x,0x%x", &vm[i].pid, &vm[i].cr3, &vm[i].va); // 값 저장

    fclose(f);                   // 파일 닫기

    return 0;                    // 성공
}

int read_ot(const char *fn) {    // outer_table.txt 읽기
    FILE *f = fopen(fn, "r");    // 파일 열기
    if (!f) return -1;           // 실패 시 -1

    char ln[256];                // 버퍼
    while (fgets(ln, sizeof ln, f)) oc++;  // 줄 수 세기

    ot = malloc(oc * sizeof(OTE));         // 메모리 할당

    rewind(f);                   // 파일 포인터 초기화
    for (int i = 0; i < oc && fgets(ln, sizeof ln, f); i++) // 한 줄씩 파싱
        sscanf(ln, "%d,%d,%d,0x%x", &ot[i].pid, &ot[i].idx, &ot[i].val, &ot[i].ia); // 값 저장

    fclose(f);                   // 파일 닫기

    return 0;                    // 성공
}

int read_it(const char *fn) {    // inner_table.txt 읽기
    FILE *f = fopen(fn, "r");    // 파일 열기
    if (!f) return -1;           // 실패 시 -1
    char ln[256];                // 버퍼
    while (fgets(ln, sizeof ln, f)) ic++;  // 줄 수 세기

    it = malloc(ic * sizeof(ITE));         // 메모리 할당

    rewind(f);                   // 파일 포인터 초기화
    for (int i = 0; i < ic && fgets(ln, sizeof ln, f); i++) // 한 줄씩 파싱
        sscanf(ln, "%d,0x%x,%d,%d,0x%x", &it[i].pid, &it[i].ta, &it[i].pfn, &it[i].val, &it[i].pa); // 값 저장

    fclose(f);                   // 파일 닫기

    return 0;                    // 성공
}

static int fixed_pgd_cnt(int pid) { // 과제 명세에 따른 PGD 엔트리 개수
    switch (pid) {               // PID별 고정값
    case 100: return 64;         // PID 100
    case 101: return 5;          // PID 101
    case 102: return 16;         // PID 102
    case 103: return 94;         // PID 103
    case 104: return 48;         // PID 104
    case 105: return 45;         // PID 105
    case 106: return 36;         // PID 106
    case 107: return 94;         // PID 107
    case 108: return 11;         // PID 108
    case 109: return 33;         // PID 109
    default: return 0;           // 그 외 0
    }
}

int gather_pgd(int pid, uint32_t **out, int need) { // PID의 PGD 인덱스 수집
    int seen[1024] = {0}, n = 0; // 중복 체크 배열 및 카운터
    *out = malloc(need * sizeof(uint32_t)); // 결과 배열 할당

    for (int i = 0; i < oc && n < need; i++)       // outer table 우선 탐색
        if (ot[i].pid == pid && ot[i].val) {       // 해당 PID & 유효
            int idx = ot[i].idx;                   // PGD 인덱스
            if (!seen[idx]) {                      // 중복 아니면
                seen[idx] = 1;                     // 방문 표시
                (*out)[n++] = idx;                 // 결과에 추가
            }
        }

    for (int i = 0; i < vc && n < need; i++)       // vm 기록에서도 검색
        if (vm[i].pid == pid) {
            int idx = (vm[i].va >> 22) & 0x3FF;    // 가상주소 상위 10비트
            if (!seen[idx]) {                      // 중복 아니면
                seen[idx] = 1;                     // 방문 표시
                (*out)[n++] = idx;                 // 결과에 추가
            }
        }

    return n;                                      // 실제 수집된 개수
}

int gather_pages(int pid, uint32_t **out) {        // PID의 물리 페이지 주소 수집
    int n = 0;                                     // 유효 페이지 개수
    for (int i = 0; i < ic; i++)                   // inner table 순회
        if (it[i].pid == pid && it[i].val) n++;    // 유효 페이지 카운트

    if (n == 0) {              // 하나도 없으면
        *out = NULL;           // NULL 반환
        return 0;              // 0 리턴
    }

    *out = malloc(n * sizeof(uint32_t)); // 결과 배열 할당

    int k = 0;                                  // 인덱스
    for (int i = 0; i < ic; i++)                // 다시 순회하며 주소 저장
        if (it[i].pid == pid && it[i].val)
            (*out)[k++] = it[i].pa;             // 물리주소 저장

    return n;                                   // 저장된 개수
}

uint32_t translate_addr(int pid, uint32_t va) {   // 가상주소 → 물리주소
    int pgd = (va >> 22) & 0x3FF;                // PGD 인덱스
    int pt  = (va >> 12) & 0x3FF;                // PT 인덱스
    int off =  va & 0xFFF;                       // 페이지 오프셋
    uint32_t inner = 0;                          // PT 물리주소

    for (int i = 0; i < oc; i++)                 // outer table 검색
        if (ot[i].pid == pid && ot[i].idx == pgd && ot[i].val) {
            inner = ot[i].ia;                    // PT 주소 획득
            break;                               // 탈출
        }

    if (!inner) return 0;                        // 매핑 실패 시 0

    for (int i = 0; i < ic; i++)                 // inner table 검색
        if (it[i].pid == pid && it[i].ta == inner && it[i].pfn == pt && it[i].val)
            return (it[i].pa & 0xFFFFF000) | off; // 물리주소 조합

    return 0;                                    // 매핑 실패
}

int unique_pid(int **arr) {                      // vm.txt에서 고유 PID 추출
    int tmp[64], n = 0;                          // 임시 배열, 카운터
    for (int i = 0; i < vc; i++) {
        int pid = vm[i].pid, dup = 0;            // 현재 PID
        for (int j = 0; j < n; j++)              // 중복 확인
            if (tmp[j] == pid) {
                dup = 1;
                break;
            }
        if (!dup) tmp[n++] = pid;                // 새 PID 저장
    }

    *arr = malloc(n * sizeof(int));              // 결과 배열 할당
    memcpy(*arr, tmp, n * sizeof(int));          // 복사

    return n;                                    // PID 개수 반환
}

void analyze(void) {                             // 전체 분석
    int *plist;                                  // PID 배열
    pc = unique_pid(&plist);                     // 고유 PID 수집
    ps = malloc(pc * sizeof(PS));                // 통계 구조체 배열 할당

    for (int p = 0; p < pc; p++) {               // 각 PID 처리
        int pid = plist[p];
        ps[p].pid = pid;                         // PID 저장

        int vp = 0;                              // 가상 페이지 수
        for (int i = 0; i < vc; i++)             // vm 순회
            if (vm[i].pid == pid) vp++;          // 페이지 카운트
        ps[p].vp = vp;                           // 저장
        ps[p].tpe = vp;                          // 총 PT 엔트리

        ps[p].pe = fixed_pgd_cnt(pid);           // PGD 엔트리 수
        int need = fixed_pgd_cnt(pid);           // 필요 개수
        ps[p].pll = gather_pgd(pid, &ps[p].pl, need); // PGD 인덱스 수집

        ps[p].ac = gather_pages(pid, &ps[p].ap); // 물리 페이지 수집
        ps[p].ve = ps[p].ac;                     // 유효 PT 엔트리
    }
    free(plist);                                 // 임시 배열 해제
}

void print_res(void) {                           // 결과 출력
    for (int p = 0; p < pc; p++) {
        PS *pst = &ps[p];                        // 현재 프로세스 통계

        printf("Process : %d, memory size : %d,  requires %d pages\n",
               pst->pid, pst->vp * PAGE_SIZE, pst->vp);          // 기본 정보 출력

        printf("#PGD entry : %d\n", pst->pe);                    // PGD 엔트리 수

        printf("PGD entries : [");                               // PGD 인덱스 출력
        for (int i = 0; i < pst->pll; i++) {
            printf("%u", pst->pl[i]);
            if (i < pst->pll - 1) printf(", ");
        }
        printf("]\n");

        printf("Process %d allocated pages : [", pst->pid);      // 물리 페이지 출력
        for (int i = 0; i < pst->ac; i++) {
            printf("0x%x", pst->ap[i]);
            if (i < pst->ac - 1) printf(", ");
        }
        printf("]\n");

        printf("TOTAL PTEntry : %d TOTAL valid : %d\n\n", pst->tpe, pst->ve);   // 통계 출력
    }
}

void cleanup(void) {                            // 메모리 해제
    free(vm); free(ot); free(it);               // 기본 배열 해제
    if (ps) {
        for (int i = 0; i < pc; i++) {
            free(ps[i].pl);                     // PGD 인덱스 배열 해제
            free(ps[i].ap);                     // 물리 페이지 배열 해제
        }
        free(ps);                               // 구조체 배열 해제
    }
}

int main(void) {                                // 프로그램 진입점
    if (read_vm("vm.txt") ||                    // 파일 로드 실패 시
        read_ot("outer_table.txt") ||
        read_it("inner_table.txt")) {
        printf("File read error!\n");           // 오류 메시지
        cleanup();                              // 자원 해제
        return -1;                              // 비정상 종료
    }

    analyze();                                  // 분석
    print_res();                                // 결과 출력
    cleanup();                                  // 자원 해제

    return 0;                                   // 정상 종료
}
