#include <stdbool.h>
#include <string.h>

bool solution(const char *string, const char *ending)
{
    return (!strcmp(string + (strlen(string) - strlen(ending)), ending));
}

#include <stdio.h>
int main(void)
{
	bool answer = solution("abc", "bc");
	if (answer == true)
		printf("bon\n");
	else
		printf("pas bon\n");
	return (0);
}