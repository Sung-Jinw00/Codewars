/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skyscraper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2025/05/02 01:43:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define  TAB_SIZE  7
#define NB(x) (x - 1)

int	nbs_found[2][7] = {
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0}
};

int	rev_pos(int pos)
{
	return (TAB_SIZE - pos - 1);
}

void	print_array(int **array, int nb, int clues[TAB_SIZE * 4])
{
	if (!array || !array[0])
	{
		printf("array of %d's :\n", nb + 1);
		printf("(null)\n");
		return ;
	}
	//print wrapper_array
	printf("array of %d's :\n", nb + 1);
	printf("\n   ");
	for(int j = 0; j < TAB_SIZE; j++)
	{
		if (clues[j])
			printf(" %d  ", clues[j]);
		else
			printf("    ");
		
	}
	printf("\n");
	printf("  ─────────────────────────────\n");
	for (int i = TAB_SIZE - 1; i >= 0; i--)
	{
		if (clues[TAB_SIZE * 3 + i])
			printf("%d ", clues[TAB_SIZE * 3 + i]);
		else
			printf("  ");
		printf("|");
		for(int j = 0; j < TAB_SIZE; j++)
		{
			if (array[(rev_pos(i))][j])
				printf(" %d |", array[(rev_pos(i))][j]);
			else
				printf("   |");
		}
		if (clues[TAB_SIZE + (rev_pos(i))])
		printf(" %d", clues[TAB_SIZE + (rev_pos(i))]);
		else
			printf("  ");
		printf("\n  ─────────────────────────────\n");
	}
	printf("   ");
	for(int j = TAB_SIZE - 1; j >= 0; j--)
	{
		if (clues[TAB_SIZE * 2 + j])
			printf(" %d  ", clues[TAB_SIZE * 2 + j]);
		else
			printf("    ");
		
	}
	printf("\n");
}

void	print_all_nb_arrays(int ***available_nbs, int clues[TAB_SIZE * 4])
{
	for (int nb = 0; nb < TAB_SIZE; nb++)
		print_array(available_nbs[nb], nb, clues);
}

//─────────────────────────────
// Actualise pos
//─────────────────────────────

void	actualise_valid_pos(int nb, int line, int col, int ***available_nbs, int **solution)
{
	for (int col_inc = 0; col_inc < TAB_SIZE; col_inc++)//set every other box on the same line to zero
	{
		if (col_inc != col)
			available_nbs[nb][line][col_inc] = 0;
	}
	for (int line_inc = 0; line_inc < TAB_SIZE; line_inc++)//set every other boxs on the same col to zero
	{
		if (line_inc != line)
			available_nbs[nb][line_inc][col] = 0;
	}
	for (int nb_inc = 0; nb_inc < TAB_SIZE; nb_inc++)//set every other numbers at this position invalid
	{
		if (nb_inc != nb)
			available_nbs[nb_inc][line][col] = 0;
	}
	solution[line][col] = nb + 1;
	nbs_found[0][line]++;
	nbs_found[1][col]++;
}

void	clue_2_and_max_nb(int **solution, int ***available_nbs, int clues[TAB_SIZE * 4], int pos[2])
{
	if (!((pos[0] == 0 || pos[0] == TAB_SIZE - 1) && (pos[1] == 0 || pos[1] == TAB_SIZE - 1)
		&& solution[pos[0]][pos[1]] == TAB_SIZE))
		return ;
	if (pos[0] == 0 && clues[TAB_SIZE * 2 + rev_pos(pos[1])] == 2)
		actualise_valid_pos(NB(TAB_SIZE - 1), TAB_SIZE - 1, pos[1], available_nbs, solution);
	else if (pos[0] == TAB_SIZE - 1 && clues[rev_pos(pos[1])] == 2)
		actualise_valid_pos(NB(TAB_SIZE - 1),  0, pos[1],available_nbs, solution);
	else if (pos[1] == 0 && clues[TAB_SIZE + rev_pos(pos[0])] == 2)
		actualise_valid_pos(NB(TAB_SIZE - 1), pos[0], TAB_SIZE - 1, available_nbs, solution);
	else if (pos[1] == TAB_SIZE - 1 && clues[TAB_SIZE * 3 + rev_pos(pos[0])] == 2)
		actualise_valid_pos(NB(TAB_SIZE - 1), pos[0], 0, available_nbs, solution);
}

