
; --- 1. 定义中断向量表 (Vector Table) ---
    AREA    RESET, DATA, READONLY
    EXPORT  __Vectors

__Vectors
    DCD     0x20001000          ; [0] 栈顶地址 (SP)
    DCD     Reset_Handler       ; [1] 复位向量 (Reset Handler)
    DCD     0                   ; [2] NMI
    DCD     0                   ; [3] HardFault
    DCD     0                   ; [4] MemManage
    DCD     0                   ; [5] BusFault
    DCD     0                   ; [6] UsageFault
    DCD     0,0,0,0             ; [7-10] Reserved
    DCD     SVC_Handler         ; [11] SVCall (我们要演示的中断/异常)
    ; ... 其他中断可以在这里继续添加

; --- 2. 定义代码段 ---
    AREA    |.text|, CODE, READONLY
    THUMB                       ; 强制使用 Thumb 指令集 (Cortex-M 必须)
    ENTRY
    EXPORT  Reset_Handler

; ===========================================================
Reset_Handler
    ; 1. 初始化寄存器
    MOV     R0, #10
    MOV     R1, #20
    
    ; 2. 触发中断 (模拟中断进入)
    SVC     #0x01               ; <--- 触发中断！

    ; 3. 中断返回后会继续执行这里
    ADD     R0, R0, R1          ; R0 = 10 + 20 = 30
    
Stop
    B       Stop                ; 死循环

; ===========================================================
SVC_Handler PROC
    EXPORT  SVC_Handler
    
    ; --- [步骤1: 中断进入] ---
    PUSH    {R4, LR}            ; 虽然这里 LR 是特殊值，但也建议保存以保持栈平衡

    ; --- [步骤2: 中断处理] ---
    ADD     R4, SP, #8
    LDR     R0, [R4]
    ADD     R0, R0, #100        ; 修改 R0
    STR     R0, [R4]
    ; --- [步骤3: 中断返回] ---
    POP     {LR}            ; 恢复手动保存的寄存器

    BX      LR                  
    
    ENDP

    END
