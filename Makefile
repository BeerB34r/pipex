# **************************************************************************** #
#                                                                              #
#                                                        ::::::::              #
#    Makefile                                          :+:    :+:              #
#                                                     +:+                      #
#    By: mde-beer <mde-beer@student.codam.nl>        +#+                       #
#                                                   +#+                        #
#    Created: 2025/01/21 17:01:56 by mde-beer     #+#    #+#                   #
#    Updated: 2025/01/21 17:26:27 by mde-beer     ########   odam.nl           #
#                                                                              #
# **************************************************************************** #

.PHONY			:	all clean fclean re
.DEFAULT_GOAL	=	all

MAIN			=	main.c
SRCFILES		=	pipex.c high_tech_plumbing.c
SRCDIR			=	src
OBJFILES		=	$(SRCFILES:%.c=%.o)
OBJDIR			=	bin
INCFILES		=	pipex.h libft.h
INCDIR			=	inc libft/include
LIBS			=	libft/libft.a
define libcmd
make -C $(1) $(2)
endef

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
MAKEFLAGS		+=	-j$(shell nproc) --output-sync=target --no-print-directory
NAME			=	pipex

all				:	$(NAME)
re				:	fclean all

$(NAME)			:	$(SRCFILES) $(LIBS) $(INCFILES)
	$(CC) $(CFLAGS) -o $@ $(addprefix -I,$(INCDIR)) $(OBJFILES) $(LIBS)
