#include <stdio.h>
#include <stdlib.h>

// 交换两个整数的函数
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 对三个数进行排序的函数
void sortThree(int *a, int *b, int *c) {
    if (*a > *b) swap(a, b);
    if (*a > *c) swap(a, c);
    if (*b > *c) swap(b, c);
}

// 计算三个数的中值
int medianOfThree(int a, int b, int c) {
    int arr[3] = {a, b, c};
    // 简单排序三个数
    if (arr[0] > arr[1]) swap(&arr[0], &arr[1]);
    if (arr[0] > arr[2]) swap(&arr[0], &arr[2]);
    if (arr[1] > arr[2]) swap(&arr[1], &arr[2]);
    return arr[1]; // 中值是排序后的中间值
}

// 计算三个数的平均值（浮点数）
float averageOfThree(int a, int b, int c) {
    return (a + b + c) / 3.0f;
}

int main() {
    // 给定的序列
    int sequence[] = {5, 8, 12, 9, 10, 3, 5, 7, 8, 10, 22, 31, 17, 16, 13};
    int length = sizeof(sequence) / sizeof(sequence[0]);
    
    printf("原始序列: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n\n");
    
    printf("滑动窗口处理结果（窗口大小1x3）:\n");
    printf("窗口位置\t窗口内容\t中值\t\t平均值\n");
    printf("------------------------------------------------------------\n");
    
    // 使用1x3的窗口滑动处理
    for (int i = 0; i < length - 2; i++) {
        int a = sequence[i];
        int b = sequence[i + 1];
        int c = sequence[i + 2];
        
        // 计算中值
        int median = medianOfThree(a, b, c);
        
        // 计算平均值
        float average = averageOfThree(a, b, c);
        
        // 输出结果
        printf("窗口[%d-%d]\t[%2d, %2d, %2d]\t中值: %2d\t平均值: %.2f\n", 
               i, i+2, a, b, c, median, average);
    }
    
    printf("\n详细处理过程:\n");
    printf("============================================================\n");
    
    // 更详细的处理过程，显示排序步骤
    for (int i = 0; i < length - 2; i++) {
        int a = sequence[i];
        int b = sequence[i + 1];
        int c = sequence[i + 2];
        
        printf("\n处理窗口 [%d, %d, %d]:\n", a, b, c);
        
        // 显示排序过程
        int sorted[3] = {a, b, c};
        printf("  排序前: [%d, %d, %d]\n", sorted[0], sorted[1], sorted[2]);
        
        // 进行排序
        if (sorted[0] > sorted[1]) swap(&sorted[0], &sorted[1]);
        if (sorted[0] > sorted[2]) swap(&sorted[0], &sorted[2]);
        if (sorted[1] > sorted[2]) swap(&sorted[1], &sorted[2]);
        
        printf("  排序后: [%d, %d, %d]\n", sorted[0], sorted[1], sorted[2]);
        printf("  中值: %d\n", sorted[1]);
        printf("  平均值: (%.0f)/3 = %.2f\n", (a+b+c)/1.0, (a+b+c)/3.0);
    }
    
    // 创建中值序列和平均值序列
    printf("\n\n处理结果序列:\n");
    printf("============================================================\n");
    
    int medianSequence[length - 2];
    float averageSequence[length - 2];
    
    printf("中值序列: [");
    for (int i = 0; i < length - 2; i++) {
        medianSequence[i] = medianOfThree(
            sequence[i], 
            sequence[i + 1], 
            sequence[i + 2]
        );
        printf("%d", medianSequence[i]);
        if (i < length - 3) printf(", ");
    }
    printf("]\n");
    
    printf("平均值序列: [");
    for (int i = 0; i < length - 2; i++) {
        averageSequence[i] = averageOfThree(
            sequence[i], 
            sequence[i + 1], 
            sequence[i + 2]
        );
        printf("%.2f", averageSequence[i]);
        if (i < length - 3) printf(", ");
    }
    printf("]\n");
    
    return 0;
}
