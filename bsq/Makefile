# Name of your executable
NAME = bsq

# Compiler to use
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g

# Source files
SRCS = bsq.c bsq_functions.c bsq_functions_2.c \
       check_map1.c check_map2.c check_map3.c \
       check_map4.c find_map.c print.c

# Main rule to build your program
$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

# Clean rule to remove object files
clean:
	rm -f *.o

# Full clean rule to remove object files and executable
fclean: clean
	rm -f $(NAME)

# Phony targets
.PHONY: clean fclean
