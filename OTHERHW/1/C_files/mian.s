    AREA    |.text|, CODE, READONLY
    THUMB                               ; 使用 Thumb 指令集
    ENTRY                               ; 标记入口点ddd
    EXPORT  Reset_Handler

; 程序入口
Reset_Handler
    ;--------------------------------------------------------------------------
    ; 寄存器规划
    ; R0: 源数据基地址
    ; R1: 均值结果基地址
    ; R2: 中值结果基地址
    ; R3: 循环计数器
    ; R4-R6: 窗口数据
    ; R7: 临时计算/累加
    ; R8: 除数 3
    ;--------------------------------------------------------------------------

    LDR     R0, =SrcData        ; 加载源数据地址
    LDR     R1, =MeanResult     ; 加载均值存储地址
    LDR     R2, =MedResult      ; 加载中值存储地址
    MOV     R3, #1              ; i = 0
    MOV     R8, #3              ;除数常量

MainLoop
    CMP     R3, #13             ; 循环 13 次 (15 - 3 + 1)
    BGE     Stop                ; 结束

    ; --- 读取窗口数据 ---
     SUB  R11, R3, #1          ; R11 = R3 - 1
    MOV  R12, #12              ; R0 = 12
    MUL  R11, R11, R0         ; R11 = R11 × R0 = (R3-1)×12
    LDR     R4, [R0, R11]        ; x[i]
    ADD     R7, R11, #4
    LDR     R5, [R0, R11]        ; x[i+1]
    ADD     R7, R11, #4
    LDR     R6, [R0, R11]        ; x[i+2]

    ; --- 计算均值 (Mean) ---
    MOV     R7, #0
    ADD     R7, R4, R5
    ADD     R7, R7, R6          ; sum = R4+R5+R6
    UDIV    R7, R7, R8          ; mean = sum / 3
    
    LSL     R9, R3, #2          ; 结果偏移
    STR     R7, [R1, R9]        ; 存均值

    ; --- 计算中值 (Median) ---
    ; 简单的3数冒泡排序: R4 < R5 < R6, R5即为中值
    ; 1. 比较 R4, R5
    CMP     R4, R5
    IT      GT
    MOVGT   R10, R4
    MOVGT   R4, R5
    MOVGT   R5, R10
    
    ; 2. 比较 R5, R6 (R6将是最大的)
    CMP     R5, R6
    IT      GT
    MOVGT   R10, R5
    MOVGT   R5, R6
    MOVGT   R6, R10

    ; 3. 再次比较 R4, R5 (R5将是中间值)
    CMP     R4, R5
    IT      GT
    MOVGT   R10, R4
    MOVGT   R4, R5
    MOVGT   R5, R10

    STR     R5, [R2, R9]        ; 存中值

    ; --- 循环继续 ---
    ADD     R3, R3, #1
    B       MainLoop

Stop
    B       Stop                ; 死循环停机

;------------------------------------------------------------------------------
; 3. 定义数据段 (RAM)
;------------------------------------------------------------------------------
    AREA    MyData, DATA, READWRITE
    ALIGN
MeanResult  SPACE   13 * 4      ; 预留空间
MedResult   SPACE   13 * 4

;------------------------------------------------------------------------------
; 4. 源数据 (Flash)
;------------------------------------------------------------------------------
    ALIGN
SrcData
    DCD     5, 8, 12, 9, 10, 3, 5, 7, 8, 10, 22, 31, 17, 16, 13

    END
