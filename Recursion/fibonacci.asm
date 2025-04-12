; This is the LC3 version of a factorial function
    .ORIG   x3000
    LD  R6, STACK_TOP
    LEA	R0,	SENTENCE
    PUTS
    ; Ask the user to input a number and then echo it
    GETC
    OUT
    ; Change the ASCII code into number
    ADD R0, R0, #-16
    ADD R0, R0, #-16
    ADD R0, R0, #-16

    ADD R6, R6, #-1     ; spare stack for parameter
    STR R0, R6, #0      ; push the argument into the stack

    JSR FIBONACCI

    LDR R0, R6, #0      ; get the return value
    ADD R6, R6, #1      ; pop the return value out of the stack
    ADD R6, R6, #1      ; pop the argument out of the stack
    STR R0, R6, #0      ; push the value into the stack

    HALT

; A brief implementation of c program
; int fibonacci(int n) {
;   if(n == 1 || n == 2) {
;       return 1;
;   }
;   a = fibonacci(n-1)
;   return a + fibonacci(n-2);
;}

FIBONACCI
; we store the F(n-1) and F(n-2) in the R1 and R2, and use R4 as temporary
    ADD R6, R6, #-1     ; spare the space for return value
    ADD R6, R6, #-1     ; spare the space for return address
    STR R7, R6, #0      ; store the return address
    ADD R6, R6, #-1     ; spare the space for caller frame pointer
    STR R5, R6, #0      ; store the caller frame pointer
    ADD R6, R6, #-1     ; spare space for variable
    ADD R5, R6, #0      ; the base variable


    LDR R4, R5, #4      ; get the argument
    ; If f(1) or f(2), return 1
    ADD R3, R4, #-1     ; minus the R4
    BRz    BASE_CASE    ;
    ADD R3, R3, #-1     ;
    BRz     BASE_CASE   ;


    ADD R4, R4, #-1     ; n - 1 = R4
    ADD R6, R6, #-1     ;
    STR R4, R6, #0      ; add the argument for the next function
    JSR     FIBONACCI   ;

    LDR R1, R6, #0      ; get f(n-1)
    ADD R6, R6, #1      ; pop the return value
    ADD R6, R6, #1      ; pop the passed-in parameters
                        ; after this step R6 is at the base variable,
                        ; the same as R5
    STR R1, R5, #0      ; push the parameter into stack

    
    LDR R4, R5, #4      ; get the passed in argument
    ADD R4, R4, #-2     ; 
    ADD R6, R6, #-1     ;
    STR R4, R6, #0      ; pass in the argument
    JSR FIBONACCI       ;

    LDR R2, R6, #0      ; get the value of f(n-2)
    ADD R6, R6, #1      ; pop the return value
    ADD R6, R6, #1      ; pop the argument
    
    LDR R1, R5, #0      ; the only variable in the fibonacci function
    ADD R0, R1, R2      ; store the final result in R0
    BRnzp   FINAL       ;

    BASE_CASE
    AND R0, R0, #0      ;
    ADD R0, R0, #1      ;

FINAL
    STR R0, R5, #3      ; push the return value into the stack
    ADD R6, R6, #1      ; pop the local variable
    LDR R5, R6, #0      ; get the previous stack pointer
    ADD R6, R6, #1      ; pop the previous stack pointer
    LDR R7, R6, #0      ; get the return address
    ADD R6, R6, #1      ; pop the return address 
    RET


SAVE_R1
        .BLKW   #1
STACK_TOP
    .FILL   x4000


SENTENCE
    .STRINGZ "Please input a positive number from 0 to 9:
    "
    .END