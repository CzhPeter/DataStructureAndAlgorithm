#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct vector {
    int size, count;
    int *data;
} vector;

vector* get_new_vector(int n) {
    vector* p = (vector*)malloc(sizeof(vector));
    p->size = n;
    p->count = 0;
    p->data = (int*)malloc(sizeof(int) * n);
    return p;
}

// 扩容操作
int expand(vector* v) {
    if (v == NULL) return 0;
    printf("expand v from %d to %d\n", v->size, v->size * 2);
    // realloc()机制：
    // 1、向后扩展
    // 2、如果向后扩展失败，则找一片新内存，将原数据拷贝到新内存中，销毁原内存
    // 3、新内存也找不到，扩容失败，返回 NULL 并覆盖掉原来的内存
    int* p = (int*)realloc(v->data, sizeof(int) * v->size * 2);
    if (p == NULL) return 0;
    v->data = p;
    v->size *= 2;
    return 1;
}

int insert(vector* v, int pos, int val) {
    if (pos < 0 || pos > v->count) return 0;
    if (v->size == v->count && !expand(v)) return 0;
    // 逆序遍历，将pos位置及之后的元素向后移动一位
    for (int i = v->count - 1; i >= pos; --i) {
        v->data[i + 1] = v->data[i];
    }
    // 插入新元素
    v->data[pos] = val;
    v->count += 1;
    return 1;
}

int erase(vector* v, int pos) {
    if (pos < 0 || pos >= v->count) return 0;
    // 从pos + 1处开始遍历，将pos位置及之后的元素向前移动一位
    for (int i = pos + 1; i < v->count; ++i) {
        v->data[i - 1] = v->data[i];
    }
    v->count -= 1;
    return 1;
}

void clear(vector* v) {
    if (v == NULL) return;
    free(v->data);
    free(v);
    return;
}

void output_vector(vector* v) {
    int len = 0;
    for (int i = 0; i < v->size; ++i) {
        len += printf("%3d", i);
    }
    printf("\n");
    for (int i = 0; i < len; ++i) {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < v->count; ++i) {
        printf("%3d", v->data[i]);
    }
    printf("\n\n\n");
    return;
}

int main () {
    srand(time(0));
    vector* v = get_new_vector(2);
    for (int i = 0; i < 20; ++i) {
        int op = rand() % 4;
        int pos, val, ret;
        switch (op) {
            case 0:
            case 1:
            case 2:
                pos = rand() % (v->count + 2);
                val = rand() % 100;
                ret = insert(v, pos, val);
                printf("insert %d at %d to vector = %d\n", 
                       val, pos, ret);
                break;
            case 3:
                pos = rand() % (v->count + 2);
                ret = erase(v, pos);
                printf("erase %d at %d from vector = %d\n", 
                       v->data[pos], pos, ret);
                break;
        }
        output_vector(v);
    }
    clear(v);
    return 0;
}