/* actualise lines from up to bottom and set the solution */
void	actualise_all_lines(int nb, int cur_col, int ***available_nbs, int **solution)
{
	if (nb == TAB_SIZE - 1)//if the max towers was on the bottom
	{
		for (int line = 0; line < TAB_SIZE; line++)
		{
			actualise_valid_pos(nb, line, cur_col, available_nbs, solution);
			nb--;
		}
	}
	else if (nb == 0)
	{
		for (int line = 0; line < TAB_SIZE; line++)
		{
			actualise_valid_pos(nb, line, cur_col, available_nbs, solution);
			nb++;
		}
	}
}

/* actualise columns from left to right and set the solution */
void	actualise_all_cols(int nb, int cur_line, int ***available_nbs, int **solution)
{
	if (nb == TAB_SIZE - 1)//if the max towers was on the right
	{
		for (int col = 0; col < TAB_SIZE; col++)
		{
			actualise_valid_pos(nb, cur_line, col, available_nbs, solution);
			nb--;
		}
	}
	else if (nb == 0)
	{
		for (int col = 0; col < TAB_SIZE; col++)
		{
			actualise_valid_pos(nb, cur_line, col, available_nbs, solution);
			nb++;
		}
	}
}

void	remv_before_max_nb(int cur_col_or_line, int ***available_nbs, int **solution)
{
	if (cur_col_or_line < TAB_SIZE)//if it's from the upper clues
		actualise_valid_pos(NB(TAB_SIZE - 1), 1, cur_col_or_line, available_nbs, solution);
	else if (cur_col_or_line < TAB_SIZE * 2)//if it's from the right clues
	{
		cur_col_or_line -= TAB_SIZE - 1;
		actualise_valid_pos(NB(TAB_SIZE), cur_col_or_line, 1, available_nbs, solution);
	}
	else if (cur_col_or_line < TAB_SIZE * 3)//if it's from the lower clues
	{
		cur_col_or_line = TAB_SIZE - (cur_col_or_line - (TAB_SIZE * 2)) - 1;
		actualise_valid_pos(NB(TAB_SIZE), 1, cur_col_or_line, available_nbs, solution);
	}
	else//if it's from the left clues
	{
		cur_col_or_line = TAB_SIZE - (cur_col_or_line - (TAB_SIZE * 3)) - 1;
		actualise_valid_pos(NB(TAB_SIZE), cur_col_or_line, 1, available_nbs, solution);
	}
}

void	actualise_max_clue(int cur_col_or_line, int ***available_nbs, int **solution, int *clues)
{
	if (cur_col_or_line < TAB_SIZE)//if it's from the upper clues
	{
		actualise_all_lines(NB(1), cur_col_or_line, available_nbs, solution);
		clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){0, cur_col_or_line});
	}
	else if (cur_col_or_line < TAB_SIZE * 2)//if it's from the right clues
	{
		cur_col_or_line -= TAB_SIZE;
		actualise_all_cols(NB(7), cur_col_or_line, available_nbs, solution);
		clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){cur_col_or_line, 0});
	}
	else if (cur_col_or_line < TAB_SIZE * 3)//if it's from the lower clues
	{
		cur_col_or_line = TAB_SIZE - (cur_col_or_line - (TAB_SIZE * 2));
		actualise_all_lines(NB(7), cur_col_or_line, available_nbs, solution);
		clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){0, cur_col_or_line});
	}
	else//if it's from the left clues
	{
		cur_col_or_line = TAB_SIZE - (cur_col_or_line - (TAB_SIZE * 3));
		actualise_all_cols(NB(1), cur_col_or_line, available_nbs, solution);
		clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){cur_col_or_line, 0});
	}
}

