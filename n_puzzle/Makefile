NAME   = npuzzle

CC     = c++
CPPFLAGS = -Wall -Wextra -Werror --std=c++11
# CPPFLAGS = --std=c++11


SRCS    = srcs/main.cpp \
		  srcs/Puzzle.cpp \
		  srcs/Helper.cpp \

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