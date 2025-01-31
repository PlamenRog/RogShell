#include <stdio.h>
#include <stdlib.h>

char* getInput()
{
	char *input = NULL;
    size_t len = 0;
    ssize_t nread;


    nread = getline(&input, &len, stdin);

    if (nread == -1) {
        perror("Error reading input");
        return "";
    }

//  printf("You entered: %s", input);
	return input;
}

char* parseInput(char* str)
{
    char *delim = " ";
    char *token;
    char **tokens;
    int i = 0, tokenCount = 0;

    char *strCopy = (char *)malloc(strlen(str) + 1);
    if (strCopy == NULL) {
        printf("Memory allocation failed for strCopy!\n");
        return "";
    }
    strcpy(strCopy, str);

    token = strtok(strCopy, delim);
    while (token != NULL) {
        tokenCount++;
        token = strtok(NULL, delim);
    }

    tokens = (char **)malloc(tokenCount * sizeof(char *));
    if (tokens == NULL) {
        printf("Memory allocation failed for tokens array!\n");
        free(strCopy);
        return "";
    }

    token = strtok(str, delim);
    while (token != NULL) {
        tokens[i] = token;
        i++;
        token = strtok(NULL, delim);  // Get the next token
    }

    for (int j = 0; j < tokenCount; j++) {
        printf("tokens[%d]: %s\n", j, tokens[j]);
    }

    free(strCopy);
    free(tokens);
}
/*
int main(void)
{
	while (1)
	{

		char* defaultPrompt = "rsh> ";
		printf("%s", defaultPrompt);
		char* input = getInput();

		execl("/bin/ls", "ls", (char *)NULL);


	    free(input);

	}

	return EXIT_SUCCESS;
}
*/

int main(void)
{
	char input[] = "temporary test string";
	parseInput(input);
	return EXIT_SUCCESS;
}
