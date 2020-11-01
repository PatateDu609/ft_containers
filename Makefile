LIST			=	0
MAP				=	1


NAME			=	containers
CC				=	@clang++
OBJS			=	$(SRCS:.cpp=.o)
CFLAGS			=	-Wall -Werror -Wextra -g -I./srcs
LDFLAGS			=	-fsanitize=address -fsanitize=leak -g

SRCS_BASENAME	=	main.cpp		\
					lists.cpp		\
					maps.cpp		\
					rich.cpp		\

CFLAGS			+=	-DLIST=$(LIST)		\
					-DMAP=$(MAP)	\

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
# $(shell pwd | rev | cut -d'/' -f1 | rev)
