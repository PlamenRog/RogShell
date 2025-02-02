CFLAGS = -Wextra -Wall -Werror -pedantic

install:
	gcc ./src/main.c -o rsh $(CFLAGS)
