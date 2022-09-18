NAMEA = libft.a
##NAMES = libft.so
NAME = main

MAIN = main.c 

PATH_SRC = ./

SRC =	$(PATH_SRC)ft_atoi.c\
		$(PATH_SRC)ft_bzero.c\
		$(PATH_SRC)ft_isalnum.c\
		$(PATH_SRC)ft_isalpha.c\
		$(PATH_SRC)ft_isascii.c\
		$(PATH_SRC)ft_isdigit.c\
		$(PATH_SRC)ft_isprint.c\
		$(PATH_SRC)ft_itoa.c\
		$(PATH_SRC)ft_memalloc.c\
		$(PATH_SRC)ft_memccpy.c\
		$(PATH_SRC)ft_memchr.c\
		$(PATH_SRC)ft_memcmp.c\
		$(PATH_SRC)ft_memcpy.c\
		$(PATH_SRC)ft_memdel.c\
		$(PATH_SRC)ft_memmove.c\
		$(PATH_SRC)ft_memset.c\
		$(PATH_SRC)ft_putchar.c\
		$(PATH_SRC)ft_putchar_fd.c\
		$(PATH_SRC)ft_putendl.c\
		$(PATH_SRC)ft_putendl_fd.c\
		$(PATH_SRC)ft_putnbr.c\
		$(PATH_SRC)ft_putnbr_fd.c\
		$(PATH_SRC)ft_putstr.c\
		$(PATH_SRC)ft_putstr_fd.c\
		$(PATH_SRC)ft_strcat.c\
		$(PATH_SRC)ft_strchr.c\
		$(PATH_SRC)ft_strclr.c\
		$(PATH_SRC)ft_strcmp.c\
		$(PATH_SRC)ft_strncmp.c\
		$(PATH_SRC)ft_strcpy.c\
		$(PATH_SRC)ft_strdel.c\
		$(PATH_SRC)ft_strdup.c\
		$(PATH_SRC)ft_strequ.c\
		$(PATH_SRC)ft_striter.c\
		$(PATH_SRC)ft_striteri.c\
		$(PATH_SRC)ft_strjoin.c\
		$(PATH_SRC)ft_strlcat.c\
		$(PATH_SRC)ft_strlen.c\
		$(PATH_SRC)ft_strmap.c\
		$(PATH_SRC)ft_strmapi.c\
		$(PATH_SRC)ft_strncat.c\
		$(PATH_SRC)ft_strncpy.c\
		$(PATH_SRC)ft_strnequ.c\
		$(PATH_SRC)ft_strnew.c\
		$(PATH_SRC)ft_strnstr.c\
		$(PATH_SRC)ft_strrchr.c\
		$(PATH_SRC)ft_strsplit.c\
		$(PATH_SRC)ft_strstr.c\
		$(PATH_SRC)ft_strsub.c\
		$(PATH_SRC)ft_strtrim.c\
		$(PATH_SRC)ft_tolower.c\
		$(PATH_SRC)ft_toupper.c\
		$(PATH_SRC)ft_lstadd.c\
		$(PATH_SRC)ft_lstdel.c\
		$(PATH_SRC)ft_lstdelone.c\
		$(PATH_SRC)ft_lstiter.c\
		$(PATH_SRC)ft_lstnew.c\
		$(PATH_SRC)ft_lstmap.c\
		$(PATH_SRC)get_next_line.c\
		$(PATH_SRC)ft_strarrdel.c\
		$(PATH_SRC)ft_arrdel.c\
		$(PATH_SRC)ft_intarrnew.c\
		$(PATH_SRC)ft_strnjoin.c\
		$(PATH_SRC)ft_dbarrnew.c\
		$(PATH_SRC)ft_ftarrnew.c\
		$(PATH_SRC)ft_dbarrdel.c\
		$(PATH_SRC)ft_ftarrdel.c

HEADER = libft.h\
	 get_next_line.h

OUTPUT = *.o

all:
	gcc -c $(HEADER) $(SRC) -Wall -Wextra -Werror -iquoteincludes -g
	ar rc $(NAMEA) $(OUTPUT)
#	/bin/rm -f *.o
#	/bin/rm -f *.gch
#so :
#	gcc -shared -o $(NAMES) -fPIC $(SRC)

clean:
	/bin/rm -f *.gch
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAMEA)
#	/bin/rm -f $(NAMES)

re: fclean all

maintest:
	gcc -c $(HEADER) $(SRC) $(MAIN) -Wall -Wextra -Werror -iquoteincludes -g
	gcc -o $(OUTPUT) $(NAME) -Wall -Werror -Wextra
