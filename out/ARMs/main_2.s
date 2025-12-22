        AREA    PROG, CODE, READONLY
        ENTRY
        EXPORT  Reset_Handler

Reset_Handler
        ; ????????
        LDR     R0, =0x20000000      ; ??????
        LDR     R1, =0x20000100      ; ?????????
        
        ; ???? [5,8,12,9,10,3,5,7,8,10,22,31,17,16,13]
        MOV     R2, #5
        STR     R2, [R0], #4
        MOV     R2, #8
        STR     R2, [R0], #4
        MOV     R2, #12
        STR     R2, [R0], #4
        MOV     R2, #9
        STR     R2, [R0], #4
        MOV     R2, #10
        STR     R2, [R0], #4
        MOV     R2, #3
        STR     R2, [R0], #4
        MOV     R2, #5
        STR     R2, [R0], #4
        MOV     R2, #7
        STR     R2, [R0], #4
        MOV     R2, #8
        STR     R2, [R0], #4
        MOV     R2, #10
        STR     R2, [R0], #4
        MOV     R2, #22
        STR     R2, [R0], #4
        MOV     R2, #31
        STR     R2, [R0], #4
        MOV     R2, #17
        STR     R2, [R0], #4
        MOV     R2, #16
        STR     R2, [R0], #4
        MOV     R2, #13
        STR     R2, [R0], #4
        
        ; ??????
        LDR     R0, =0x20000000      ; ??????
        LDR     R1, =0x20000100      ; ??????
        MOV     R2, #15              ; ????
        
        ; ??1: ?????????
        LDR     R3, [R0]             ; ????????????
        MOV     R4, R3               ; ????????????
        MOV     R5, #1               ; ?????(?1??)
        
find_min_max
        CMP     R5, R2
        BGE     min_max_found
        
        LSL     R6, R5, #2           ; ?????????
        LDR     R7, [R0, R6]         ; ??????
        
        ; ?????
        CMP     R7, R3
        BGE     not_min
        MOV     R3, R7               ; ?????
not_min
        
        ; ?????
        CMP     R7, R4
        BLE     not_max
        MOV     R4, R7               ; ?????
not_max
        
        ADD     R5, R5, #1
        B       find_min_max
        
min_max_found
        ; ?? R3 = ???, R4 = ???
        
        ; ??2: ???????(??? - ???)
        SUB     R8, R4, R3           ; R8 = ????
        
        ; ??3: ??????????
        ; ?????: (x - min) / (max - min)
        MOV     R5, #0               ; ?????
        
normalize_loop
        CMP     R5, R2
        BGE     normalization_done
        
        LSL     R6, R5, #2           ; ???????
        LDR     R7, [R0, R6]         ; ?????? x
        
        ; ?? (x - min)
        SUB     R9, R7, R3
        
        ; ??????,????1000?????
        ; ?? (x - min) * 1000
        MOV     R10, #1000
        MUL     R9, R9, R10
        
        ; ??????: ((x - min) * 1000) / (max - min)
        ; ??????
        MOV     R10, R8              ; ?? = ????
        BL      divide
        
        ; R0 ???????(??1000????)
        ; ????
        LSL     R6, R5, #2
        STR     R0, [R1, R6]
        
        ; ??????R8(?????????R0-R3)
        MOV     R8, R10
        
        ADD     R5, R5, #1
        B       normalize_loop
        
normalization_done
        ; ?????,??????
here    B       here

; ?????: R0 = ???, R1 = ??, ?? R0 = ?
divide
        MOV     R2, #0               ; ?????0
        
divide_loop
        CMP     R0, R1               ; ????????
        BLT     divide_done          ; ????? < ??,??
        
        SUB     R0, R0, R1           ; ???????
        ADD     R2, R2, #1           ; ??1
        B       divide_loop
        
divide_done
        MOV     R0, R2               ; ????R0
        BX      LR                   ; ??
        
        END