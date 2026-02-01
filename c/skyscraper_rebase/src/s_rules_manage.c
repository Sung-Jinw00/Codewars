#include "skyscraper.h"

//─────────────────────────────
// Find with rules
//─────────────────────────────

/**
 * @brief
 * Fill empty boxes from Left To Right with remaining numbers
 * in ascending order when the rule conditions are met.
 *
 * This function is called when the number of remaining values
 * equals (clue - 1) or when the last boxes are already filled.
 *
 * @param clue            The clue associated with the line (visible towers)
 * @param line            The line index being processed
 * @param solution        The current solution grid
 * @param available_nbs   The table of available numbers per cell
 * @param lbaf            True if last boxes are already filled
 */
void	all_boxs_empty_ltr(int clue, int line, int **solution, int ***available_nbs, bool lbaf)
{
	int	remaining_nb[N] = {0};
	int remaining_nbs = N;

	//list all numbers
	for (int i = 0; i < N; i++)
		remaining_nb[i] = i + 1;
	//get remaining nbs
	for (int col = 0; col < N; col++)
	{
		if (solution[line][col])
		{
			remaining_nb[NB(solution[line][col])] = 0;
			remaining_nbs--;
		}
	}
	//if i have clue - 1 numbers left or if last boxes are filled
	if (remaining_nbs == clue - 1 || lbaf)
	{
		int i = 0;
		for (int col = 0; !solution[line][col]; col++)
		{
			//i put numbers in ascending order
			while (i < N && !remaining_nb[i])
				i++;
			//fprintf(stderr, "LTR all box empty ascending nb on line %d = %d\n", line, remaining_nb[i]);
			set_valid_pos(NB(remaining_nb[i]), line, col, available_nbs, solution);
			i++;
		}
		//clue is fullfilled
		clues_fullfilled[line] = true;
	}
}

/**
 * @brief
 * Check whether the ascending rule is valid on a line
 * when read from Left To Right.
 *
 * It validates spacing between existing numbers according
 * to the clue and ensures an ascending sequence is possible.
 *
 * @param clues           The full array of clues
 * @param line            The line index to check
 * @param solution        The current solution grid
 * @param available_nbs   The table of available numbers per cell
 *
 * @return true if the ascending rule is valid, false otherwise
 */

bool	ascending_rule_works_ltr(int *clues, int line, int **solution, int ***available_nbs)
{
	int	clue = clues[left_cond_nb(line)], prev_nb, col = 0, next_nb, empty_boxs;
	bool lbaf = false;
	int res;

	//return false if there's no clue or N is further than clue
	if (!clue || ((res = is_nb_on_line(N, line, solution)) != -1 && res + 1 < clue))
		return (false);
	//goes to the first existing number
	while (!solution[line][col] && col < N)
		col++;
	if (col == N)
		return (false);
	//return false if the number is N or last boxes are filled
	if (solution[line][col] == N || (lbaf = last_boxs_are_filled(LTR, solution, line, col)))
		return (all_boxs_empty_ltr(clue, line, solution, available_nbs, lbaf), false);
	prev_nb = solution[line][col];
	while (solution[line][col] != N)
	{
		if (!solution[line][col])
		{
			empty_boxs = 1;
			while (!solution[line][col + empty_boxs])
			{
				if (!available_nbs[NB(prev_nb + empty_boxs)][line][col + empty_boxs])//check that numbers can be placed
					return (false);
				empty_boxs++;
			}
			next_nb = solution[line][col + empty_boxs];
			if (empty_boxs != (next_nb - prev_nb - 1))
				return (false);
			col += empty_boxs;
		}
		prev_nb = solution[line][col];
		if (solution[line][col] != N)
			col++;
	}
	clues_fullfilled[line] = true;
	return (true);
}

/**
 * @brief
 * Check whether the ascending rule is valid on a line
 * when read from Top To Bottom.
 *
 * It validates spacing between existing numbers according
 * to the clue and ensures an ascending sequence is possible.
 *
 * @param clues           The full array of clues
 * @param line            The line index to check
 * @param solution        The current solution grid
 * @param available_nbs   The table of available numbers per cell
 *
 * @return true if the ascending rule is valid, false otherwise
 */
