NAME	=	Snake

SRC	=	main.cpp			\
		Cdn.cpp				\
		Display.cpp			\
		Map.cpp				\
		Random.cpp			\
		Snake.cpp			\
		SnakeIA.cpp			\
		Logable.cpp

OBJ	=	$(SRC:.cpp=.o)

INCLUDE	=

LIB	=	-lsfml-graphics -lsfml-window -lsfml-system -lmysqlclient

CC	=	g++

CXXFLAGS +=	-Wall -Wextra -Werror
CXXFLAGS +=	-g $(INCLUDE)

LFLAG	+=	$(INCLUDE) $(LIB)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LFLAG) $(INCLUDE)
clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		re clean fclean all
