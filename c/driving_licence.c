#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

/**
 * @brief Convert a 3-letter month abbreviation in a date string to its numeric value.
 * 
 * @param str A date string in the format "DD-MMM-YYYY" (e.g., "30-Nov-2005")
 * @return The month number (1 for Jan, 2 for Feb, ..., 12 for Dec). Returns 0 if invalid.
 */
char get_month(const char *str)
{
	char months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	for (int i = 0; i < 12; i++)
		if (!strncmp(str + 3, months[i], 3)) return i + 1;
	return 0;
}

/**
 * @brief Generate a UK driving license number from personal data.
 * 
 * The function constructs a 16-character license number using the following rules:
 * 
 * - 1–5: The first five characters of the surname, padded with '9' if shorter.
 * 
 * - 6: Decade digit of the birth year (e.g., 1987 → '8').
 * 
 * - 7–8: Birth month, incremented by 50 if the driver is female.
 * 
 * - 9–10: Day of birth (two digits).
 * 
 * - 11: Year digit (last digit of the birth year).
 * 
 * - 12–13: Initials of the first and middle names (padded with '9' if no middle name).
 * 
 * - 14: Arbitrary digit, usually '9' to differentiate drivers with similar preceding characters.
 * 
 * - 15–16: Two computer check digits, fixed as "AA".
 * 
 * @param data Array of 5 strings containing: {
 * data[0]: First name,
 * data[1]: Middle name (can be empty),
 * data[2]: Surname,
 * data[3]: Date of birth in "DD-MMM-YYYY" format,
 * data[4]: Gender ("M" or "F")
 * }
 * 
 * @return a dynamically allocated string containing the 16-character driving license number. The user is responsible for freeing this memory.
 */
char *driver(const char *data[])
{
	int i;
	char *UK_driving_nb = calloc(sizeof(char), 17);

	// 1-5: first 5 letters of last name, uppercase, pad with '9'
	for (i = 0; i < 5; i++)
        UK_driving_nb[i] = data[2][i] ? toupper((unsigned char)data[2][i]) : '9';
	// 6: decade digit from year
	UK_driving_nb[i++] = data[3][strlen(data[3]) - 2];
	// 7-8: month (add 50 if female)
	char month = get_month(data[3]);
	if (!strcmp(data[4], "F"))
		month += 50;
	UK_driving_nb[i++] = month / 10 + 48;
	UK_driving_nb[i++] = month % 10 + 48;
	// 9-10: day
	UK_driving_nb[i++] = data[3][0];
	UK_driving_nb[i++] = data[3][1];
	// 11: year digit
	UK_driving_nb[i++] = data[3][strlen(data[3]) - 1];
	// 12-13: first letters of first and middle name (pad with '9')
	UK_driving_nb[i++] = data[0][0];
	UK_driving_nb[i++] = data[1][0] ? data[1][0] : '9';
	// 14-16: fixed digits
	strncat(UK_driving_nb, "9AA", 3);
    return (UK_driving_nb);
}

int main(void)
{
	const char *data1[]   = {"Romane",    "Danae",  "Metge", "30-Nov-2005",       "F"};
	char *str = NULL;

	str = driver(data1);
	return (printf("plaque de %s : %s\n", data1[0], str));
	free(str);
}

// 1–5: Les cinq premiers caractères du nom de famille (complétés par des 9 s'il y a moins de 5 caractères)

// 6: Le chiffre de la décennie à partir de l'année de naissance (par exemple, pour 1987, ce serait 8)

// 7–8: Le mois de naissance (7e caractère incrémenté de 5 si le conducteur est une femme, c'est-à-dire 51-62 au lieu de 01-12)

// 9–10: La date dans le mois de naissance

// 11: Le chiffre de l'année de naissance (par exemple, pour 1987, ce serait 7)

// 12–13: La lettre initiale du prénom et du deuxième prénom, complétée par un 9 s'il n'y a pas de deuxième prénom

// 14: Chiffre arbitraire – généralement 9, mais décrémenté pour différencier les pilotes ayant les 13 premiers caractères en commun. Nous utiliserons toujours 9.

// 15–16: Deux chiffres de contrôle informatiques. Nous utiliserons toujours « AA ».
