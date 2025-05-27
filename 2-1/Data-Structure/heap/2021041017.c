// gcc 8.1.0 환경
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10000     // Heap의 최대 원소 개수, 사이즈 수정 가능합니다.
#define HEAP_FULL(n) (n == MAX_SIZE - 1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
    int key;
} element;

element heap[MAX_SIZE];
int heap_size = 0;

void push(element item, int *n);
element pop(int *n);

int main() {
    // 경로 수정 가능합니다.
    const char *filePath = "C:\\Users\\win11\\Desktop\\data\\vsc\\univ\\heap\\test.txt";
    FILE *file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "파일 열기에 실패하였습니다.\n");
        return 1;
    }

    int num;
    element item;

    while (fscanf(file, "%d", &num) != EOF) {
        item.key = num;
        push(item, &heap_size);
    }

    fclose(file);

    while (!HEAP_EMPTY(heap_size)) {
        element max_item = pop(&heap_size);
        printf("%d\n", max_item.key);
    }

    return 0;
}

// 최대 힙에서의 삽입
void push(element item, int *n) {
    int i;

    if (HEAP_FULL(*n)) {
        fprintf(stderr, "The heap is full.\n");
        exit(EXIT_FAILURE);
    }

    i = ++(*n);

    while ((i != 1) && (item.key > heap[i / 2].key)) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = item;
}

// 최대 힙에서의 삭제
element pop(int *n) {
    int parent, child;
    element item, tmp;
    if (HEAP_EMPTY(*n)) {
        fprintf(stderr, "The heap is empty.\n");
        exit(EXIT_FAILURE);
    }

    item = heap[1];
    tmp = heap[(*n)--];
    parent = 1;
    child = 2;

    while (child <= *n) {
        if ((child < *n) && (heap[child].key < heap[child + 1].key))
            child++;        // 오른쪽 자식 노드가 더 큰 경우 

        if (tmp.key >= heap[child].key)
            break;

        heap[parent] = heap[child];
        parent = child;
        child *= 2;         // 다음 레벨의 왼쪽 자식 노드 
    }

    heap[parent] = tmp;
    return item;
}
