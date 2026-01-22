#include "assembler_interpreter.h"

# ifndef RESET
#  define RESET				"\033[0m"
# endif

/* Bold text */
# ifndef BOLD
#  define BOLD				"\033[1m"
# endif

/* Underlined text */
# ifndef UNDERLINE
#  define UNDERLINE			"\033[4m"
# endif

/* Cyan text */
# ifndef CYAN
#  define CYAN				"\033[36m"
# endif

/* Red text */
# ifndef RED
#  define RED				"\033[31m"
# endif

/* Green text */
# ifndef GREEN
#  define GREEN				"\033[32m"
# endif

int main(void)
{
	const char *instructions[] = {
		(const char []){"msg 'Hello World!'\n\
  testlabel:\n\
  ; test comment\n\
  mov a,1\n\
  end"},
		(const char []){"\
; My first program\n\
mov  a, 5\n\
inc  a\n\
call function\n\
msg  '(5+1)/2 = ', a    ; output message\n\
end\n\
\n\
function:\n\
    div  a, 2\n\
    ret\n"},
		(const char []){"\
mov   a, 5\n\
mov   b, a\n\
mov   c, a\n\
call  proc_fact\n\
call  print\n\
end\n\
\n\
proc_fact:\n\
    dec   b\n\
    mul   c, b\n\
    cmp   b, 1\n\
    jne   proc_fact\n\
    ret\n\
\n\
print:\n\
    msg   a, '! = ', c ; output text\n\
    ret\n\
"},
		(const char []){"\
mov   a, 8            ; value\n\
mov   b, 0            ; next\n\
mov   c, 0            ; counter\n\
mov   d, 0            ; first\n\
mov   e, 1            ; second\n\
call  proc_fib\n\
call  print\n\
end\n\
\n\
proc_fib:\n\
    cmp   c, 2\n\
    jl    func_0\n\
    mov   b, d\n\
    add   b, e\n\
    mov   d, e\n\
    mov   e, b\n\
    inc   c\n\
    cmp   c, a\n\
    jle   proc_fib\n\
    ret\n\
\n\
func_0:\n\
    mov   b, c\n\
    inc   c\n\
    jmp   proc_fib\n\
\n\
print:\n\
    msg   'Term ', a, ' of Fibonacci series is: ', b        ; output text\n\
    ret\n\
"},
		(const char []){"\
mov   a, 11           ; value1\n\
mov   b, 3            ; value2\n\
call  mod_func\n\
msg   'mod(', a, ', ', b, ') = ', d        ; output\n\
end\n\
\n\
; Mod function\n\
mod_func:\n\
    mov   c, a        ; temp1\n\
    div   c, b\n\
    mul   c, b\n\
    mov   d, a        ; temp2\n\
    sub   d, c\n\
    ret\n\
"
},
		(const char []){"\
mov   a, 81         ; value1\n\
mov   b, 153        ; value2\n\
call  init\n\
call  proc_gcd\n\
call  print\n\
end\n\
\n\
proc_gcd:\n\
    cmp   c, d\n\
    jne   loop\n\
    ret\n\
\n\
loop:\n\
    cmp   c, d\n\
    jg    a_bigger\n\
    jmp   b_bigger\n\
\n\
a_bigger:\n\
    sub   c, d\n\
    jmp   proc_gcd\n\
\n\
b_bigger:\n\
    sub   d, c\n\
    jmp   proc_gcd\n\
\n\
init:\n\
    cmp   a, 0\n\
    jl    a_abs\n\
    cmp   b, 0\n\
    jl    b_abs\n\
    mov   c, a            ; temp1\n\
    mov   d, b            ; temp2\n\
    ret\n\
\n\
a_abs:\n\
    mul   a, -1\n\
    jmp   init\n\
\n\
b_abs:\n\
    mul   b, -1\n\
    jmp   init\n\
\n\
print:\n\
    msg   'gcd(', a, ', ', b, ') = ', c\n\
    ret\n\
"},
		(const char []){"\
call  func1\n\
call  print\n\
end\n\
\n\
func1:\n\
    call  func2\n\
    ret\n\
\n\
func2:\n\
    ret\n\
\n\
print:\n\
    msg 'This program should return -1'\n\
"},
		(const char []){"\
mov   a, 2            ; value1\n\
mov   b, 10           ; value2\n\
mov   c, a            ; temp1\n\
mov   d, b            ; temp2\n\
call  proc_func\n\
call  print\n\
end\n\
\n\
proc_func:\n\
    cmp   d, 1\n\
    je    continue\n\
    mul   c, a\n\
    dec   d\n\
    call  proc_func\n\
\n\
continue:\n\
    ret\n\
\n\
print:\n\
    msg a, '^', b, ' = ', c\n\
    ret\n\
"},
		0x0
	};
	char *answer[] = {
		"Hello World!",
		"(5+1)/2 = 3",
		"5! = 120",
		"Term 8 of Fibonacci series is: 21",
		"mod(11, 3) = 2",
		"gcd(81, 153) = 9",
		(char *)-1,
		"2^10 = 1024",
		0x0
	};
		
	for(size_t i = 0; instructions[i]; i++)
	{
		char *result = assembler_interpreter("vwe\nmove c\nw rve \nrver");
		if (result == (char *)-1)
		{
			printf(CYAN UNDERLINE BOLD"\n\nTest %ld :"RESET CYAN" result = "RESET"|%p|\n", i + 1, (void *)result);
			if (result == (char *)-1)
				printf(GREEN"\nNo diff, congrats !\n"RESET);
			else
				printf(RED UNDERLINE"\ndifference !"RESET RED"\nanswer = "RESET"|0xffffffffffffffff|");
			continue ;
		}
		else
		{
			if (!result)
				printf(CYAN UNDERLINE BOLD"\n\nTest %ld :"RESET CYAN" result = "RESET"|(null)|\n", i + 1);
			else
				printf(CYAN UNDERLINE BOLD"\n\nTest %ld :"RESET CYAN" result = "RESET"|%s|\n", i + 1, result);
			free(result);
			continue ;
		}
		if (!result)
			printf(CYAN UNDERLINE BOLD"\n\nTest %ld :"RESET CYAN" result = "RESET"|(null)|\n", i + 1);
		else
			printf(CYAN UNDERLINE BOLD"\n\nTest %ld :"RESET CYAN" result = "RESET"|%s|\n", i + 1, result);
		if (!result || strcmp(result, answer[i]))
			printf(RED UNDERLINE"\ndifference !"RESET RED"\nanswer = "RESET"|%s|", answer[i]);
		else
			printf(GREEN"\nNo diff, congrats !\n"RESET);
		free(result);
	}
	return (0);
}
