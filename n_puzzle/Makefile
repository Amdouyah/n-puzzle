NAME   = npuzzle

CC     = c++
CPPFLAGS = -Wall -Wextra -Werror

SRCS    = srcs/main.cpp \
		  srcs/Puzzle.cpp \

OBJS    = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CPPFLAGS) -o $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re