#include "labels.h"

/**
 * @brief Checks if a label exists in the global label storage.
 *
 * @param label The label to search for.
 * @return true if the label exists, false otherwise.
 */
bool	label_exist(char *label)
{
	if (!label || !*label)
		return (false);
	int i = 0, len_label = strlen(label);
	while (label_storages[i] && strncmp(label, label_storages[i], len_label))
		i++;
	return (label_storages[i] && !strncmp(label, label_storages[i], len_label));
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
			if (pos_label != -1)
			{
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
		}
		i += strclen(program + i, '\n'), i += skip_wspaces(program + i);
	}
	free(program);
}

/**
 * @brief Stores a label from a program line into global label storage.
 *
 * @param program Program line containing the label (ending with ':').
 * @return Index of the stored label, or -1 on error.
 */
int	label(const char *program)
{
	if (!program || !*program)
		return (-1);
	int i = 0;
	char arg1[500] = {0};

	sscanf(program, "%49[^:]:", arg1);
	while (i < 500 && label_storages[i]) // check for label storage slot
		i++;
	label_storages[i] = strdup(arg1); // store label
	label_storages[i + 1] = NULL; // store label
	return (i);
}

/**
 * @brief Skips the instructions that belong to a subroutine.
 *
 * Used to ignore the content of a subroutine when scanning main program instructions.
 *
 * @param arr_cmds Array of instruction strings.
 * @param j Pointer to the current instruction index; will be updated to skip the subroutine.
 */
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
