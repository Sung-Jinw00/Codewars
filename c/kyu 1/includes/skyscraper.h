/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skyscraper.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:34:35 by marvin            #+#    #+#             */
/*   Updated: 2026/01/19 16:01:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKYSCRAPER_H
# define SKYSCRAPER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//─────────────────────────────
// Defines
//─────────────────────────────

# define  N  7
//i'm lazy to write N - 1 for the right position in the array
# define NB(x) (x - 1)

# ifndef RESET
#  define RESET				"\033[0m"
# endif

/* Green text */
# ifndef GREEN
#  define GREEN				"\033[32m"
# endif

//─────────────────────────────
// Global variables
//─────────────────────────────

extern int		nbs_found[2][7];
extern bool	clues_fullfilled[N * 4];

/**
 * @enum Direction
 * @brief Reading directions for the Skyscraper puzzle
 * 
 * LTR = Left To Right
*/
/**
 * RTL = Right To Left
*/
/**
 * BTT = Bottom To Top
*/
/**
 * TTB = Top To Bottom
 */
typedef enum Direction
{
	LTR,	//Left To Right
	RTL,	//Right To Left
	BTT,	//Bottom To Top
	TTB		//Top To Bottom
}	Direction;

//main function
int **SolvePuzzle(int *clues);

//─────────────────────────────
// Backtracking
//─────────────────────────────

void	put_guessable_nbs(int ***available_nbs, int **solution, int *clues);
int		**backtracking_solve(int ***available_nbs, int **solution, int *clues);

//─────────────────────────────
// Backtracking Utils
//─────────────────────────────

void	sol_dup(int sol_save[N][N], int **solution, int dest);
void	set_available_amount(int available_amount[N][N], int ***available_nbs);
void	get_pos_least_amount(int start_line, int start_col, int pos[2], int available_amount[N][N]);

//─────────────────────────────
// Manage possibilities
//─────────────────────────────

void	reduce_possibilities(int ***available_nbs, int **solution, int *clues);

//─────────────────────────────
// Find with rules
//─────────────────────────────

bool	set_one_possibility_rules(int ***available_nbs, int **solution, int *clues);
bool	ascending_rule_works_btt(int *clues, int col, int **solution, int ***available_nbs);
bool	ascending_rule_works_ltr(int *clues, int line, int **solution, int ***available_nbs);
bool	ascending_rule_works_ttb(int *clues, int col, int **solution, int ***available_nbs);
bool	ascending_rule_works_rtl(int *clues, int line, int **solution, int ***available_nbs);
void	all_boxs_empty_ttb(int clue, int col, int **solution, int ***available_nbs, bool lbaf);
void	all_boxs_empty_btt(int clue, int col, int **solution, int ***available_nbs, bool lbaf);
void	all_boxs_empty_ltr(int clue, int line, int **solution, int ***available_nbs, bool lbaf);
void	all_boxs_empty_rtl(int clue, int line, int **solution, int ***available_nbs, bool lbaf);
void	put_ascending_nbs(Direction way, int line, int col, int **solution, int ***available_nbs);

//─────────────────────────────
// Find with clues
//─────────────────────────────

void	remv_before_max_nb(int cur_col_or_line, int ***available_nbs);
void	set_limit_nbs(int nb_clue, int cur_col_or_line, int ***available_nbs);
bool	set_one_possibility_clue(int ***available_nbs, int **solution, int *clues);
void	actualise_max_nb(int cur_col_or_line, int ***available_nbs, int **solution, int *clues);
void	actualise_max_clue(int cur_col_or_line, int ***available_nbs, int **solution, int *clues);
void	clue_2_and_max_nb(int **solution, int ***available_nbs, int clues[N * 4], int pos[2]);
bool	olny_one_possibility_clue(int **solution, int ***available_nbs, int nb, int *ptr_line, int *ptr_col);

//─────────────────────────────
// Actualise solution
//─────────────────────────────

void	actualise_all_column(int nb, int cur_col, int ***available_nbs, int **solution);
void	actualise_all_line(int nb, int cur_line, int ***available_nbs, int **solution);
void	set_valid_pos(int nb, int line, int col, int ***available_nbs, int **solution);

//─────────────────────────────
// Print
//─────────────────────────────

void	print_array(int **array, int nb, int clues[N * 4]);
void	print_all_nb_arrays(int ***available_nbs, int clues[N * 4]);
void	print_all_available_each_box(int ***available_nbs, int clues[N * 4], int **solution);

//─────────────────────────────
// Utils
//─────────────────────────────

int		rev_nb(int pos);
int		left_cond_nb(int line);
int		right_cond_nb(int line);
int		bottom_cond_nb(int col);
int		***init_availability(void);
int		is_nb_on_col(int nb, int col, int **solution);
int		is_nb_on_line(int nb, int line, int **solution);
bool	lacking_towers(Direction way, int line, int col, int **solution);
bool	last_boxs_are_filled(Direction way, int **solution, int line, int col);
int		tiniest_nb_in_box(int ***available_nbs, int start_nb, int line, int col);
bool	last_boxs_arent_filled(Direction way, int **solution, int line, int col);

#endif