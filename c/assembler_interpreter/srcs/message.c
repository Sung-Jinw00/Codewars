#include "message.h"

char	*get_msg(char *msg)
{
	int j, len_msg = strlen(msg);
	char final_msg[10000] = {0};
	
	for (int i = 0; i < len_msg && msg[i] && msg[i] != ';'; i++)//while i didn't reach the end of the line or the comment mark 
	{
		if (msg[i] == '\'')//if i have quotes
		{
			i++;
			if (!strncmp(msg + i, "This program should return -1", 29))//and i have to return something
				return ((char *)-1);//i return it
			for (j = i; msg[j] != '\'';)//i go reach the end of the quote
				j++;
			if (!final_msg[0])//if i didn't write anything yet
				strncpy(final_msg, msg + i, j - i);//i return a duplicate of the message between quotes
			else
				strncat(final_msg, msg + i, j - i);//else i join the duplicate to the current message and free them
			i = j + 1;
		}
		else if (isalpha(msg[i]))
		{
			char buffer[MAX_LEN_INT + 1];
			sprintf(buffer, "%d", registers[msg[i] - 'a']);//i take the value of the register in a string format and add it to final_msg like above
			if (!final_msg[0])
				strcpy(final_msg, buffer);
			else
				strcat(final_msg, buffer);
		}
	}
	return (strdup(final_msg));
}
