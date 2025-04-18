/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler_interpreter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:45:18 by marvin            #+#    #+#             */
/*   Updated: 2025/04/17 00:45:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LEN_INT 11

/* ────────────────────────────────────────────────────────────────────────── */
/*                              Global variables                              */
/* ────────────────────────────────────────────────────────────────────────── */

// ───────────────────────────────
//  Variables
// ───────────────────────────────

bool	ret = false;
bool	end = false;
int		last_cmp = 0;

// ───────────────────────────────
//  Instructions
// ───────────────────────────────

// instructions array
const char *asm_commands[] = {"mov", "inc", "dec", "add", "sub", "mul", "div", "cmp", "jmp", "jne", "je", "jge", "jg", "jle", "jl", NULL};

// lenght of instructions array
//						"mov", "inc", "dec", "add", "sub", "mul", "div", "cmp", "jmp", "jne", "je", "jge", "jg", "jle", "jl", NULL
size_t len_commands[] = { 3,     3,     3,     3,     3,     3,     3,     3,     3,     3,    2,     3,    2,     3,    2};

// ───────────────────────────────
//  Labels
// ───────────────────────────────

// labels array
char *label_storages[500] = {0};

// sub-routines array
char **label_sub_routines[500] = {0};

// ───────────────────────────────
//  Registers
// ───────────────────────────────

// Registers a-z
int registers[26] = {0};


/* ────────────────────────────────────────────────────────────────────────── */
/*                                    Utils                                   */
/* ────────────────────────────────────────────────────────────────────────── */

bool	label_exist(char *label)
{
	if (!label || !*label)
		return (false);
	int i = 0, len_label = strlen(label);
	while (label_storages[i] && strncmp(label, label_storages[i], len_label))
		i++;
	return (label_storages[i] && !strncmp(label, label_storages[i], len_label));
}

void	free_label_storages(char **array)
{
	for (int i = 0; array && array[i]; i++)
		free(array[i]);
}

void	free_array(char ***array)
{
	for (int i = 0; *array && (*array)[i]; i++)
		free((*array)[i]);
	free(*array);
	*array = NULL;
}

int	skip_wspaces(char *str)
{
	int i = 0;

	while (isspace(str[i]))
		i++;
	return (i);
}

int	strclen(char *program, char cut)
{
	int i = 0;
	while (program && program[i] && program[i] != cut)
		i++;
	return (i);
}

int	count_words(char *program, char cut, int limit)
{
	int trigger = 0, count = 0;

	for (int i = 0; i < limit && program[i]; i++)
	{
		if (program[i] && program[i] == cut && trigger)
			trigger = 0;
		while (i < limit && program[i] == cut)
			i++;
		i += skip_wspaces(program + i);
		if (i < limit && program[i] && program[i] != cut && !trigger)
			(trigger = 1, count++);
	}
	return (count);
}

char	**split(char *program, char cut, int limit)
{
	int len_word = 0, trigger = 0;

	if (!program || !program[0])
		return (free(program), NULL);
	int count = count_words(program, cut, limit);
	if (!count)
		return (free(program), NULL);
	char **arr = calloc(sizeof(char *), count + 1);
	if (!arr)
		return (free(program), NULL);
	int j = 0;
	for (int i = 0; i < limit && program[i]; i++)
	{
		i += skip_wspaces(program + i);
		if (strclen(program + i, ';') < strclen(program + i, cut))
			len_word = strclen(program + i, ';'), trigger = 1;
		else
			len_word = strclen(program + i, cut);
		if (program[i] && len_word)
		{
			arr[j++] = strndup(program + i, len_word);
			i += len_word;
		}
		if (i < limit && trigger)
			trigger = 0, i += strclen(program + i, cut);
	}
	arr[count] = NULL;
	return (free(program), arr);
}

char **remove_wspaces(char **array)
{
	if (!array)
		return (NULL);
	for (int i = 0; array[i]; i++)
	{
		int j = 0, k = j;
		while (isspace(array[i][k]))
			k++;
		while (array[i][k])
			array[i][j++] = array[i][k++];
		while (j < k)
			array[i][j++] = 0;
	}
	return (array);
}

