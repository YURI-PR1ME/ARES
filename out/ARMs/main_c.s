//===========================================================================
    // ???: SlidingWindow.s
    // ???: ARM Compiler 6 (Clang)
    // ??: ARM Cortex-M3
    //===========================================================================

    .syntax unified          // ??:???????? (Thumb-2)
    .cpu cortex-m3           // ?????
    .thumb                   // ?? Thumb ???

    //---------------------------------------------------------------------------
    // ??? (Data Section)
    //---------------------------------------------------------------------------
    .data
    .align 4                 // 4????

SrcData:
    .word 5, 8, 12, 9, 10, 3, 5, 7, 8, 10, 22, 31, 17, 16, 13
    
MeanRes:
    .zero 48                 // ?? 12??? * 4?? = 48??,??
MedRes:
    .zero 48                 // ?? 48??,??

    //---------------------------------------------------------------------------
    // ??? (Code Section)
    //---------------------------------------------------------------------------
    .text
    .global Reset_Handler           // ????,?????????
    .type Reset_Handler, %function

Reset_Handler:
    // --- ?????? ---
    LDR     R0, =SrcData     // R0 ?????
    LDR     R1, =MeanRes     // R1 ???????
    LDR     R2, =MedRes      // R2 ??????
    MOV     R3, #12          // R3 ????? (15-4+1=12)

Loop_Start:
    // --- 1. ??????? 4 ?? ---
    LDR     R4, [R0, #0]     // ?1??
    LDR     R5, [R0, #4]     // ?2??
    LDR     R6, [R0, #8]     // ?3??
    LDR     R7, [R0, #12]    // ?4??

    // --- 2. ????? (Mean) ---
    // ??: (a + b + c + d) / 4
    MOV     R8, R4
    ADD     R8, R8, R5
    ADD     R8, R8, R6
    ADD     R8, R8, R7       // ??
    LSR     R8, R8, #2       // ??2? (??4)
    STR     R8, [R1], #4     // ????,R1??????

    // --- 3. ???? (Median) ---
    // ????? R4, R5, R6, R7 ??,??? (R5+R6)/2
    // ?????????

    // ?1???:??????? R7
    CMP     R4, R5           // ?? R4, R5
    ITTT    GT               // ?? R4 > R5 (??:????3?T,????3???)
    MOVGT   R9, R4           // ????
    MOVGT   R4, R5
    MOVGT   R5, R9           // ????
    
    CMP     R5, R6           // ?? R5, R6
    ITTT    GT               // ?? R5 > R6
    MOVGT   R9, R5
    MOVGT   R5, R6
    MOVGT   R6, R9
    
    CMP     R6, R7           // ?? R6, R7
    ITTT    GT               // ?? R6 > R7
    MOVGT   R9, R6
    MOVGT   R6, R7
    MOVGT   R7, R9

    // ?2???:??2????? R6
    CMP     R4, R5
    ITTT    GT
    MOVGT   R9, R4
    MOVGT   R4, R5
    MOVGT   R5, R9
    
    CMP     R5, R6
    ITTT    GT
    MOVGT   R9, R5
    MOVGT   R5, R6
    MOVGT   R6, R9

    // ?3???:?????
    CMP     R4, R5
    ITTT    GT
    MOVGT   R9, R4
    MOVGT   R4, R5
    MOVGT   R5, R9

    // ??????: R4 <= R5 <= R6 <= R7
    // ?? = (R5 + R6) / 2
    ADD     R8, R5, R6
    LSR     R8, R8, #1       // ??1? (??2)
    STR     R8, [R2], #4     // ????,R2??????

    // --- 4. ???? ---
    ADD     R0, R0, #4       // ???????1???
    SUBS    R3, R3, #1       // ????1
    BNE     Loop_Start       // ??0???

Stop:
    B       Stop             // ???

    .end