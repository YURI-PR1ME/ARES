;==========================================================================
;====Power Disassembler for MCS-51 and 6502================================
;==========================================================================
;   Writen by: 覃远高
;   Copyright: 覃远高
;    HomePage: http://coolsh.163.net
;      E-mail: qinyg@163.net
;         Tel: 0755-2282553
;      Update: 3.Jul,2000
;==========================================================================
;===========Disassemble information========================================
;==========================================================================
;    File Name: C:\users\yuri\Desktop\ARES\A013NNNN\KEIL\KEY_SMG.hex
;      IC Body: MCS-51  
;         Date: 12/19/2025
;==========================================================================
;==========================================================================
;标号==============指令================================地址===机器码=======
;==========================================================================
Q0000:             LJMP  Q0003                        ;0000   02 00 03
;==========================================================================
Q0003:             MOV   R0,#7FH                      ;0003   78 7F
                   CLR   A                            ;0005   E4
Q0006:             MOV   @R0,A                        ;0006   F6
                   DJNZ  R0,Q0006                     ;0007   D8 FD
                   MOV   SP,#1CH                      ;0009   75 81 1C
                   LJMP  Q004A                        ;000C   02 00 4A
;==========================================================================
Q000F:             LJMP  Q0158                        ;000F   02 01 58
;==========================================================================
Q0012:             CLR   A                            ;0012   E4
                   MOVC  A,@A+DPTR                    ;0013   93
                   INC   DPTR                         ;0014   A3
                   MOV   R0,A                         ;0015   F8
Q0016:             CLR   A                            ;0016   E4
                   MOVC  A,@A+DPTR                    ;0017   93
                   INC   DPTR                         ;0018   A3
                   JC    Q001E                        ;0019   40 03
                   MOV   @R0,A                        ;001B   F6
                   SJMP  Q001F                        ;001C   80 01
Q001E:             MOVX  @R0,A                        ;001E   F2
Q001F:             INC   R0                           ;001F   08
                   DJNZ  R7,Q0016                     ;0020   DF F4
                   SJMP  Q004D                        ;0022   80 29
Q0024:             CLR   A                            ;0024   E4
                   MOVC  A,@A+DPTR                    ;0025   93
                   INC   DPTR                         ;0026   A3
                   MOV   R0,A                         ;0027   F8
                   ANL   A,#07H                       ;0028   54 07
                   ADD   A,#0CH                       ;002A   24 0C
                   XCH   A,R0                         ;002C   C8
                   CLR   C                            ;002D   C3
                   RLC   A                            ;002E   33
                   SWAP  A                            ;002F   C4
                   ANL   A,#0FH                       ;0030   54 0F
                   ORL   A,#20H                       ;0032   44 20
                   XCH   A,R0                         ;0034   C8
                   MOVC  A,@A+PC                      ;0035   83
                   JC    Q003C                        ;0036   40 04
                   CPL   A                            ;0038   F4
                   ANL   A,@R0                        ;0039   56
                   SJMP  Q003D                        ;003A   80 01
Q003C:             ORL   A,@R0                        ;003C   46
Q003D:             MOV   @R0,A                        ;003D   F6
                   DJNZ  R7,Q0024                     ;003E   DF E4
                   SJMP  Q004D                        ;0040   80 0B
                   AJMP  Q0002                        ;0042   01 02
                   INC   A                            ;0044   04
                   INC   R0                           ;0045   08
                   JBC   24H.0,Q0089                  ;0046   10 20 40
                   SJMP  QFFDB                        ;0049   80 90
Q004A:             MOV   DPTR,#0176H                  ;004A   90 01 76
Q004D:             CLR   A                            ;004D   E4
                   MOV   R6,#01H                      ;004E   7E 01
                   MOVC  A,@A+DPTR                    ;0050   93
                   JZ    Q000F                        ;0051   60 BC
                   INC   DPTR                         ;0053   A3
                   MOV   R7,A                         ;0054   FF
                   ANL   A,#3FH                       ;0055   54 3F
                   JNB   ACC.5,Q0063                  ;0057   30 E5 09
                   ANL   A,#1FH                       ;005A   54 1F
                   MOV   R6,A                         ;005C   FE
                   CLR   A                            ;005D   E4
                   MOVC  A,@A+DPTR                    ;005E   93
                   INC   DPTR                         ;005F   A3
                   JZ    Q0063                        ;0060   60 01
                   INC   R6                           ;0062   0E