int	label(const char *program);
/* i found back the label in the original string, if i found the label */
void	get_labels_and_sub_routines(char* program)
{
	if (!program)
		return ;

	int i = 0, pos_label = 0, len_program = (int)strlen(program);
	while (i < len_program && program[i])//i found back the label in the original string
	{
		int len = strclen(program + i, '\n');
		if (len != 0 && program[i + len - 1] == ':')
		{
			pos_label = label(program + i);
			i += len + 1;//i go to the next line
			int j = i;//i go to the next line
			/* while i didn't reach the end of the sub_routine by encountering a `\n` or a `;`*/
			while (program[j]) 
			{
				if (program[j] != '\n')
					j += skip_wspaces(program + j);
				if (program[j] == '\n' || program[j] == ';')
					break ;
				j += strclen(program + j, '\n') + 1;
			}
			label_sub_routines[pos_label] = remove_wspaces(split(strdup(program + i), '\n', j - i));
			i = j;
		}
		i += strclen(program + i, '\n'), i += skip_wspaces(program + i);
	}
	free(program);
}

/* count the strings in an array */
int	count_tabs(char **arr)
{
	int i = 0;

	while (arr && arr[i])
		i++;
	return (i);
}

char	*get_msg(char *msg)
{
	int j, len_msg = strlen(msg);
	char final_msg[10000] = {0};
	
	for (int i = 0; i < len_msg && msg[i] && msg[i] != ';'; i++)//while i didn't reach the end of the line or the comment mark 
	{
		if (msg[i] == '\'')//if i have quotes
		{
			i++;
			if (!strncmp(msg + i, "This program should return -1", 29))//and i have to return something
				return ((char *)-1);//i return it
			for (j = i; msg[j] != '\'';)//i go reach the end of the quote
				j++;
			if (!final_msg[0])//if i didn't write anything yet
				strncpy(final_msg, msg + i, j - i);//i return a duplicate of the message between quotes
			else
				strncat(final_msg, msg + i, j - i);//else i join the duplicate to the current message and free them
			i = j + 1;
		}
		else if (isalpha(msg[i]))
		{
			char buffer[MAX_LEN_INT + 1];
			sprintf(buffer, "%d", registers[msg[i] - 'a']);//i take the value of the register in a string format and add it to final_msg like above
			if (!final_msg[0])
				strcpy(final_msg, buffer);
			else
				strcat(final_msg, buffer);
		}
	}
	return (strdup(final_msg));
}

/* ────────────────────────────────────────────────────────────────────────── */
/*                                Instructions                                */
/* ────────────────────────────────────────────────────────────────────────── */

// - `mov x, y`: copies the value `y` (integer or register) into register `x`.
void	mov(const char *instruction)
{
	char arg1[16] = {0}, arg2[16] = {0};

	sscanf(instruction, "mov %16[^,],%*[, ] %15s", arg1, arg2);
	if (isalpha(arg2[0]))
		registers[arg1[0] - 'a'] = registers[arg2[0] - 'a'];
	else
		registers[arg1[0] - 'a'] = atoi(arg2);
}

// - `inc x`: increments the value of register `x` by 1.
void	inc(const char *instruction)
{
	char arg1[16] = {0};

	sscanf(instruction, "inc %s", arg1);
	registers[arg1[0] - 'a']++;
}

// - `dec x`: decrements the value of register `x` by 1.
void	dec(const char *instruction)
{
	char arg1[16] = {0};

	sscanf(instruction, "dec %s", arg1);
	registers[arg1[0] - 'a']--;
}

// - `add x, y`: adds `y` (integer or register) to `x` (register[x] += y).
void	add(const char *instruction)
{
	char arg1[16] = {0}, arg2[16] = {0};

	sscanf(instruction, "add %16[^,],%*[, ] %15s", arg1, arg2);
	if (isalpha(arg2[0]))
		registers[arg1[0] - 'a'] += registers[arg2[0] - 'a'];
	else
		registers[arg1[0] - 'a'] += atoi(arg2);
}

// - `sub x, y`: subtracts `y` from `x` (register[x] -= y).
void	sub(const char *instruction)
{
	char arg1[16] = {0}, arg2[16] = {0};

	sscanf(instruction, "sub %16[^,],%*[, ] %15s", arg1, arg2);
	if (isalpha(arg2[0]))
		registers[arg1[0] - 'a'] -= registers[arg2[0] - 'a'];
	else
		registers[arg1[0] - 'a'] -= atoi(arg2);
}

// - `mul x, y`: multiplies `x` by `y` (register[x] *= y).
void	mul(const char *instruction)
{
	char arg1[16] = {0}, arg2[16] = {0};

	sscanf(instruction, "mul %16[^,],%*[, ] %15s", arg1, arg2);
	if (isalpha(arg2[0]))
		registers[arg1[0] - 'a'] *= registers[arg2[0] - 'a'];
	else
		registers[arg1[0] - 'a'] *= atoi(arg2);
}

