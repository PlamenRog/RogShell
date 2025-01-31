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


int main(void)
{

	return EXIT_SUCCESS;
}