void	all_boxs_empty_ttb(int clue, int col, int **solution, int ***available_nbs, bool lbaf)
{
	int	remaining_nb[N] = {0};
	int remaining_nbs = N;

	for (int i = 0; i < N; i++)
		remaining_nb[i] = i + 1;
	for (int line = 0; line < N; line++)
	{
		if (solution[line][col])
		{
			remaining_nb[NB(solution[line][col])] = 0;
			remaining_nbs--;
		}
	}
	if (remaining_nbs == clue - 1 || lbaf)
	{
		int i = 0;
		for (int line = 0; !solution[line][col]; line++)
		{
			while (i < N && !remaining_nb[i])
				i++;
			//fprintf(stderr, "TTB all box empty ascending nb on column %d = %d\n", col, remaining_nb[i]);
			set_valid_pos(NB(remaining_nb[i]), line, col, available_nbs, solution);
			i++;
		}
		clues_fullfilled[col] = true;
	}
}

/**
 * @brief
 * Check if i can put numbers in ascending order, and do it if it's possible
 * 
 * @param clues			the array of clues
 * @param col			the column i should check on
 * @param solution		the solution board
 * @param available_nbs	the array of possible numbers
 * 
 * @return `true` if it works, `false` if it doesn't work
 */
bool	ascending_rule_works_ttb(int *clues, int col, int **solution, int ***available_nbs)
{
	int	clue = clues[col], prev_nb, line = 0, next_nb, empty_boxs;
	bool lbaf = false;
	int res;

	if (!clue || ((res = rev_nb(is_nb_on_col(N, col, solution))) != -1 && res + 1 < clue))
		return (false);
	while (!solution[line][col])
		line++;
	if (solution[line][col] == N || (lbaf = last_boxs_are_filled(TTB, solution, line, col)))
		return (all_boxs_empty_ttb(clue, col, solution, available_nbs, lbaf), false);
	prev_nb = solution[line][col];
	while (solution[line][col] != N)
	{
		if (!solution[line][col])
		{
			empty_boxs = 1;
			while (!solution[line + empty_boxs][col])
			{
				//fprintf(stderr, "is %d available on solution[%d][%d] ?\n%s\n", prev_nb + empty_boxs, line + empty_boxs, col, available_nbs[NB(prev_nb + empty_boxs)][line + empty_boxs][col] ? "yes" : "no");
				if (!available_nbs[NB(prev_nb + empty_boxs)][line + empty_boxs][col])//check that numbers can be placed
					return (false);
				empty_boxs++;
			}
			next_nb = solution[line + empty_boxs][col];
			if (empty_boxs != (next_nb - prev_nb - 1))
				return (false);
			line += empty_boxs;
		}
		prev_nb = solution[line][col];
		if (solution[line][col] != N)
			line++;
	}
	clues_fullfilled[col] = true;
	return (true);
}

/**
 * @brief
 * Fill empty boxes from Bottom To Top with remaining numbers
 * in ascending order when rule conditions are satisfied.
 *
 * @param clue            The clue associated with the column
 * @param col             The column index being processed
 * @param solution        The current solution grid
 * @param available_nbs   The table of available numbers per cell
 * @param lbaf            True if last boxes are already filled
 */
void	all_boxs_empty_btt(int clue, int col, int **solution, int ***available_nbs, bool lbaf)
{
	int	remaining_nb[N] = {0};
	int remaining_nbs = N;

	for (int i = 0; i < N; i++)
		remaining_nb[i] = i + 1;
	for (int line = N - 1; line >= 0; line--)
	{
		if (solution[line][col])
		{
			remaining_nb[NB(solution[line][col])] = 0;
			remaining_nbs--;
		}
	}
	if (remaining_nbs == clue - 1 || lbaf)
	{
		int i = 0;
		for (int line = N - 1; !solution[line][col]; line--)
		{
			while (i < N && !remaining_nb[i])
				i++;
			//fprintf(stderr, "BTT all box empty ascending nb on column %d = %d\n", col, remaining_nb[i]);
			set_valid_pos(NB(remaining_nb[i]), line, col, available_nbs, solution);
			i++;
		}
		clues_fullfilled[col] = true;
	}
}

/**
 * @brief
 * Check if i can put numbers in ascending order, and do it if it's possible
 * 
 * @param clues			the array of clues
 * @param col			the column i should check on
 * @param solution		the solution board
 * @param available_nbs	the array of possible numbers
 * 
 * @return `true` if it works, `false` if it doesn't work
 */
