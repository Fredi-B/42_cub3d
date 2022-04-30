# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 10:45:40 by fbechtol          #+#    #+#              #
#    Updated: 2022/04/30 18:55:56 by fbechtol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# _*_ Makefile _*_

#target: dependencies
#	action

CC = gcc
CFLAGS = -Wall -Wextra -Werror -c
INCLUDES = libft.h get_next_line.h
NAME = libft.a
SOURCES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
	ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	ft_int_strdup.c ft_int_memcpy.c ft_atox.c\
	get_next_line.c get_next_line_utils.c ft_strncmp_backwards.c

BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
	ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJECTS = $(SOURCES:.c=.o)
BONUSOBJECTS = $(BONUS:.c=.o)

#all targets which aren't files
.phony: all clean fclean re bonus

# -c create silently
# -r replace or add and creates if there's no archive
# -s writes / updates object-file index
# $@ = target's name
# ‘$<’ is the first prerequisite <-- doesn't work with the test 
$(NAME): $(OBJECTS)
	ar -crs $@ $(OBJECTS)

bonus: $(NAME) $(BONUSOBJECTS)
	ar -crs $(NAME) $(BONUSOBJECTS)

all: $(NAME) bonus

# -f --> force remove
clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
