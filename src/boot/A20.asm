%ifndef A20
%define A20

[bits 32]

enable_a20:
		cli
		pusha

        call    wait_input
        mov     al,0xAD
        out     0x64,al		; disable keyboard
        call    wait_input

        mov     al,0xD0
        out     0x64,al		; tell controller to read output port
        call    wait_output

        in      al,0x60
        push    eax			; get output port data and store it
        call    wait_input

        mov     al,0xD1
        out     0x64,al		; tell controller to write output port
        call    wait_input

        pop     eax
        or      al,2		; set bit 1 (enable a20)
        out     0x60,al		; write out data back to the output port

        call    wait_input
        mov     al,0xAE		; enable keyboard
        out     0x64,al

        call	wait_input
		popa
        sti
        ret

wait_input:
		in      al,0x64
		test    al,2
		jnz     wait_input
		ret

wait_output:
		in      al,0x64
		test    al,1
		jz      wait_output
		ret

%endif ;A20