bool	ascending_rule_works_btt(int *clues, int col, int **solution, int ***available_nbs)
{
	int	clue = clues[bottom_cond_nb(col)], prev_nb, line = N - 1, next_nb, empty_boxs;
	bool lbaf = false;
	int res;

	if (!clue || ((res = rev_nb(is_nb_on_col(N, col, solution))) != -1 && res + 1 < clue))
		return (false);
	while (!solution[line][col])
		line--;
	if (solution[line][col] == N || (lbaf = last_boxs_are_filled(BTT, solution, line, col)))
		return (all_boxs_empty_btt(clue, col, solution, available_nbs, lbaf), false);
	prev_nb = solution[line][col];
	while (solution[line][col] != N)
	{
		if (!solution[line][col])
		{
			empty_boxs = 1;
			while (!solution[line - empty_boxs][col])
			{
				if (!available_nbs[NB(prev_nb + empty_boxs)][line - empty_boxs][col])//check that numbers can be placed
					return (false);
				empty_boxs++;
			}
			next_nb = solution[line - empty_boxs][col];
			if (empty_boxs != (next_nb - prev_nb - 1))
				return (false);
			line -= empty_boxs;
		}
		prev_nb = solution[line][col];
		if (solution[line][col] != N)
			line--;
	}
	clues_fullfilled[col] = true;
	return (true);
}

/**
 * @brief
 * Fill empty boxes from Right To Left with remaining numbers
 * in ascending order when rule conditions are satisfied.
 *
 * @param clue            The clue associated with the line
 * @param line            The line index being processed
 * @param solution        The current solution grid
 * @param available_nbs   The table of available numbers per cell
 * @param lbaf            True if last boxes are already filled
 */
void	all_boxs_empty_rtl(int clue, int line, int **solution, int ***available_nbs, bool lbaf)
{
	int	remaining_nb[N] = {0};
	int remaining_nbs = N;

	for (int i = 0; i < N; i++)
		remaining_nb[i] = i + 1;
	for (int col = N - 1; col >= 0; col--)
	{
		if (solution[line][col])
		{
			remaining_nb[NB(solution[line][col])] = 0;
			remaining_nbs--;
		}
	}
	if (remaining_nbs == clue - 1 || lbaf)
	{
		int i = 0;
		for (int col = N - 1; !solution[line][col]; col--)
		{
			while (i < N && !remaining_nb[i])
				i++;
			//fprintf(stderr, "RTL all box empty ascending nb on line %d = %d\n", line, remaining_nb[i]);
			set_valid_pos(NB(remaining_nb[i]), line, col, available_nbs, solution);
			i++;
		}
		clues_fullfilled[line] = true;
	}
}

/**
 * @brief
 * Check if i can put numbers in ascending order, and do it if it's possible
 * 
 * @param clues			the array of clues
 * @param line			the line i should check on
 * @param solution		the solution board
 * @param available_nbs	the array of possible numbers
 * 
 * @return `true` if it works, `false` if it doesn't work
 */
bool	ascending_rule_works_rtl(int *clues, int line, int **solution, int ***available_nbs)
{
	int clue = clues[right_cond_nb(line)], prev_nb, col = N - 1, next_nb, empty_boxs;
	bool lbaf = false;
	int res;

	if (!clue || ((res = rev_nb(is_nb_on_line(N, line, solution))) != -1 && res + 1 < clue))
		return (false);
	while (!solution[line][col])
		col--;
	if (solution[line][col] == N || (lbaf = last_boxs_are_filled(RTL, solution, line, col)))
		return (all_boxs_empty_rtl(clue, line, solution, available_nbs, lbaf), false);
	prev_nb = solution[line][col];
	while (solution[line][col] != N)
	{
		if (!solution[line][col])
		{
			empty_boxs = 1;
			while (!solution[line][col - empty_boxs])
			{
				if (!available_nbs[NB(prev_nb + empty_boxs)][line][col - empty_boxs])//check that numbers can be placed
					return (false);
				empty_boxs++;
			}
			next_nb = solution[line][col - empty_boxs];
			if (empty_boxs != (next_nb - prev_nb - 1))
				return (false);
			col -= empty_boxs;
		}
		prev_nb = solution[line][col];
		if (solution[line][col] != N)
			col--;
	}
	clues_fullfilled[line] = true;
	return (true);
}

/**
 * @brief
 * Put numbers in ascending order
 * 
 * @param way		The reading way, of type @ref Direction
 * @param line			the line i should check on, depending on `way`
 * @param col			the column i should check on, depending on `way`
 * @param solution		the solution board
 * @param available_nbs	the array of possible numbers
 */
