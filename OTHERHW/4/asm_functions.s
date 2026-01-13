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
    
; 声明要调用的C函数
    IMPORT  modify_r7_in_c      ; 声明C函数

; ===========================================================
Reset_Handler
    ; 1. 初始化寄存器
    MOV     R0, #10
    MOV     R1, #20
    MOV     R7, #50             ; 初始化 R7 = 50
    
    ; 2. 触发中断 (模拟中断进入)
    SVC     #0x01               ; <--- 触发中断！

    ; 3. 中断返回后会继续执行这里
    ; 此时 R7 应该已经被 C 函数修改过了
    ADD     R0, R0, R1          ; R0 = 10 + 20 = 30
    ; 我们可以使用修改后的 R7
    ADD     R0, R0, R7          ; R0 = 30 + R7 (被C函数修改后的值)
    
Stop
    B       Stop                ; 死循环

; ===========================================================
; 中断服务程序 (SVC_Handler)
; 现在调用C函数处理，然后返回汇编
; ===========================================================
SVC_Handler PROC
    EXPORT  SVC_Handler
    
    ; --- [步骤1: 中断进入] ---
    ; 硬件已经自动保存了现场
    ; 我们需要手动保存可能被C函数破坏的寄存器
    ; 根据AAPCS调用约定，R4-R11需要被调用者保存
    PUSH    {R4-R7, LR}         ; 保存寄存器，包括LR(EXC_RETURN)
    
    ; --- [步骤2: 调用C函数处理] ---
    ; 准备参数（如果需要）
    ; 这里我们直接将当前R7的值作为参数传递给C函数
    MOV     R0, R7              ; 参数1：当前R7的值
    
    ; 调用C函数
    BL      modify_r7_in_c      ; 调用C函数，返回值在R0中
    
    ; 将C函数的返回值赋给R7
    MOV     R7, R0              ; 更新R7为C函数返回的值
    
    ; --- [步骤3: 中断返回] ---
    ; 恢复保存的寄存器
    POP     {R4-R6, LR}         ; 恢复寄存器，包括LR(EXC_RETURN)
    
    ; 关键指令：返回中断前的程序
    ; LR中包含特殊的EXC_RETURN值
    BX      LR                  ; 触发硬件中断返回流程
    
    ENDP

    END
