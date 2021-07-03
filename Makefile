VECTOR			=	0
STACK			=	0
MAP				=	1

DEBUG			=	1

NAME			=	containers

ifeq (, $(shell which clang++))
	CC			= g++
else
	CC			= clang++
endif

OBJS			=	$(SRCS:.cpp=.o)
CFLAGS			=	-Wall -Werror -Wextra -g -I./srcs -std=c++98
LDFLAGS			=	-fsanitize=address -fsanitize=leak -g

SRCS_BASENAME	=	main.cpp		\
					rich.cpp		\
					vectors.cpp		\
					stacks.cpp		\
					maps.cpp		\

CFLAGS			+=	-DVECTOR=$(VECTOR)		\
					-DSTACK=$(STACK)		\
					-DMAP=$(MAP)			\
					-DDEBUG=$(DEBUG)		\

ifeq ($(DEBUG), 1)
	ifeq ($(CC), "clang++")
		CFLAGS		+=	-ferror-limit=100
	endif
endif

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
