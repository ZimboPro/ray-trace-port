# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/24 09:53:07 by lde-jage          #+#    #+#              #
#    Updated: 2017/09/19 10:43:23 by syoung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

HDR = libft/*.h\
	  includes/*.h

SRC = srcs/*.c

FLAGS = -Werror -Wall -Wextra -iquoteincludes -iquotelibft -g -g3

LIB = -L libft/ -lft -lm 

OT = *.o

ifeq ($(shell uname -s), Darwin)
SYS = OSX
else
SYS = LINUX
endif

ifeq ($(SYS), OSX)
SDL = -F /Library/Frameworks -framework SDL2
else
SDL = -lSDL2
endif

$(NAME): all

all: 
	make -C libft/
	clang -c $(HDR) $(SRC) $(FLAGS)
	clang -o $(NAME) $(OT) $(SDL) $(LIB) $(FLAGS)

clean:
	/bin/rm -f $(OT)
	/bin/rm -f *.gch
	/bin/rm -f includes/*.gch

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