Q0063:             XCH   A,R7                         ;0063   CF
                   ANL   A,#0C0H                      ;0064   54 C0
                   ADD   A,ACC                        ;0066   25 E0
                   JZ    Q0012                        ;0068   60 A8
                   JC    Q0024                        ;006A   40 B8
                   CLR   A                            ;006C   E4
                   MOVC  A,@A+DPTR                    ;006D   93
                   INC   DPTR                         ;006E   A3
                   MOV   R2,A                         ;006F   FA
                   CLR   A                            ;0070   E4
                   MOVC  A,@A+DPTR                    ;0071   93
                   INC   DPTR                         ;0072   A3
                   MOV   R0,A                         ;0073   F8
Q0074:             CLR   A                            ;0074   E4
                   MOVC  A,@A+DPTR                    ;0075   93
                   INC   DPTR                         ;0076   A3
                   XCH   A,R0                         ;0077   C8
                   XCH   A,DPL                        ;0078   C5 82
                   XCH   A,R0                         ;007A   C8
                   XCH   A,R2                         ;007B   CA
                   XCH   A,DPH                        ;007C   C5 83
                   XCH   A,R2                         ;007E   CA
                   MOVX  @DPTR,A                      ;007F   F0
                   INC   DPTR                         ;0080   A3
                   XCH   A,R0                         ;0081   C8
                   XCH   A,DPL                        ;0082   C5 82
                   XCH   A,R0                         ;0084   C8
                   XCH   A,R2                         ;0085   CA
                   XCH   A,DPH                        ;0086   C5 83
                   XCH   A,R2                         ;0088   CA
Q0089:             DJNZ  R7,Q0074                     ;0089   DF E9
                   DJNZ  R6,Q0074                     ;008B   DE E7
                   SJMP  Q004D                        ;008D   80 BE
Q008F:             MOV   A,1BH                        ;008F   E5 1B
                   CJNE  A,#0EH,Q00A7                 ;0091   B4 0E 13
                   INC   1CH                          ;0094   05 1C
                   MOV   A,1CH                        ;0096   E5 1C
                   SETB  C                            ;0098   D3
                   SUBB  A,#07H                       ;0099   94 07
                   JC    Q00A0                        ;009B   40 03
                   MOV   1CH,#07H                     ;009D   75 1C 07
Q00A0:             MOV   A,#10H                       ;00A0   74 10
                   ADD   A,1CH                        ;00A2   25 1C
                   MOV   R0,A                         ;00A4   F8
                   MOV   @R0,1CH                      ;00A5   A6 1C
Q00A7:             MOV   A,1BH                        ;00A7   E5 1B
                   CJNE  A,#0DH,Q00BC                 ;00A9   B4 0D 10
                   MOV   A,1CH                        ;00AC   E5 1C
                   SETB  C                            ;00AE   D3
                   SUBB  A,#00H                       ;00AF   94 00
                   JC    Q00BC                        ;00B1   40 09
                   MOV   A,#10H                       ;00B3   74 10
                   ADD   A,1CH                        ;00B5   25 1C
                   MOV   R0,A                         ;00B7   F8
                   MOV   @R0,#0AH                     ;00B8   76 0A
                   DEC   1CH                          ;00BA   15 1C
Q00BC:             MOV   A,1BH                        ;00BC   E5 1B
                   CJNE  A,#0BH,Q00D5                 ;00BE   B4 0B 14
                   CLR   A                            ;00C1   E4
                   MOV   1CH,A                        ;00C2   F5 1C
                   MOV   R7,A                         ;00C4   FF
Q00C5:             MOV   A,#08H                       ;00C5   74 08
                   ADD   A,R7                         ;00C7   2F
                   MOV   R0,A                         ;00C8   F8
                   MOV   A,@R0                        ;00C9   E6
                   MOV   R6,A                         ;00CA   FE
                   MOV   A,#10H                       ;00CB   74 10
                   ADD   A,R7                         ;00CD   2F
                   MOV   R0,A                         ;00CE   F8
                   MOV   @R0,06H                      ;00CF   A6 06
                   INC   R7                           ;00D1   0F
                   CJNE  R7,#08H,Q00C5                ;00D2   BF 08 F0
Q00D5:             RET                                ;00D5   22
;==========================================================================
Q00D6:             MOV   18H,#80H                     ;00D6   75 18 80
                   CLR   A                            ;00D9   E4
                   MOV   1AH,A                        ;00DA   F5 1A
Q00DC:             CLR   A                            ;00DC   E4
                   MOV   P2,A                         ;00DD   F5 A0
                   MOV   A,#10H                       ;00DF   74 10
                   ADD   A,1AH                        ;00E1   25 1A
                   MOV   R0,A                         ;00E3   F8
                   MOV   A,@R0                        ;00E4   E6
                   MOV   DPTR,#0181H                  ;00E5   90 01 81
                   MOVC  A,@A+DPTR                    ;00E8   93
                   MOV   P0,A                         ;00E9   F5 80
                   MOV   P2,18H                       ;00EB   85 18 A0
                   MOV   R7,#05H                      ;00EE   7F 05
                   MOV   R6,#00H                      ;00F0   7E 00
                   LCALL Q0168                        ;00F2   12 01 68
                   MOV   R7,18H                       ;00F5   AF 18
                   MOV   R0,#01H                      ;00F7   78 01
                   MOV   A,R7                         ;00F9   EF
                   INC   R0                           ;00FA   08
                   SJMP  Q00FE                        ;00FB   80 01
