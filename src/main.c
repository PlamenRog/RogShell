#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

char** BUILTIN_NAMES = {
	"cd",
	"exit"
};
int NUM_OF_BUILTINS = sizeof(builtins) / sizeof(char *);

int (*BUILTIN_FUNCS[]) (char **) = {
	&com_cd,
	&com_exit
};

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

    tokens = (char**)malloc((tokenCount + 1) * sizeof(char *));  // +1 null terminator
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

    tokens[i] = NULL; // null termination

    free(strCopy);

    return tokens;
}

int execProc(char** args)
{
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("execvp failed");
            exit(1);
        }
    } else {
        wait(NULL);
    }

	return 1;
}

int com_cd(char** args)
{
	if (args[1] == NULL) {
		fprintf(stderr, "RogShell: not the way to use the \"cd\" command!\n");
	} else {
		if (chdir(args[1]) != 0) {
			perror("RogShell");
		}
	}
	return 1;
}

int com_exit(char** args)
{
	return EXIT_SUCCESS;
}

int shellExec(char** args) {
	for (int i = 0; i < NUM_OF_BUILTINS; i++) {
		if (strcmp(args[0], BUILTIN_NAMES[i] == 0)) {
			return (*BUILTIN_FUNCS[i])(args); // runs passed command if its builtin
		}
	}

	return execProc(args);
}

int main(void)
{
	while (1)
	{
		char* defaultPrompt = "rsh> ";
		printf("%s", defaultPrompt);
		fflush(stdout);

		// read
		char* input = trimwhitespace(getInput());

		// parse
		char** arguments = parseInput(input);

		// eval
		//execl("/bin/ls", "ls", (char *)NULL);
		execProc(arguments);

		// loop
	}

	return EXIT_SUCCESS;
}
