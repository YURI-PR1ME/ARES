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
    ; Cortex-M 中最简单的测试中断是 "SVC" (系统调用)
    ; 执行这条指令后，CPU 会自动保存现场并跳转到 SVC_Handler
    SVC     #0x01               ; <--- 触发中断！

    ; 3. 中断返回后会继续执行这里
    ADD     R0, R0, R1          ; R0 = 10 + 20 = 30
    
Stop
    B       Stop                ; 死循环

; ===========================================================
; 中断服务程序 (SVC_Handler)
; 对应题目的：中断进入(硬件自动)、处理、返回
; ===========================================================
SVC_Handler PROC
    EXPORT  SVC_Handler
    
    ; --- [步骤1: 中断进入] ---
    ; 你不需要写代码！Cortex-M 硬件已经自动完成了以下操作：
    ; 1. 自动压栈 (Push): R0, R1, R2, R3, R12, LR, PC, xPSR
    ; 2. 更新 SP 指针
    ; 3. LR 寄存器被自动赋值为一个特殊值 (如 0xFFFFFFF9)
    
    ; 如果你需要使用 R4-R11，需要手动保存 (Cortex-M 规范)
    PUSH    {R4, LR}            ; 虽然这里 LR 是特殊值，但也建议保存以保持栈平衡

    ; --- [步骤2: 中断处理] ---
    ; 在这里写你的处理逻辑
    ; 例如：将 R0 增加 100 (注意：这里的 R0 是寄存器中的，不是栈里的)
    ; 实际应用中，我们通常修改内存或外设
    ADD     R4, SP, #8
    LDR     R0, [R4]
    ADD     R0, R0, #100        ; 修改 R0
    STR     R0, [R4]
    ; --- [步骤3: 中断返回] ---
    POP     {LR}            ; 恢复手动保存的寄存器

    ; 关键指令！
    ; 因为 LR 此时是一个特殊值 (EXC_RETURN)，
    ; CPU 执行 BX LR 时，不会跳转到 0xFFFFFFF9，
    ; 而是触发硬件 "Unstacking" 流程：
    ; 1. 自动从栈中恢复 R0-R3, PC, xPSR 等
    ; 2. 切换回用户模式/线程模式
    BX      LR                  
    
    ENDP

    END