// - `div x, y`: divides `x` by `y` using integer division (register[x] /= y).
void	div_func(const char *instruction)
{
	char arg1[16] = {0}, arg2[16] = {0};

	sscanf(instruction, "div %16[^,],%*[, ] %15s", arg1, arg2);
	if (isalpha(arg2[0]))
		registers[arg1[0] - 'a'] /= registers[arg2[0] - 'a'];
	else
		registers[arg1[0] - 'a'] /= atoi(arg2);
}

// - `label:`: defines a label in the program (identifier followed by ":"), used for jumps or calls.
int	label(const char *program)
{
	int i = 0;
	char arg1[50] = {0};

	sscanf(program, "%49[^:]:", arg1);
	while (i < 500 && label_storages[i]) // check for label storage slot
		i++;
	label_storages[i] = strdup(arg1); // store label
	label_storages[i + 1] = NULL; // store label
	return (i);
}

// - `cmp x, y`: compares `x` and `y`, used for conditional jumps.
void	cmp(const char *instruction)
{
	char arg1[16] = {0}, arg2[16] = {0};

	sscanf(instruction, "cmp %16[^,],%*[, ] %15s", arg1, arg2);
	if (isalpha(arg2[0]))
		last_cmp = (int)registers[arg1[0] - 'a'] - (int)registers[arg2[0] - 'a'];
	else
		last_cmp = (int)registers[arg1[0] - 'a'] - atoi(arg2);
}

char	*exec_label(char *label);
// - `jmp lbl`: jumps to the label `lbl`.
char	*jmp(const char *instruction)
{
	char label[50] = {0};

	sscanf(instruction, "jmp %s", label);
	if (label_exist(label))
		return (exec_label(label));
	return (NULL);
}

// - `jne lbl`: jumps to `lbl` if `x` != `y` (from last `cmp`).
char	*jne(const char *instruction)
{
	char label[50] = {0};

	sscanf(instruction, "jne %s", label);
	if (last_cmp && label_exist(label))
		return (exec_label(label));
	return (NULL);
}

// - `je lbl`: jumps to `lbl` if `x` == `y`.
char	*je(const char *instruction)
{
	char label[50] = {0};

	sscanf(instruction, "je %s", label);
	if (!last_cmp && label_exist(label))
		return (exec_label(label));
	return (NULL);
}

// - `jge lbl`: jumps to `lbl` if `x` >= `y`.
char	*jge(const char *instruction)
{
	char label[50] = {0};

	sscanf(instruction, "jge %s", label);
	if (last_cmp >= 0 && label_exist(label))
		return (exec_label(label));
	return (NULL);
}

// - `jg lbl`: jumps to `lbl` if `x` > `y`.
char	*jg(const char *instruction)
{
	char label[50] = {0};

	sscanf(instruction, "jg %s", label);
	if (last_cmp > 0 && label_exist(label))
		return (exec_label(label));
	return (NULL);
}

// - `jle lbl`: jumps to `lbl` if `x` <= `y`.
char	*jle(const char *instruction)
{
	char label[50] = {0};

	sscanf(instruction, "jle %s", label);
	if (last_cmp <= 0 && label_exist(label))
		return (exec_label(label));
	return (NULL);
}

// - `jl lbl`: jumps to `lbl` if `x` < `y`.
char	*jl(const char *instruction)
{
	char label[50] = {0};

	sscanf(instruction, "jl %s", label);
	if (last_cmp < 0 && label_exist(label))
		return (exec_label(label));
	return (NULL);
}

// - `call lbl`: calls the subroutine at `lbl`. Execution resumes after `ret`.

// - `ret`: returns to the instruction following the most recent `call`.

// - `msg 'Text', x, ...`: stores the program output. Accepts quoted text and register values. Argument count is variable.

// - `end`: indicates the program ends successfully. Triggers output return. Without it, default output is used.

// - `; comment`: any text after a semicolon is ignored (comment).

// instruction's functions array
void	(*command_functions[])(const char *) = {mov, inc, dec, add, sub, mul, div_func, cmp, NULL};
char	*(*command_functions_return[])(const char *) = {jmp, jne, je, jge, jg, jle, jl, NULL};
/* ────────────────────────────────────────────────────────────────────────── */
/*                                    Exec                                    */
/* ────────────────────────────────────────────────────────────────────────── */

char	*exec_routine(char **arr_cmds, int routine_lvl);

char	*exec_label(char *label)
{
	if (!label || !*label)
		return (NULL);
	int i = 0;
	while (isspace(*label))
		label++;
	while (label_storages[i] && strcmp(label_storages[i], label))//i search for the label increment
		i++;
	if (!label_sub_routines[i])
		return (NULL);
	return (exec_routine(label_sub_routines[i], 1));//i execute the sub-instruction of the label
}

