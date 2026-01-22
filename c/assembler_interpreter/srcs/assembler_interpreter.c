#include "assembler_interpreter.h"

// Instruction strings
const char *asm_commands[] = {
    "mov", "inc", "dec", "add", "sub", "mul", "div",
    "cmp", "jmp", "jne", "je", "jge", "jg", "jle", "jl", NULL
};

// Instruction lengths
size_t len_commands[] = {
    3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 2, 3, 2, 3, 2
};

char	*exec_routine(char **arr_cmds, int routine_lvl);

/**
 * @brief Executes a subroutine by label.
 *
 * @param label Label name.
 * @return Pointer to the subroutine execution result.
 */
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

/**
 * @brief Executes a routine (array of instructions) recursively.
 *
 * @param arr_cmds Array of instruction strings.
 * @param routine_lvl Level of recursion (0 for main program, >0 for subroutine).
 * @return Pointer to the output message or -1.
 */
char	*exec_routine(char **arr_cmds, int routine_lvl)
{
	if (!arr_cmds || !*arr_cmds)
		return (NULL);
	char *answer = (char *)-1;
	
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
			if (answer != (char *)-1 && answer)
				free(answer);
			answer = get_msg(arr_cmds[j] + 4);
		}
		else if (!strncmp(arr_cmds[j], "call ", 5))//if i have call, i go execute the sub_routine of the label
		{
			if (answer != (char *)-1 && answer)
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
					if (answer != (char *)-1 && answer)
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

/**
 * @brief Top-level assembler interpreter.
 *
 * Parses labels, subroutines, and executes the given program string.
 *
 * @param program Program string to execute.
 * @return Output message as string, or (char*)-1 if the program returns that special value.
 */
char	*assembler_interpreter(const char* program)
{
	if (!program || !*program)
		return (NULL);
	printf("program = %s\n\n\n", program);
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
	for (int i = 0; arr_cmds[i]; i++)
		printf("arr_cmds[%d] = %s\n", i, arr_cmds[i]);
	free_array(&arr_cmds);
	printf("%p\n", arr_cmds);
	free_label_storages(label_storages);
	for (int i = 0; label_sub_routines[i]; i++)
		free_array(&label_sub_routines[i]);
	last_cmp = 0;
	end = false;
	ret = false;
	return (answer);
}
