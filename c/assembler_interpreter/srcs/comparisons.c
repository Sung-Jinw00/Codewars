#include "comparisons.h"

/**
 * @brief Executes a jump to a label.
 *
 * @param instruction Instruction string, e.g., "jmp label".
 * @return Pointer to the subroutine execution result or NULL.
 */
char	*jmp(const char *instruction)
{
	if (!instruction || !*instruction)
		return (NULL);
	char label[50] = {0};

	sscanf(instruction, "jmp %s", label);
	if (label_exist(label))
		return (exec_label(label));
	ret = true;
	return (NULL);
}

/**
 * @brief Jump to a label if last comparison was not equal (x != y).
 *
 * @param instruction Instruction string, e.g., "jne label".
 * @return Pointer to the subroutine execution result, or NULL if label doesn't exist.
 */
char	*jne(const char *instruction)
{
	if (!instruction || !*instruction)
		return (NULL);
	char label[50] = {0};

	sscanf(instruction, "jne %s", label);
	if (!label_exist(label))
		ret = true;
	else if (last_cmp)
		return (exec_label(label));
	return (NULL);
}

/**
 * @brief Jump to a label if last comparison was equal (x == y).
 *
 * @param instruction Instruction string, e.g., "je label".
 * @return Pointer to the subroutine execution result, or NULL if label doesn't exist.
 */
char	*je(const char *instruction)
{
	if (!instruction || !*instruction)
		return (NULL);
	char label[50] = {0};

	sscanf(instruction, "je %s", label);
	if (!label_exist(label))
		ret = true;
	else if (!last_cmp)
		return (exec_label(label));
	return (NULL);
}

/**
 * @brief Jump to a label if last comparison was greater or equal (x >= y).
 *
 * @param instruction Instruction string, e.g., "jge label".
 * @return Pointer to the subroutine execution result, or NULL if label doesn't exist.
 */
char	*jge(const char *instruction)
{
	if (!instruction || !*instruction)
		return (NULL);
	char label[50] = {0};

	sscanf(instruction, "jge %s", label);
	if (!label_exist(label))
		ret = true;
	else if (last_cmp >= 0)
		return (exec_label(label));
	return (NULL);
}

/**
 * @brief Jump to a label if last comparison was greater (x > y).
 *
 * @param instruction Instruction string, e.g., "jg label".
 * @return Pointer to the subroutine execution result, or NULL if label doesn't exist.
 */
char	*jg(const char *instruction)
{
	if (!instruction || !*instruction)
		return (NULL);
	char label[50] = {0};

	sscanf(instruction, "jg %s", label);
	if (!label_exist(label))
		ret = true;
	else if (last_cmp > 0)
		return (exec_label(label));
	return (NULL);
}

/**
 * @brief Jump to a label if last comparison was less or equal (x <= y).
 *
 * @param instruction Instruction string, e.g., "jle label".
 * @return Pointer to the subroutine execution result, or NULL if label doesn't exist.
 */
char	*jle(const char *instruction)
{
	if (!instruction || !*instruction)
		return (NULL);
	char label[50] = {0};

	sscanf(instruction, "jle %s", label);
	if (!label_exist(label))
		ret = true;
	else if (last_cmp <= 0)
		return (exec_label(label));
	return (NULL);
}

/**
 * @brief Jump to a label if last comparison was less (x < y).
 *
 * @param instruction Instruction string, e.g., "jl label".
 * @return Pointer to the subroutine execution result, or NULL if label doesn't exist.
 */
char	*jl(const char *instruction)
{
	if (!instruction || !*instruction)
		return (NULL);
	char label[50] = {0};

	sscanf(instruction, "jl %s", label);
	if (!label_exist(label))
		ret = true;
	else if (last_cmp < 0)
		return (exec_label(label));
	return (NULL);
}