void	put_ascending_nbs(Direction way, int line, int col, int **solution, int ***available_nbs)
{
	int inc_col, inc_line = 0;

	if (way == LTR)
	{
		inc_col = 0;
		while (!solution[line][inc_col])
			inc_col++;
		while (solution[line][inc_col] != N)
		{
			while (solution[line][inc_col] && solution[line][inc_col] != N)
				inc_col++;
			while (!solution[line][inc_col])
			{
				//fprintf(stderr, "LTR ascending nb on line %d = %d\n", line, solution[line][inc_col - 1] + 1);
				set_valid_pos(NB(solution[line][inc_col - 1] + 1), line, inc_col, available_nbs, solution);
				inc_col++;
			}
		}
		clues_fullfilled[left_cond_nb(line)] = true;
	}
	else if (way == RTL)
	{
		inc_col = N - 1;
		while (!solution[line][inc_col])
			inc_col--;
		while (solution[line][inc_col] != N)
		{
			while (solution[line][inc_col] && solution[line][inc_col] != N)
				inc_col--;
			while (!solution[line][inc_col])
			{
				//fprintf(stderr, "RTL ascending nb on line %d = %d\n", line, solution[line][inc_col + 1] + 1);
				set_valid_pos(NB(solution[line][inc_col + 1] + 1), line, inc_col, available_nbs, solution);
				inc_col--;
			}
		}
		clues_fullfilled[right_cond_nb(line)] = true;
	}
	else if (way == TTB)
	{
		inc_line = 0;
		while (!solution[inc_line][col])
			inc_line++;
		while (solution[inc_line][col] != N)
		{
			while (solution[inc_line][col] && solution[inc_line][col] != N)
				inc_line++;
			while (!solution[inc_line][col])
			{
				//fprintf(stderr, "TTB ascending nb on column %d = %d\n", col, solution[inc_line - 1][col] + 1);
				set_valid_pos(NB(solution[inc_line - 1][col] + 1), inc_line, col, available_nbs, solution);
				inc_line++;
			}
		}
		clues_fullfilled[bottom_cond_nb(col)] = true;
	}
	else
	{
		inc_line = N - 1;
		while (!solution[inc_line][col])
			inc_line--;
		while (solution[inc_line][col] != N)
		{
			while (solution[inc_line][col] && solution[inc_line][col] != N)
				inc_line--;
			while (!solution[inc_line][col])
			{
				//fprintf(stderr, "BTT ascending nb on column %d = %d\n", col, solution[inc_line + 1][col] + 1);
				set_valid_pos(NB(solution[inc_line + 1][col] + 1), inc_line, col, available_nbs, solution);
				inc_line--;
			}
		}
		clues_fullfilled[col] = true;
	}
}

/**
 * @brief
 * Put numbers in ascending order
 * 
 * @param way		The reading way, of type @ref Direction
 * @param line			the line i should check on, depending on `way`
 * @param col			the column i should check on, depending on `way`
 * @param solution		the solution board
 * @param available_nbs	the array of possible numbers
 */
void	put_ascending_possibilities(Direction way, int line, int col, int **solution, int ***available_nbs)
{
	int inc_col = 0, inc_line = 0;

	if (way == LTR)
	{
		inc_col = 0;
		while (solution[line][inc_col] != N)
		{
			while (solution[line][inc_col] && solution[line][inc_col] != N)
				inc_col++;
			while (!solution[line][inc_col])
			{
				int nb = min_possibility(available_nbs, line, inc_col);
				//fprintf(stderr, "LTR min_possibility on line %d = %d\n", line, nb);
				if (nb >= 0)
					set_valid_pos(NB(nb), line, inc_col, available_nbs, solution);
				inc_col++;
			}
		}
		clues_fullfilled[left_cond_nb(line)] = true;
	}
	else if (way == RTL)
	{
		inc_col = N - 1;
		while (solution[line][inc_col] != N)
		{
			while (solution[line][inc_col] && solution[line][inc_col] != N)
				inc_col--;
			while (!solution[line][inc_col])
			{
				int nb = min_possibility(available_nbs, line, inc_col);
				//fprintf(stderr, "RTL min_possibility on line %d = %d\n", line, nb);
				if (nb >= 0)
					set_valid_pos(NB(nb), line, inc_col, available_nbs, solution);
				inc_col--;
			}
		}
		clues_fullfilled[right_cond_nb(line)] = true;
	}
	else if (way == TTB)
	{
		while (solution[inc_line][col] != N)
		{
			while (solution[inc_line][col] && solution[inc_line][col] != N)
				inc_line++;
			while (!solution[inc_line][col])
			{
				int nb = min_possibility(available_nbs, inc_line, col);
				//fprintf(stderr, "TTB min_possibility on column %d = %d\n", col, nb);
				if (nb >= 0)
					set_valid_pos(NB(nb), inc_line, col, available_nbs, solution);
				inc_line++;
			}
		}
		clues_fullfilled[bottom_cond_nb(col)] = true;
	}
	else
	{
		inc_line = N - 1;
		while (solution[inc_line][col] != N)
		{
			while (solution[inc_line][col] && solution[inc_line][col] != N)
				inc_line--;
			while (!solution[inc_line][col])
			{
				int nb = min_possibility(available_nbs, inc_line, col);
				//fprintf(stderr, "BTT min_possibility on column %d = %d\n", col, nb);
				if (nb >= 0)
					set_valid_pos(NB(nb), inc_line, col, available_nbs, solution);
				inc_line--;
			}
		}
		clues_fullfilled[col] = true;
	}
}