void	actualise_max_nb(int cur_col_or_line, int ***available_nbs, int **solution, int *clues)
{
	if (cur_col_or_line < TAB_SIZE)//if it's from the upper clues
	{
		actualise_valid_pos(NB(TAB_SIZE), 0, cur_col_or_line, available_nbs, solution);
		clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){0, cur_col_or_line});
	}
	else if (cur_col_or_line < TAB_SIZE * 2)//if it's from the right clues
	{
		cur_col_or_line -= TAB_SIZE - 1;
		actualise_valid_pos(NB(TAB_SIZE), cur_col_or_line, 0, available_nbs, solution);
		clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){cur_col_or_line, 0});
	}
	else if (cur_col_or_line < TAB_SIZE * 3)//if it's from the lower clues
	{
		cur_col_or_line = TAB_SIZE - (cur_col_or_line - (TAB_SIZE * 2)) - 1;
		actualise_valid_pos(NB(TAB_SIZE), 0, cur_col_or_line, available_nbs, solution);
		clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){0, cur_col_or_line});
	}
	else//if it's from the left clues
	{
		cur_col_or_line = TAB_SIZE - (cur_col_or_line - (TAB_SIZE * 3)) - 1;
		actualise_valid_pos(NB(TAB_SIZE), cur_col_or_line, 0, available_nbs, solution);
		clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){cur_col_or_line, 0});
	}
}
/* set the limit on all numbers depending on their distance with the clue border */
void	set_limit_nbs(int nb_clue, int cur_col_or_line, int ***available_nbs)
{
	int	max_limit = (TAB_SIZE - nb_clue) + 1;// no tower can be above this limit or it will 100% hide more towers than wanted

	if (cur_col_or_line < TAB_SIZE)//if it's from the upper clues
	{
		for (int i = 0; i < nb_clue; i++)//we put the limit until nb_clue boxes, then you can have whatever value you want, it can work
		{
			for (int nb = max_limit; nb < TAB_SIZE; nb++)
				available_nbs[nb][i][cur_col_or_line] = 0;
			max_limit++;//the more we step away from the border, the higher the limit is, in the ascending logic
		}
	}
	else if (cur_col_or_line < TAB_SIZE * 2)//if it's from the right clues
	{
		cur_col_or_line -= TAB_SIZE;
		for (int i = TAB_SIZE - 1; i > rev_pos(nb_clue); i--)
		{
			for (int nb = max_limit; nb < TAB_SIZE; nb++)
				available_nbs[nb][cur_col_or_line][i] = 0;
			max_limit++;//the more we step away from the border, the higher the limit is, in the ascending logic
		}
	}
	else if (cur_col_or_line < TAB_SIZE * 3)//if it's from the lower clues
	{
		cur_col_or_line = TAB_SIZE - (cur_col_or_line - (TAB_SIZE * 2)) - 1;
		for (int i = TAB_SIZE - 1; i > rev_pos(nb_clue); i--)
		{
			for (int nb = max_limit; nb < TAB_SIZE; nb++)
				available_nbs[nb][i][cur_col_or_line] = 0;
			max_limit++;//the more we step away from the border, the higher the limit is, in the ascending logic
		}
	}
	else//if it's from the left clues
	{
		cur_col_or_line = TAB_SIZE - (cur_col_or_line - (TAB_SIZE * 3)) - 1;
		for (int i = 0; i < nb_clue; i++)
		{
			for (int nb = max_limit; nb < TAB_SIZE; nb++)
				available_nbs[nb][cur_col_or_line][i] = 0;
			max_limit++;//the more we step away from the border, the higher the limit is, in the ascending logic
		}
	}
}

bool	only_one_possibility(int **solution, int ***available_nbs, int nb, int *ptr_line, int *ptr_col)
{
	int	count = 0;
	int	dup_line = *ptr_line, dup_col = *ptr_col;

	if (nbs_found[0][dup_line] != TAB_SIZE)
	{
		for (int col = 0; col < TAB_SIZE; col++)
		{
			if (available_nbs[nb][dup_line][col] != 0 && !solution[dup_line][col])
			{
				*ptr_col = col;
				count++;
			}
		}
		if (count == 1)
			return (true);
		*ptr_col = dup_col;
		count = 0;
	}
	if (nbs_found[1][dup_col] != TAB_SIZE)
	{
		for (int line = 0; line < TAB_SIZE; line++)
		{
			if (available_nbs[nb][line][dup_col] != 0 && !solution[line][dup_col])
			{
				*ptr_line = line;
				count++;
			}
		}
		if (count == 1)
			return (true);
		*ptr_line = dup_line;
	}
	return (false);
}

/* look in diagonal if one line or column has only one possility for a number and set it in answer tab */
bool	set_one_possibility(int ***available_nbs, int **solution, int *clues)
{
	bool changes = false;
	int line, col, actual_check;

	for (line = 0, col = 0; line < TAB_SIZE; line++, col++)
	{
		actual_check = line;
		for (int nb = 0; nb < TAB_SIZE; nb++)
		{
			if (only_one_possibility(solution, available_nbs, nb, &line, &col))
			{
				actualise_valid_pos(nb, line, col, available_nbs, solution);
				clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){line, col});
				changes = true;
				break;
			}
		}
		col = line = actual_check;
	}
	return (changes);
}

