#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

int get_month(const char *str)
{
	if (!strncmp(str + 3, "Jan", 3))
		return (1);
	else if (!strncmp(str + 3, "Feb", 3))
		return (2);
	else if (!strncmp(str + 3, "Mar", 3))
		return (3);
	else if (!strncmp(str + 3, "Apr", 3))
		return (4);
	else if (!strncmp(str + 3, "May", 3))
		return (5);
	else if (!strncmp(str + 3, "Jun", 3))
		return (6);
	else if (!strncmp(str + 3, "Jul", 3))
		return (7);
	else if (!strncmp(str + 3, "Aug", 3))
		return (8);
	else if (!strncmp(str + 3, "Sep", 3))
		return (9);
	else if (!strncmp(str + 3, "Oct", 3))
		return (10);
	else if (!strncmp(str + 3, "Nov", 3))
		return (11);
	else if (!strncmp(str + 3, "Dec", 3))
		return (12);
	return (0);
}


char *driver(const char *data[])
{
	int i = 0;
	char *UK_driving_nb;

	/* 1-5 */
	UK_driving_nb = calloc(sizeof(char), 17);
	strcpy((char *)UK_driving_nb, data[2]);
	while (UK_driving_nb[i] && i < 5)
	{
		UK_driving_nb[i] = (char)toupper((int)UK_driving_nb[i]);
		i++;
	}
	while (i < 5)
		UK_driving_nb[i++] = '9';
	/* 6 */
	UK_driving_nb[i++] = data[3][strlen(data[3]) - 2];
	/* 7-8 */
	int month = get_month(data[3]);
	if (!strcmp(data[4], "F"))
		month += 50;
	if (month < 10)
		UK_driving_nb[i++] = '0';
	else
		UK_driving_nb[i++] = (char)month / 10 + 48;
	UK_driving_nb[i++] = (char)month % 10 + 48;
	/* 9-10 */
	UK_driving_nb[i++] = data[3][0];
	UK_driving_nb[i++] = data[3][1];
	/* 11 */
	UK_driving_nb[i++] = data[3][strlen(data[3]) - 1];
	/* 12-13 */
	UK_driving_nb[i++] = data[0][0];
	if (data[1][0])
		UK_driving_nb[i++] = data[1][0];
	else
		UK_driving_nb[i++] = '9';
	/* 14 */
	UK_driving_nb[i++] = '9';
	/* 15-16 */
	UK_driving_nb[i++] = 'A';
	UK_driving_nb[i++] = 'A';
    return (UK_driving_nb); // return value will be free'd
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
