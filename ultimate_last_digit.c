/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_last_digit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:11:20 by marvin            #+#    #+#             */
/*   Updated: 2025/04/16 14:11:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define ulong unsigned long

ulong mod_pow(ulong base, ulong exp, ulong mod)
{
    ulong result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return (result);
}

int last_digit(const unsigned long int *arr, size_t arr_size)
{
    if (arr_size == 0)
        return (1);

    if (arr_size == 1)
        return (arr[0] % 10);

    ulong exp = arr[arr_size - 1];
    for (int i = (int)arr_size - 2; i >= 1; i--) {
        if (arr[i] == 0 && exp == 0) {
            exp = 1;
        } else {
            exp = mod_pow(arr[i], exp, 20);
            if (exp == 0) {
                exp = 20;
            }
        }
    }
    if (arr[0] == 0 && exp == 0)
        return (1);
    return (mod_pow(arr[0] % 10, exp, 10));
}

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

int main(void)
{
	const ulong *arr[12] = {
		(const ulong[]){},
		(const ulong[]){ 0, 0 },
		(const ulong[]){ 0, 0, 0 },
		(const ulong[]){ 1, 2 },
		(const ulong[]){ 3, 4, 5 },
		(const ulong[]){ 4, 3, 6 },
		(const ulong[]){ 7, 6, 21 },
		(const ulong[]){ 12, 30, 21 },
		(const ulong[]){ 2, 2, 2, 0 },
		(const ulong[]){ 937640, 767456, 981242 },
		(const ulong[]){ 123232, 694022, 140249 },
		(const ulong[]){ 499942, 898102, 846073 }
	};
	size_t arr_sizes[12] = { 0, 2, 3, 2, 3, 3, 3, 3, 4, 3, 3, 3 };
	int expected[12] = { 1, 1, 0, 1, 1, 4, 1, 6, 4, 0, 6, 6 };
	int answer;

	for (int i = 0; i < 11; i++)
	{
		answer = last_digit(arr[i], arr_sizes[i]);
		printf(UNDERLINE BOLD"\n\nTest %d :\n"RESET"answer = %d\n", i + 1, answer);
		if (answer != expected[i])
			printf("\ndifference !\nexpected = %d\n", expected[i]);
		else
			printf("\nno diff, congrats !\n");
	}
	return (0);
}