/**
 * @brief
 * Check if a number is only in one box on a line or column and assign it if it exist
 * 
 * @param available_nbs	the array of possible numbers
 * @param line			the current line
 * @param col			the current column
 * @param solution		the solution board
 */
void	nb_in_one_box(int ***available_nbs, int line, int col, int **solution, bool *changes)
{
	int count = 0, inc_line, inc_col;

	for (int nb = NB(1); nb < N; nb++)
	{
		for (inc_line = 0; inc_line < N; inc_line++)
			if (available_nbs[nb][inc_line][col] && !solution[inc_line][col])
				count++;
		if (count == 1)
		{
			for (inc_line = 0; !available_nbs[nb][inc_line][col];)
				inc_line++;
			//fprintf(stderr, "only nb on solution[%d][%d] = %d\n", inc_line, col, nb + 1);
			set_valid_pos(nb, inc_line, col, available_nbs, solution);
			*changes = true;
			return ;
		}
		count = 0;
		for (int inc_col = 0; inc_col < N; inc_col++)
			if (available_nbs[nb][line][inc_col] && !solution[line][inc_col])
				count++;
		if (count == 1)
		{
			for (inc_col = 0; !available_nbs[nb][line][inc_col];)
				inc_col++;
			//fprintf(stderr, "only nb on solution[%d][%d] = %d\n", line, inc_col, nb + 1);
			set_valid_pos(nb, line, inc_col, available_nbs, solution);
			*changes = true;
			return ;
		}
		count = 0;
	}
}

/**
 * @brief
 * Look in diagonal if one line or column has only one possility for a number and set it in answer tab
 * 
 * @param available_nbs	the array of possible numbers
 * @param solution		the solution board
 * @param clues			the array of clues
 */
bool	set_one_possibility_rules(int ***available_nbs, int **solution, int *clues)
{
	bool changes = false;
	int line, col;

	for (line = 0, col = 0; line < N; line++, col++)
	{
		//if there's numbers to find in the current line and N is on the line
		if (nbs_found[0][line] != N && is_nb_on_line(N, line, solution) != -1)
		{
			//if the clue is not fullfilled on the left, towers missing and i can put ascending order, i put it
			if (!clues_fullfilled[left_cond_nb(line)] && lacking_towers(LTR, line, col, solution)
				&& ascending_rule_works_ltr(clues, line, solution, available_nbs))
				put_ascending_nbs(LTR, line, col, solution, available_nbs), changes = true;
			//if the clue is not fullfilled on the right, towers missing and i can put ascending order, i put it
			if (!clues_fullfilled[right_cond_nb(line)] && lacking_towers(RTL, line, col, solution)
				&& ascending_rule_works_rtl(clues, line, solution, available_nbs))
				put_ascending_nbs(RTL, line, col, solution, available_nbs), changes = true;
		}
		if (nbs_found[1][col] != N && is_nb_on_col(N, col, solution) != -1)
		{
			//if the clue is not fullfilled at the bottom, towers missing and i can put ascending order, i put it
			if (!clues_fullfilled[bottom_cond_nb(col)] && lacking_towers(BTT, line, col, solution)
				&& ascending_rule_works_btt(clues, col, solution, available_nbs))
				put_ascending_nbs(BTT, line, col, solution, available_nbs), changes = true;
			//if the clue is not fullfilled on the top, towers missing and i can put ascending order, i put it
			if (!clues_fullfilled[col] && lacking_towers(TTB, line, col, solution)
				&& ascending_rule_works_ttb(clues, col, solution, available_nbs))
				put_ascending_nbs(TTB, line, col, solution, available_nbs), changes = true;
		}
		nb_in_one_box(available_nbs, line, col, solution, &changes);
	}
	return (changes);
}
