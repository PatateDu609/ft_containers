LIST			=	0
VECTOR			=	0
STACK			=	0
QUEUE			=	0
MAP				=	1

DEBUG			=	0

NAME			=	containers
CC				=	@clang++
OBJS			=	$(SRCS:.cpp=.o)
CFLAGS			=	-Wall -Werror -Wextra -g -I./srcs -std=c++98
LDFLAGS			=	-fsanitize=address -fsanitize=leak -g

SRCS_BASENAME	=	main.cpp		\
					rich.cpp		\
					lists.cpp		\
					vectors.cpp		\
					stacks.cpp		\
					queues.cpp		\
					maps.cpp		\

CFLAGS			+=	-DLIST=$(LIST)			\
					-DVECTOR=$(VECTOR)		\
					-DQUEUE=$(QUEUE)		\
					-DSTACK=$(STACK)		\
					-DMAP=$(MAP)			\
					-DDEBUG=$(DEBUG)		\

SRCS			=	$(addprefix tests/, $(SRCS_BASENAME))

%.o:			%.cpp
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS)
				$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)
				@echo "\033[31;1mCompilation done\033[0m"
				@./$(NAME)

all:			$(NAME)

clean:
				@rm -f $(OBJS)

fclean:			clean
				@rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
