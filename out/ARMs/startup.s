// Simple startup file for Cortex-M0
.syntax unified
.cpu cortex-m0
.thumb

.global Reset_Handler
.global __Vectors

// Minimal vector table
.section .isr_vector,"a",%progbits
.align 2
__Vectors:
    .word 0x20001000          // Initial stack pointer (adjust based on your RAM size)
    .word Reset_Handler       // Reset handler
    .word 0                   // NMI handler
    .word 0                   // Hard fault handler
    // Add more vectors as needed for your specific MCU

.section .text.Reset_Handler
.thumb_func
Reset_Handler:
    // Initialize .data section (copy from ROM to RAM)
    ldr r0, =_sdata
    ldr r1, =_edata
    ldr r2, =_sidata
    b copy_data_check
    
copy_data_loop:
    ldr r3, [r2], #4
    str r3, [r0], #4
    
copy_data_check:
    cmp r0, r1
    blt copy_data_loop
    
    // Zero initialize .bss section
    ldr r0, =_sbss
    ldr r1, =_ebss
    movs r2, #0
    b zero_bss_check
    
zero_bss_loop:
    str r2, [r0], #4
    
zero_bss_check:
    cmp r0, r1
    blt zero_bss_loop
    
    // Call main function
    bl main
    
    // If main returns, loop forever
infinite_loop:
    b infinite_loop