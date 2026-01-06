#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>

const char *const morse[55] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", ".-.-.-", "--..--", "..--..", ".----.", "-.-.--", "-..-.", "-.--.", "-.--.-", ".-...", "---...", "-.-.-.", "-...-", ".-.-.", "-....-", "..--.-", ".-..-.", "...-..-", ".--.-.", "...---..."};  
const char *const ascii[55] = {"A",  "B",    "C",    "D",   "E", "F",    "G",   "H",    "I",  "J",    "K",   "L",    "M",  "N",  "O",   "P",    "Q",    "R",   "S",   "T", "U",   "V",    "W",   "X",    "Y",    "Z",    "0",     "1",     "2",     "3",     "4",     "5",     "6",     "7",     "8",     "9",     ".",      ",",      "?",      "'",      "!",      "/",     "(",     ")",      "&",     ":",      ";",      "=",     "+",     "-",      "_",      "\"",     "$",       "@",      "SOS"};

char *decode_morse(const char* morse_code) 
{
	char *buf = calloc(strlen(morse_code), 1), *b = buf;
	char *copy = strdup(morse_code), *tok = strtok(copy, " ");
	while (tok)
	{
		for (int i = 0; i < (int)(sizeof(morse) / sizeof(morse[0])); i++)
		{
			if (!strcmp(tok, morse[i]))
			{
				strcpy(b, ascii[i]);
				b += strlen(ascii[i]);
				break;
			}      
		}
		if ((tok = strtok(NULL, " ")) && *(tok - 1) == ' ')
			*b++ = ' '; 
	}
	
	free(copy);
	return buf;
}

#include <stdio.h>

int main(void)
{
	char *decoded = decode_morse("   .... . -.--   .--- ..- -.. .");
	if (decoded)
		printf("message = %s\n", decoded);
	else
		printf("message = NULL\n");
	free(decoded);
	return 0;
}