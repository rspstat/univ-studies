//gcc, g++ 모두 구동 가능하도록 하였습니다. (gcc 8.1.0 기준) 
//maze.txt 파일의 미로에서 끝 행 + 1에 줄바꿈이 없는지 확인부탁드리겠습니다...! 없는것이 좋습니다!
//소프트웨어학과 2021041017 김규현 항상 감사합니다.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

typedef struct {
    int vert;   //수직 
    int horiz;  //수평 
} offsets;

//방향의 우선순위는 최대한 예시로 주신거랑 비슷하게 하였습니다.
offsets move[8] = {{0, 1}, {1, 0}, {1, 1}, {-1, 1}, {-1, 0}, {1, -1}, {0, -1}, {-1, -1}}; 

typedef struct {
    int row;    //행
    int col;    //열
    int dir;    //방향
} element;

element stack[MAX_SIZE * MAX_SIZE];
int top = -1;

void push(element item) {       
    if (top < MAX_SIZE * MAX_SIZE - 1) 
        stack[++top] = item;        //스택에 요소 추가, -1이어서 ++top 사용
}

element pop() {
    if (top > -1)
        return stack[top--];        //스택이 비어있지 않다면 top에 있는 요소를 반환, 및 top 감소
    
    return (element){-1, -1, -1};   //스택이 빌 경우 => -1 반환
}

void path(int rows, int cols, int **maze, int **mark) {    
    element pos = {0, 0, 0};                            //시작 위치 및 방향
    push(pos);

    mark[0][0] = 0;                                     //시작점 경로

    while (top != -1) {
        pos = pop();                                    //스택에서 꺼낸 요소
        int row = pos.row;
        int col = pos.col;
        int dir = pos.dir;

        if (row == rows - 1 && col == cols - 1) {       //n,m의 출구에 도달하면 종료
            mark[row][col] = 0;
            break;
        }

        if (dir < 8) {
            int next_row = row + move[dir].vert;
            int next_col = col + move[dir].horiz;
            if (next_row >= 0 && next_row < rows && next_col >= 0 && next_col < cols && maze[next_row][next_col] == 0 && mark[next_row][next_col] == 1) {
                mark[next_row][next_col] = 0;           //방문한 곳은 0으로 길을 표시
                element next_pos = {next_row, next_col, 0};
                push((element){row, col, dir + 1});     //현재 위치를 다시 스택에 추가
                push(next_pos);                         //다음 위치 추가
            } 
            else 
                push((element){row, col, dir + 1});     //다음 방향을 위해 다시 스택에 추가
        }
    }

    printf("\n<<<SOLUTION>>>\n");                       //최종 미로 출력
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < cols - 1; j++) 
            printf("%d", mark[i][j]); 
        
        printf("\n");
    }
}

int main() {
    FILE *file = fopen("maze.txt", "r");  
    if (!file) {        //파일을 열 수 없을 경우
        printf("can't open maze.txt file. maze.txt 파일을 열 수 없습니다.\n");
        return 1;
    }

    int rows = 0, cols = 0, ch;

    ch = fgetc(file);
    while (ch != EOF) {
        if (ch == '\n') 
            rows++;
        else if (rows == 0 && ch != '\r') 
            cols++;
        ch = fgetc(file);
    }

    if (cols > 0 && ch != '\n')
        rows++;

    rewind(file);

    int **maze = (int **)malloc(rows * sizeof(int *));  //2차원 maze 배열 동적할당 (gcc, g++ 둘 다 가능)
    int **mark = (int **)malloc(rows * sizeof(int *));  //2차원 mark 배열 동적할당 (gcc, g++ 둘 다 가능)

    for (int i = 0; i < rows; i++) {
        maze[i] = (int *)malloc(cols * sizeof(int));
        mark[i] = (int *)malloc(cols * sizeof(int));

        for (int j = 0; j < cols; j++) {
            fscanf(file, "%1d", &maze[i][j]);           //maze 2차원 배열에 maze.txt 파일의 미로를 대입
            mark[i][j] = 1;                             //mark 2차원 배열을 전부 1로 대입 (maze 배열 아닙니다!!)
        }
    }

    fclose(file);                                       //파일을 닫음

    printf("<<<INPUT MAZE>>>\n");
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < cols; j++) 
            printf("%d", maze[i][j]);                   //maze.txt 미로 출력
        
        printf("\n");
    }

    path(rows, cols, maze, mark);                       //path 미로 함수 실행

    for (int i = 0; i < rows; i++) {
        free(maze[i]);
        free(mark[i]);
    }

    free(maze);                                         
    free(mark);                                         //maze, mark 동적할당 해제

    return 0;
}