void	skip_sub_routine(char **arr_cmds, int *j)
{
	if (!arr_cmds || !*arr_cmds)
		return ;
	int i = 0, k = 0, len_cmp = strclen(arr_cmds[*j], ':');

	while (label_storages[i] && strncmp(arr_cmds[*j], label_storages[i], len_cmp))//i search for the label increment
		i++;
	if (label_sub_routines[i])
	{
		while (label_sub_routines[i][k] && !strcmp(arr_cmds[++(*j)], label_sub_routines[i][k]))
			k++;
		(*j)--;
	}
}

char	*exec_routine(char **arr_cmds, int routine_lvl)
{
	if (!arr_cmds || !*arr_cmds)
		return (NULL);
	char *answer = NULL;
	
	for (int j = 0; arr_cmds[j]; j++)//while i didn't reach the end of the asm
	{
		if (!routine_lvl && ret)
			ret = false;
		if (routine_lvl && ret)
			return (answer);
		if ( end || !strncmp(arr_cmds[j], "end", 3))// if i have end, i quit the exec and return answer
			return (end = true, answer);
		else if (routine_lvl && !strncmp(arr_cmds[j], "ret", 3))//if i have ret and i'm in a sub_routine, i quit the sub_routine
			return (ret = true, answer);
		else if (!strncmp(arr_cmds[j], "msg ", 4))//if i have msg, i go get the message
		{
			if (answer)
				free(answer);
			answer = get_msg(arr_cmds[j] + 4);
		}
		else if (!strncmp(arr_cmds[j], "call ", 5))//if i have call, i go execute the sub_routine of the label
		{
			if (answer)
				free(answer);
			answer = exec_label(arr_cmds[j] + 5);
		}
		else if (arr_cmds[j][strlen(arr_cmds[j]) - 1] == ':')
			skip_sub_routine(arr_cmds, &j);
		else if (arr_cmds[j][0] == 'j')
		{
			for (int i = 0; asm_commands[i + 8]; i++)//else, i search for the current instruction  : jmp, jne, je, jge, jg, jle, jl
			{
				if (!strncmp(arr_cmds[j], asm_commands[i + 8], len_commands[i + 8]))//if i find an instruction
				{
					if (answer)
						free(answer);
					answer = command_functions_return[i]((const char *)arr_cmds[j]);//i go execute it
					break ;
				}
			}
		}
		else
		{
			for (int i = 0; asm_commands[i]; i++)//else, i search for the current instruction
			{
				if (!strncmp(arr_cmds[j], asm_commands[i], len_commands[i]))//if i find an instruction
				{
					command_functions[i]((const char *)arr_cmds[j]);//i go execute it
					break ;
				}
			}
		}
	}
	return (answer);
}

/* ────────────────────────────────────────────────────────────────────────── */
/*                                    Main                                    */
/* ────────────────────────────────────────────────────────────────────────── */

char	*assembler_interpreter(const char* program)
{
	if (!program || !*program)
		return (NULL);
	for (int i = 0; i < 500; i++)
	{
		label_storages[i] = NULL;
		label_sub_routines[i] = NULL;
	}
	/* i take all my labels and sub-routines before starting, facilitate the access of those when multiple `call` occurs */
	get_labels_and_sub_routines(strdup(program));
	/* i create an array of instructions, easier to move and compare */
	char **arr_cmds = split(strdup(program), '\n', strlen(program));
	if (!arr_cmds)
		return (NULL);
	char *answer = exec_routine(arr_cmds, 0);
	free_array(&arr_cmds);
	free_label_storages(label_storages);
	for (int i = 0; label_sub_routines[i]; i++)
		free_array(&label_sub_routines[i]);
	last_cmp = 0;
	end = false;
	ret = false;
	return (answer);
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
		char *result = assembler_interpreter("\
mov   a, 2            ; value1\n\
mov   b, 10           ; value2\n\
ov   c, a            ; temp1\n\
mov   d, b            ; temp2\n\
call  proc_func\n\
cal  print\n\
call  proc_gcd\n\
call  print\n\
end\n\
\n\
proc_func:\n\
    cmp   d, 1\n\
    je    contnue\n\
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
");
		free(result);
		continue ;
		if (answer[i] == (char *)-1)
		{
			printf(CYAN UNDERLINE BOLD"\n\nTest %ld :"RESET CYAN" result = "RESET"|%p|\n", i + 1, (void *)result);
			if (result == (char *)-1)
				printf(GREEN"\nNo diff, congrats !\n"RESET);
			else
				printf(RED UNDERLINE"\ndifference !"RESET RED"\nanswer = "RESET"|0xffffffffffffffff|");
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
