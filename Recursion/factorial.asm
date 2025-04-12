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

    ADD R6, R6, #-1     ; 
    STR R0, R6, #0      ; Push the parameter for Subroutine into the stack

    JSR	Factorial       ; Call the subroutine to implement it
                        ; The control is then passed to the callee function
    LDR	R0,	R6,	#0      ; fetch the final result
    ADD R6, R6, #2      ; Pop the result and input parameter for the Subroutine

    STR R0, R6, #0      ; update the value into the run-time of this main function
    HALT


; An Review of Run Time Stack:
;
; for the following function,
; function(parameter1, parameter2, parameter3) {
;   variable1;
;   variable2;
;   variable3;
;}
; The run time stack for this function is:
;
;       variable3       R6
;       variable2
;       variable1       R5
;       Caller's Frame Pointer
;       Return Address 
;       Return Value
;       parameter1
;       parameter2
;       parameter3
;   RUN TIME STACK FOR THE CALLEE FUNCTION

FACTORIAL
    ; R5: The frame pointer
    ; R6: the Stack top
    ; R7: Callee Save Info 

    ; for return value and bookkeeping information
        ADD R6, R6, #-2     ; the space for return value and return address
        STR R7, R6, #0      ; store the return address
        ADD R6, R6, #-1     ; the space for the caller stack frame
        STR R5, R6, #0      ; store the caller stack frame
        ADD R5, R6, #-1     ; it is said that this procedure prepare the frame pointer for callee function, 
                            ; but I think that the stackpointer is still R6, R5 is now upper than R6

        LDR R1, R5, #4      ; This is important, this is how the computer does work
                            ; it find the value of parameter/variable by stack frame pointer + offset
                            ; however, since in the factorial function, we have no local variables in factorial function
                            ; so, it seems a little bit strange.
        ADD R2, R1, #-1     ; to check whether R1 > 0 while calculating the R1 - 1 for the next step
        BRn     BASE_CASE 

    ; Here we will do the recrusive part, f(n) = n * f(n-1)
        ADD R6, R6, #-1     ; update the stack top
        STR R2, R6, #0      ; This is the parameter for the calle function
                            ; we will do the recrusive part
    ; Recrusive Part Here
        JSR FACTORIAL

    ; This part is also important, it show the control-transition between callee and caller function
    ; You can first see the RETURN part below, so that you will understand what we are do.
    ; We will use R0 as temporary Register to store the return value
        LDR  R0, R6, #0      ; the stack pointer is at the return value for the callee's callee function
        ADD R6, R6, #2      ; pop the return value and callee's callee's parameter out
        ; remember that we've load R1 with the parameter
        ; HOWEVER, WE CALL ANOTHER FACTORIAL SUBROUTINE, AND ITS VALUE IS CHANGED, SO, WE NEED RO LOAD IT AGAIN
        LDR R1, R5, #4      ;
        ; R2 <- R1 * R0, to calculate the factorial.    
        ST  R7, SAVE_R7     ; Since we will use the subroutine, we need to save R7, caller save.
        JSR POSITIVE_MULTIPLY
        LD  R7, SAVE_R7     ;
        ADD R0, R2, #0      ; Store the value of R2 into R0
        BRnzp   RETURN


    BASE_CASE
        AND R0, R0, #0      ;
        ADD R0, R0, #1      ; factorical(0) = 1

    RETURN 
        STR R0, R5, #3      ; Save teh value of callee function into the return position
                            ; We will pop the local variables form the runtime stack for callee funtion
                            ; BUt since this time, we have no local variable, so nothing here
        LDR R5, R6, #0      ; Since we've popped all the local variables for callee funciton,
                            ; So, the stacktop is now caller's stack frame pointer
        ADD R6, R6, #1     ;
        LDR R7, R6, #0      ; Load the return address 
        ADD R6, R6, #1      ; Now, the stack top is at the return value, we can give control back to caller function

        RET

POSITIVE_MULTIPLY
        ; The input will be inside R0 and R1 (both are positive)
        ; While the output is in R2
        ST  R3, SAVE_R3
        AND	R2,	R2,	#0
        ADD R3, R1, #0
    LOOP
        ADD R2, R2, R0
        ADD R3, R3, #-1
        BRp     LOOP

        LD	R3,	SAVE_R3
        RET

SAVE_R3
        .BLKW   #1
SAVE_R7
        .BLKW	#1
STACK_TOP
    .FILL   x4000

; We can only accept 7! since we only have 16 bits
SENTENCE
    .STRINGZ "Please input a positive number from 0 to 7:
    "
    .END