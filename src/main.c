#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

char* getInput()
{
	char *input = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&input, &len, stdin);

	if (nread == -1) {
		perror("Error reading input");
		return NULL;
	}

//	printf("You entered: %s", input);
	return input;
}

char *trimwhitespace(char *str)
{
	char *end;

	while(isspace((unsigned char)*str)) str++;

	if(*str == 0)
		return str;

	end = str + strlen(str) - 1;
	while(end > str && isspace((unsigned char)*end)) end--;

	end[1] = '\0';

	return str;
}

char** parseInput(char* str)
{
	char *delim = " ";
	char *token;
	char **tokens;
	int i = 0, tokenCount = 0;

	char *strCopy = (char *)malloc(strlen(str) + 1);
	if (strCopy == NULL) {
		printf("Memory allocation failed for strCopy!\n");
		return NULL;
	}
	strcpy(strCopy, str);

	token = strtok(strCopy, delim);
	while (token != NULL) {
		tokenCount++;
		token = strtok(NULL, delim);
	}

	tokens = (char**)malloc(tokenCount * sizeof(char *));
	if (tokens == NULL) {
		printf("Memory allocation failed for tokens array!\n");
		free(strCopy);
		return NULL;
	}

	token = strtok(str, delim);
	while (token != NULL) {
		tokens[i] = token;
		i++;
		token = strtok(NULL, delim);
	}

	free(strCopy);
		
    for (int i = 0; tokens[i] != NULL; i++) {
        printf("arguments[%d]: %s\n", i, tokens[i]);
    }
	return tokens;
}

int main(void)
{
	while (1)
	{
		// read
		char* defaultPrompt = "rsh> ";
		printf("%s", defaultPrompt);

		char* input = trimwhitespace(getInput());

		// parse
		char** arguments = parseInput(input);
		if (arguments == NULL) return 1;
		//int numberOfArguments = sizeof(arguments) / sizeof(*arguments);



		// eval
		//execl("/bin/ls", "ls", (char *)NULL);

		// loop
	}

	return EXIT_SUCCESS;
}
