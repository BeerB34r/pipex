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

.PHONY			:	all clean fclean re clangd
.DEFAULT_GOAL	=	all

MAIN			=	main.c

SRCFILES		=	pipex.c high_tech_plumbing.c toolbox.c
SRCDIR			=	src

OBJFILES		=	$(addprefix $(OBJDIR)/,$(SRCFILES:%.c=%.o))
OBJDIR			=	bin

INCFILES		=	pipex.h libft.h
INCDIR			=	inc libft/include

LIBS			=	libft/libft.a
define libcmd
	@$(MAKE) -C $(1) $(2)
endef

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
VPATH			=	$(SRCDIR) $(INCDIR)
MAKEFLAGS		+=	--output-sync=target --no-print-directory
NAME			=	pipex

all				:	$(NAME)
re				:	fclean all
debug			:	CFLAGS += -g
debug			:	re
$(OBJDIR)		:	; mkdir $@
clangd			:	fclean ; $(shell intercept-build-14 make all)

$(NAME)			:	$(MAIN) $(OBJFILES) $(LIBS) $(INCFILES)
	$(CC) $(CFLAGS) -o $@ $(addprefix -I,$(INCDIR)) $(OBJFILES) $(LIBS) $<

$(OBJDIR)/%.o	:	%.c $(INCFILES) | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $(addprefix -I,$(INCDIR)) $<
%.a				:
	+@$(call libcmd, $(dir $@), all)

clean			:
	rm -rf $(OBJDIR)
	@$(foreach dir,$(dir $(LIBS)),$(call libcmd,$(dir),clean))
fclean			:
	rm -f $(NAME)
	@$(foreach dir,$(dir $(LIBS)),$(call libcmd,$(dir),fclean))