Q00FD:             RR    A                            ;00FD   03
Q00FE:             DJNZ  R0,Q00FD                     ;00FE   D8 FD
                   MOV   18H,A                        ;0100   F5 18
                   INC   1AH                          ;0102   05 1A
                   MOV   A,1AH                        ;0104   E5 1A
                   CLR   C                            ;0106   C3
                   SUBB  A,#08H                       ;0107   94 08
                   JC    Q00DC                        ;0109   40 D1
                   RET                                ;010B   22
;==========================================================================
Q010C:             MOV   P1,#0FH                      ;010C   75 90 0F
                   MOV   A,P1                         ;010F   E5 90
                   ANL   A,#0FH                       ;0111   54 0F
                   XRL   A,#0FH                       ;0113   64 0F
                   JZ    Q013F                        ;0115   60 28
                   MOV   R7,#0FH                      ;0117   7F 0F
                   MOV   R6,#00H                      ;0119   7E 00
                   LCALL Q0168                        ;011B   12 01 68
                   MOV   A,P1                         ;011E   E5 90
                   ANL   A,#0FH                       ;0120   54 0F
                   XRL   A,#0FH                       ;0122   64 0F
                   JZ    Q013C                        ;0124   60 16
                   MOV   A,P1                         ;0126   E5 90
                   ANL   A,#0FH                       ;0128   54 0F
                   MOV   19H,A                        ;012A   F5 19
Q012C:             MOV   A,P1                         ;012C   E5 90
                   ANL   A,#0FH                       ;012E   54 0F
                   XRL   A,#0FH                       ;0130   64 0F
                   JZ    Q0139                        ;0132   60 05
                   LCALL Q00D6                        ;0134   12 00 D6
                   SJMP  Q012C                        ;0137   80 F3
Q0139:             MOV   R7,19H                       ;0139   AF 19
                   RET                                ;013B   22
;==========================================================================
Q013C:             MOV   R7,#0FH                      ;013C   7F 0F
                   RET                                ;013E   22
;==========================================================================
Q013F:             MOV   R7,#0FH                      ;013F   7F 0F
                   RET                                ;0141   22
;==========================================================================
Q0142:             CLR   A                            ;0142   E4
                   MOV   R7,A                         ;0143   FF
Q0144:             MOV   A,#08H                       ;0144   74 08
                   ADD   A,R7                         ;0146   2F
                   MOV   R0,A                         ;0147   F8
                   MOV   A,@R0                        ;0148   E6
                   MOV   R6,A                         ;0149   FE
                   MOV   A,#10H                       ;014A   74 10
                   ADD   A,R7                         ;014C   2F
                   MOV   R0,A                         ;014D   F8
                   MOV   @R0,06H                      ;014E   A6 06
                   INC   R7                           ;0150   0F
                   CJNE  R7,#08H,Q0144                ;0151   BF 08 F0
                   CLR   A                            ;0154   E4
                   MOV   1CH,A                        ;0155   F5 1C
                   RET                                ;0157   22
;==========================================================================
Q0158:             LCALL Q0142                        ;0158   12 01 42
Q015B:             LCALL Q010C                        ;015B   12 01 0C
                   MOV   1BH,R7                       ;015E   8F 1B
                   LCALL Q008F                        ;0160   12 00 8F
                   LCALL Q00D6                        ;0163   12 00 D6
                   SJMP  Q015B                        ;0166   80 F3
Q0168:             MOV   A,R7                         ;0168   EF
                   SETB  C                            ;0169   D3
                   SUBB  A,#00H                       ;016A   94 00
                   JC    Q0175                        ;016C   40 07
                   MOV   R6,#0EBH                     ;016E   7E EB
                   DJNZ  R6,$                         ;0170   DE FE
                   DEC   R7                           ;0172   1F
                   SJMP  Q0168                        ;0173   80 F3
Q0175:             RET                                ;0175   22
;==========================================================================
Q0176:		 DB  08H, 08H, 00H, 0AH, 0AH, 0AH, 0AH, 0AH	;........
Q017E:		 DB  0AH, 0AH, 00H,0C0H,0F9H,0A4H,0B0H, 99H	;........
Q0186:		 DB  92H, 82H,0F8H, 80H, 90H,0FFH	;......
;========================================================================== 