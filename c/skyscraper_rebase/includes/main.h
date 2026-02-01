#ifndef MAIN_H
# define MAIN_H

#include "skyscraper.h"
#include <string.h>

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

//main
int		main(void);

//utils

void	free_array(int **result);
void	print_indices(int clues[N * 4]);
int		**wrapped_array(int static_array[N][N]);
void	print_answer(int **array, int **wrapper_array, int clues[N * 4]);

#endif