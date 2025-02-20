# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/23 11:26:43 by jcheron           #+#    #+#              #
#    Updated: 2025/01/21 15:48:35 by jcheron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					:=		libft.a
LIBFT_PATH				:=		libft/
PRINTF_PATH				:=		ft_printf/
GNL_PATH				:=		get_next_line/

CC						:=		gcc
CFLAGS					:=		-Wall -Werror -Wextra

RM						:=		rm -f

FILES					:=									\
					$(PRINTF_PATH)ft_printf.c				\
					$(PRINTF_PATH)printers/ft_print_c.c		\
					$(PRINTF_PATH)printers/ft_print_d.c		\
					$(PRINTF_PATH)printers/ft_print_p.c		\
					$(PRINTF_PATH)printers/ft_print_s.c		\
					$(PRINTF_PATH)printers/ft_print_u.c		\
					$(PRINTF_PATH)printers/ft_print_x.c		\
															\
					$(GNL_PATH)get_next_line.c				\
					$(GNL_PATH)get_next_line_utils.c		\
															\
					$(LIBFT_PATH)ft_is/ft_isalnum.c			\
					$(LIBFT_PATH)ft_is/ft_isalpha.c			\
					$(LIBFT_PATH)ft_is/ft_isascii.c			\
					$(LIBFT_PATH)ft_is/ft_isdigit.c			\
					$(LIBFT_PATH)ft_is/ft_isnumber.c		\
					$(LIBFT_PATH)ft_is/ft_isprint.c			\
					$(LIBFT_PATH)ft_is/ft_iswhitespace.c	\
					$(LIBFT_PATH)ft_lst/ft_lstadd_back.c	\
					$(LIBFT_PATH)ft_lst/ft_lstadd_front.c	\
					$(LIBFT_PATH)ft_lst/ft_lstclear.c		\
					$(LIBFT_PATH)ft_lst/ft_lstdelone.c		\
					$(LIBFT_PATH)ft_lst/ft_lstiter.c		\
					$(LIBFT_PATH)ft_lst/ft_lstmap.c			\
					$(LIBFT_PATH)ft_lst/ft_lstnew.c			\
					$(LIBFT_PATH)ft_lst/ft_lstsize.c		\
					$(LIBFT_PATH)ft_mem/ft_bzero.c			\
					$(LIBFT_PATH)ft_mem/ft_calloc.c			\
					$(LIBFT_PATH)ft_mem/ft_memchr.c			\
					$(LIBFT_PATH)ft_mem/ft_memcpy.c			\
					$(LIBFT_PATH)ft_mem/ft_memcmp.c			\
					$(LIBFT_PATH)ft_mem/ft_memmove.c		\
					$(LIBFT_PATH)ft_mem/ft_memset.c			\
					$(LIBFT_PATH)ft_put/ft_putchar_fd.c		\
					$(LIBFT_PATH)ft_put/ft_putchar.c		\
					$(LIBFT_PATH)ft_put/ft_putendl_fd.c		\
					$(LIBFT_PATH)ft_put/ft_putendl.c		\
					$(LIBFT_PATH)ft_put/ft_putnbr_base.c	\
					$(LIBFT_PATH)ft_put/ft_putnbr_fd.c		\
					$(LIBFT_PATH)ft_put/ft_putnbr.c			\
					$(LIBFT_PATH)ft_put/ft_putstr_fd.c		\
					$(LIBFT_PATH)ft_put/ft_putstr.c			\
					$(LIBFT_PATH)ft_str/ft_split.c			\
					$(LIBFT_PATH)ft_str/ft_strchr.c			\
					$(LIBFT_PATH)ft_str/ft_strdup.c			\
					$(LIBFT_PATH)ft_str/ft_striteri.c		\
					$(LIBFT_PATH)ft_str/ft_strjoin.c		\
					$(LIBFT_PATH)ft_str/ft_strlcat.c		\
					$(LIBFT_PATH)ft_str/ft_strlcpy.c		\
					$(LIBFT_PATH)ft_str/ft_strlen.c			\
					$(LIBFT_PATH)ft_str/ft_strmapi.c		\
					$(LIBFT_PATH)ft_str/ft_strncmp.c		\
					$(LIBFT_PATH)ft_str/ft_strnstr.c		\
					$(LIBFT_PATH)ft_str/ft_strrchr.c		\
					$(LIBFT_PATH)ft_str/ft_strtrim.c		\
					$(LIBFT_PATH)ft_str/ft_substr.c			\
					$(LIBFT_PATH)ft_to/ft_atoi.c			\
					$(LIBFT_PATH)ft_to/ft_itoa.c			\
					$(LIBFT_PATH)ft_to/ft_tolower.c			\
					$(LIBFT_PATH)ft_to/ft_toupper.c

OBJS = ${FILES:%.c=%.o}

all : ${NAME}

$(NAME) : ${OBJS}
		@ar rcs $@ $^

%.o : %.c
		@$(CC) $(CFLAGS) -o $@ -c $<

clean :
		@${RM} ${OBJS}

fclean : clean
		@${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re
















