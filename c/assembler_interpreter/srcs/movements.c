#include "movements.h"

/**
 * @brief Copies a value (immediate or from another register) into a register.
 *
 * @param instruction Instruction string, e.g., "mov a, 5".
 */
void	mov(const char *instruction)
{
	if (!instruction || !*instruction)
		return ;
	char arg1[16] = {0}, arg2[16] = {0};

	sscanf(instruction, "mov %16[^,],%*[, ] %15s", arg1, arg2);
	if (isalpha(arg2[0]))
		registers[arg1[0] - 'a'] = registers[arg2[0] - 'a'];
	else
		registers[arg1[0] - 'a'] = atoi(arg2);
}

/**
 * @brief Increments the value of a register by 1.
 *
 * @param instruction Instruction string, e.g., "inc a".
 */
void	inc(const char *instruction)
{
	if (!instruction || !*instruction)
		return ;
	char arg1[16] = {0};

	sscanf(instruction, "inc %s", arg1);
	registers[arg1[0] - 'a']++;
}

/**
 * @brief Decrements the value of a register by 1.
 *
 * @param instruction Instruction string, e.g., "dec a".
 */
void	dec(const char *instruction)
{
	if (!instruction || !*instruction)
		return ;
	char arg1[16] = {0};

	sscanf(instruction, "dec %s", arg1);
	registers[arg1[0] - 'a']--;
}

/**
 * @brief Adds a value (immediate or from another register) to a register.
 *
 * @param instruction Instruction string, e.g., "add a, b".
 */
void	add(const char *instruction)
{
	if (!instruction || !*instruction)
		return ;
	char arg1[16] = {0}, arg2[16] = {0};

	sscanf(instruction, "add %16[^,],%*[, ] %15s", arg1, arg2);
	if (isalpha(arg2[0]))
		registers[arg1[0] - 'a'] += registers[arg2[0] - 'a'];
	else
		registers[arg1[0] - 'a'] += atoi(arg2);
}

/**
 * @brief Subtracts a value (immediate or from another register) from a register.
 *
 * @param instruction Instruction string, e.g., "sub a, b".
 */
void	sub(const char *instruction)
{
	if (!instruction || !*instruction)
		return ;
	char arg1[16] = {0}, arg2[16] = {0};

	sscanf(instruction, "sub %16[^,],%*[, ] %15s", arg1, arg2);
	if (isalpha(arg2[0]))
		registers[arg1[0] - 'a'] -= registers[arg2[0] - 'a'];
	else
		registers[arg1[0] - 'a'] -= atoi(arg2);
}

/**
 * @brief Multiplies a register by a value (immediate or from another register).
 *
 * @param instruction Instruction string, e.g., "mul a, b".
 */
void	mul(const char *instruction)
{
	if (!instruction || !*instruction)
		return ;
	char arg1[16] = {0}, arg2[16] = {0};

	sscanf(instruction, "mul %16[^,],%*[, ] %15s", arg1, arg2);
	if (isalpha(arg2[0]))
		registers[arg1[0] - 'a'] *= registers[arg2[0] - 'a'];
	else
		registers[arg1[0] - 'a'] *= atoi(arg2);
}

/**
 * @brief Divides a register by a value (integer division).
 *
 * @param instruction Instruction string, e.g., "div a, b".
 */
void	div_func(const char *instruction)
{
	if (!instruction || !*instruction)
		return ;
	char arg1[16] = {0}, arg2[16] = {0};

	sscanf(instruction, "div %16[^,],%*[, ] %15s", arg1, arg2);
	if (isalpha(arg2[0]))
		registers[arg1[0] - 'a'] /= registers[arg2[0] - 'a'];
	else
		registers[arg1[0] - 'a'] /= atoi(arg2);
}


/**
 * @brief Compares two values (register or immediate) and sets global last_cmp.
 *
 * @param instruction Instruction string, e.g., "cmp a, b".
 */
void	cmp(const char *instruction)
{
	if (!instruction || !*instruction)
	{
		last_cmp = 0;
		return ;
	}
	char arg1[16] = {0}, arg2[16] = {0};

	sscanf(instruction, "cmp %16[^,],%*[, ] %15s", arg1, arg2);
	if (isalpha(arg2[0]))
		last_cmp = (int)registers[arg1[0] - 'a'] - (int)registers[arg2[0] - 'a'];
	else
		last_cmp = (int)registers[arg1[0] - 'a'] - atoi(arg2);
}