void	set_guessable_nbs(int ***available_nbs, int **solution, int *clues)
{
	for (int i = 0; i < TAB_SIZE * 4; i++)//while i didn't checked all clues
	{
		if (clues[i] != 0)//if a clue is different than zero
		{
			if (clues[i] == TAB_SIZE)//if clue = max nb
				actualise_max_clue(i, available_nbs, solution, clues);//i put the line
			else if (clues[i] == 1)//else if clue = 1
				actualise_max_nb(i, available_nbs, solution, clues);//i put max nb
			// else if (clues[i] == 2)//else if clue = 2
			// 	remv_before_max_nb(i, available_nbs, solution);//i put max nb
			set_limit_nbs(clues[i], i, available_nbs);//i set limits for nbs
		}
	}
	for (bool changes = true; changes != false;)
		changes = set_one_possibility(available_nbs, solution, clues);
}

int	***init_availability(void)
{
	int ***available_nbs = malloc(sizeof(int **) * TAB_SIZE);

	for (int i = 0; i < TAB_SIZE; i++)
	{
		available_nbs[i] = malloc(sizeof(int *) * TAB_SIZE);
		for (int j = 0; j < TAB_SIZE; j++)
		{
			available_nbs[i][j] = malloc(sizeof(int) * TAB_SIZE);
			for (int k = 0; k < TAB_SIZE; k++)
				available_nbs[i][j][k] = i + 1;
		}
	}
	return (available_nbs);
}

//─────────────────────────────
// Main Exercice
//─────────────────────────────

int **SolvePuzzle(int *clues)
{
	if (!clues)
		return (NULL);
	int ***available_nbs = init_availability();
	int **solution = calloc(sizeof(int *), TAB_SIZE);
	for (int i = 0; i < TAB_SIZE; i++)
		solution[i] = calloc(sizeof(int), TAB_SIZE);
	set_guessable_nbs(available_nbs, solution, clues);
	//print_all_nb_arrays(available_nbs, clues);
	return (solution);
}

//─────────────────────────────
// Main Utils
//─────────────────────────────

#include <stdio.h>

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

/* Red text */
# ifndef RED
#  define RED				"\033[31m"
# endif

/* Green text */
# ifndef GREEN
#  define GREEN				"\033[32m"
# endif

/* Cyan text */
# ifndef CYAN
#  define CYAN				"\033[36m"
# endif

void	print_answer(int **array, int **wrapper_array, int clues[TAB_SIZE * 4])
{
	if (!array || !array[0])
	{
		printf("(null)\n");
		return ;
	}
	//print wrapper_array
	/* printf(CYAN UNDERLINE"should be :\n"RESET);
	printf("\n   ");
	for(int j = 0; j < TAB_SIZE; j++)
	{
		if (clues[j])
			printf(" %d  ", clues[j]);
		else
			printf("    ");
		
	}
	printf("\n");
	printf("  ─────────────────────────────\n");
	for (int i = TAB_SIZE - 1; i >= 0; i--)
	{
		if (clues[TAB_SIZE * 3 + i])
			printf("%d ", clues[TAB_SIZE * 3 + i]);
		else
			printf("  ");
		printf("|");
		for(int j = 0; j < TAB_SIZE; j++)
			printf(" %d |", wrapper_array[rev_pos(i)][j]);
		if (clues[TAB_SIZE + (rev_pos(i))])
		printf(" %d", clues[TAB_SIZE + (rev_pos(i))]);
		else
			printf("  ");
		printf("\n  ─────────────────────────────\n");
	}
	printf("   ");
	for(int j = TAB_SIZE - 1; j >= 0; j--)
	{
		if (clues[TAB_SIZE * 2 + j])
			printf(" %d  ", clues[TAB_SIZE * 2 + j]);
		else
			printf("    ");
		
	}
	printf("\n"); */
	//print array
	printf(CYAN UNDERLINE"\ngot :\n"RESET);
	printf("\n   ");
	for(int j = 0; j < TAB_SIZE; j++)
	{
		if (clues[j])
			printf(" %d  ", clues[j]);
		else
			printf("    ");
		
	}
	printf("\n");
	printf("  ─────────────────────────────\n");
	for (int i = TAB_SIZE - 1; i >= 0; i--)
	{
		if (clues[TAB_SIZE * 3 + i])
			printf("%d ", clues[TAB_SIZE * 3 + i]);
		else
			printf("  ");
		printf("|");
		for(int j = 0; j < TAB_SIZE; j++)
		{
			if (array[rev_pos(i)][j] == wrapper_array[rev_pos(i)][j])
				printf(" "GREEN"%d"RESET" |", array[rev_pos(i)][j]);
			else
				printf(" "RED"%d"RESET" |", array[rev_pos(i)][j]);
			
		}
		if (clues[TAB_SIZE + (rev_pos(i))])
		printf(" %d", clues[TAB_SIZE + (rev_pos(i))]);
		else
			printf("  ");
		printf("\n  ─────────────────────────────\n");
	}
	printf("   ");
	for(int j = TAB_SIZE - 1; j >= 0; j--)
	{
		if (clues[TAB_SIZE * 2 + j])
			printf(" %d  ", clues[TAB_SIZE * 2 + j]);
		else
			printf("    ");
		
	}
	printf("\n");
}

