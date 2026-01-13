;============================================================================
; 修复版：加入了 RESET 向量表，解决 L6236E 报错
;============================================================================

; --- 1. 定义中断向量表 (Vector Table) ---
; 链接器必须找到名为 "RESET" 的段，并把它放在内存最开始的地方
    AREA    RESET, DATA, READONLY
    EXPORT  __Vectors

__Vectors
    DCD     0x20001000          ; 栈顶地址 (Initial Stack Pointer) - 随便给一个RAM地址即可
    DCD     __main              ; 复位向量 (Reset Vector) - 程序启动后跳转到 __main
    ; (这里省略了其他中断向量，对于练习足够了)

; --- 2. 定义数据段 ---
    AREA    MyData, DATA, READONLY
Array   DCD     5, 8, 12, 9, 10, 3, 5, 7, 8, 10, 22, 31, 17, 16, 13
ArrayEnd

; --- 3. 定义代码段 ---
    AREA    |.text|, CODE, READONLY
    ENTRY                           ; 标记程序入口
    EXPORT  __main

__main
    ; -----------------------------------------------------------
    ; 初始化
    ; -----------------------------------------------------------
    LDR     R0, =Array              ; R0 = 数组的首地址
    MOV     R1, #13                 ; R1 = 循环次数 (15 - 3 + 1)
    MOV     R8, #3
    MOV     R7, #0

    ; -----------------------------------------------------------
    ; 滑动窗口循环
    ; R9 为均值
    ; R10 为中值
    ; -----------------------------------------------------------
Loop_Window
    CMP     R1, #0                  ; 检查计数器
    BEQ     Stop                    ; 结束

    ; --- 加载窗口数据 ---
    LDR     R4, [R0, #0]            ; 第1个数
    LDR     R5, [R0, #4]            ; 第2个数
    LDR     R6, [R0, #8]            ; 第3个数

    ; --- 计算均值 (Mean) ---
    MOV     R7, #0
    ADD     R7, R4, R5
    ADD     R7, R7, R6          ; sum = R4+R5+R6
    UDIV    R7, R7, R8          ; mean = sum / 3
    MOV     R9, R7
 ; ============================================
bubble_sort_asc
    ; 使用R11作为临时寄存器
    
    ; 第一轮比较：确保R6是最大的
    CMP     R4, R5          ; 比较R4和R5
    BLE     compare1_ok     ; 如果R4 <= R5，跳过交换
    ; 交换R4和R5
    MOV     R11, R4
    MOV     R4, R5
    MOV     R5, R11
compare1_ok
    
    CMP     R5, R6          ; 比较R5和R6
    BLE     compare2_ok     ; 如果R5 <= R6，跳过交换
    ; 交换R5和R6
    MOV     R11, R5
    MOV     R5, R6
    MOV     R6, R11
compare2_ok
    
    ; 第二轮比较：确保R5是第二大的
    CMP     R4, R5          ; 再次比较R4和R5
    BLE     compare3_ok     ; 如果R4 <= R5，跳过交换
    ; 交换R4和R5
    MOV     R11, R4
    MOV     R4, R5
    MOV     R5, R11
compare3_ok  
    MOV     R10, R5
; --- 滑动 ---
    ADD     R0, R0, #4              ; 指针后移4字节
    SUB     R1, R1, #1              ; 计数器-1
    B       Loop_Window

Stop
    B       Stop                    ; 死循环

    END