//wrapper
int	**wrapped_array(int static_array[TAB_SIZE][TAB_SIZE])
{
	static int *rows[TAB_SIZE];
	for (int i = 0; i < TAB_SIZE; i++)
		rows[i] = static_array[i];
	return (rows);
}

void	print_indices(int clues[TAB_SIZE * 4])
{
	printf("\n   ");
	for(int j = 0; j < TAB_SIZE; j++)
	{
		if (clues[j])
			printf(" %d  ", clues[j]);
		else
			printf("    ");
		
	}
	printf("\n");
	printf("  ─────────────────────────────\n");
	for (int i = TAB_SIZE - 1; i >= 0; i--)
	{
		if (clues[TAB_SIZE * 3 + i])
			printf("%d ", clues[TAB_SIZE * 3 + i]);
		else
			printf("  ");
		printf("|");
		for(int j = 0; j < TAB_SIZE; j++)
			printf("   |");
		if (clues[TAB_SIZE + (rev_pos(i))])
		printf(" %d", clues[TAB_SIZE + (rev_pos(i))]);
		else
			printf("  ");
		printf("\n  ─────────────────────────────\n");
	}
	printf("   ");
	for(int j = TAB_SIZE - 1; j >= 0; j--)
	{
		if (clues[TAB_SIZE * 2 + j])
			printf(" %d  ", clues[TAB_SIZE * 2 + j]);
		else
			printf("    ");
		
	}
	printf("\n");
}

void	free_array(int **result)
{
	for (int i = 0; i < TAB_SIZE; i++)
		free(result[i]);
	free(result);
}

//─────────────────────────────
// Main
//─────────────────────────────

int main(void)
{
	static int clues[][TAB_SIZE * 4] = {
	  { 7, 0, 0, 0, 2, 2, 3,
		0, 0, 3, 0, 0, 0, 0,
		3, 0, 3, 0, 0, 5, 0,
		0, 0, 0, 0, 5, 0, 4 },
	  { 0, 2, 3, 0, 2, 0, 0,
		5, 0, 4, 5, 0, 4, 0,
		0, 4, 2, 0, 0, 0, 6,
		5, 2, 2, 2, 2, 4, 1 }
	};
	
	static int expected[][TAB_SIZE][TAB_SIZE] = {
		{{ 1, 5, 6, 7, 4, 3, 2 },
		 { 2, 7, 4, 5, 3, 1, 6 },
		 { 3, 4, 5, 6, 7, 2, 1 },
		 { 4, 6, 3, 1, 2, 7, 5 },
		 { 5, 3, 1, 2, 6, 4, 7 },
		 { 6, 2, 7, 3, 1, 5, 4 },
		 { 7, 1, 2, 4, 5, 6, 3 }},
		{{ 7, 6, 2, 1, 5, 4, 3 },
		 { 1, 3, 5, 4, 2, 7, 6 },
		 { 6, 5, 4, 7, 3, 2, 1 },
		 { 5, 1, 7, 6, 4, 3, 2 },
		 { 4, 2, 1, 3, 7, 6, 5 },
		 { 3, 7, 6, 2, 1, 5, 4 },
		 { 2, 4, 3, 5, 6, 1, 7 }}
	};
	int diff = 0;

	for (int i = 0; i < 2; i++)
	{
		int **result = SolvePuzzle(clues[i]);
		printf(CYAN UNDERLINE BOLD"Test %d :\n"RESET, i);
		for (int j = 0; j < TAB_SIZE; j++)
		{
			if (!result || memcmp(result, expected[i], TAB_SIZE * sizeof(int)))
			{
				diff = 1;
				printf(RED "diff !\n"/* CYAN UNDERLINE"result of :" */RESET);
				/* print_indices(clues[i]); */
				print_answer(result, wrapped_array(expected[i]), clues[i]);
				printf(RESET);
				break ;
			}
		}
		if (!diff)
			printf(GREEN"no diff !"CYAN" congrats !\n"RESET);
		printf("\n\n");
		diff = 0;
		free_array(result);
	}
	return (0);
}
