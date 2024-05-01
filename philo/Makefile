# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 12:17:02 by jmertane          #+#    #+#              #
#    Updated: 2024/03/28 19:05:41 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	philo
DEBUGBIN	:=	$(NAME)
OBJSDIR		:=	build/
DEPSDIR		:=	.deps/
ERRORTXT	:=	error.txt
DEBUGFLG	:=	.debug

RM			:=	rm -rf
AR			:=	ar -rcs
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra -pthread
DEBUGFLAGS	=	-g -fsanitize=thread
DEPFLAGS	=	-c -MT $@ -MMD -MP -MF $(DEPSDIR)$*.d
SCREENCLR	:=	printf "\033c"
SLEEP		:=	sleep .1

FILES		:=	main \
				valid \
				init \
				manager \
				routine \
				monitor \
				opmutex \
				opthread \
				optimer \
				getset \
				synchro \
				logger \
				utils

SRCS		:=	$(addsuffix .c, $(FILES))
SRCS_DEBUG	:=	$(SRCS)

OBJS		=	$(patsubst %.c, $(OBJSDIR)%.o, $(SRCS))
OBJS_DEBUG	=	$(patsubst %.c, $(OBJSDIR)%.o, $(SRCS_DEBUG))
DEPS		=	$(patsubst %.c, $(DEPSDIR)%.d, $(SRCS))

F			=	=============================================================
B			=	\033[1m
T			=	\033[0m
G			=	\033[32m
V			=	\033[35m
C			=	\033[36m
R			=	\033[31m
Y			=	\033[33m

all: $(NAME)
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $(NAME)
	@echo "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)\n" && $(SLEEP)
	@echo "$(V)Compiled $(G)$(CNTR)$(V) object file(s).$(T)\n"
	@echo "$(V)Using compiler $(G)$(CC)$(V) with flags: $(G)$(CFLAGS)$(T)\n"
	@echo "$(V)Successfully compiled binary: $(G)$(B)$(NAME)$(T)\n"

debug: $(DEBUGFLG)
$(DEBUGFLG): $(OBJS_DEBUG)
	@$(CC) $(CFLAGS) $(DEBUGFLAGS) $^ -o $(DEBUGBIN) && touch $@
	@echo "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)\n" && $(SLEEP)
	@echo "$(V)Compiled $(G)$(CNTR)$(V) object file(s).$(T)\n"
	@echo "$(V)Using compiler $(G)$(CC)$(V) with flags: $(G)$(CFLAGS) $(DEBUGFLAGS)$(T)\n"
	@echo "$(V)Successfully compiled binary: $(G)$(B)$(DEBUGBIN)$(T)\n"

$(OBJSDIR)%.o: %.c | $(OBJSDIR) $(DEPSDIR)
	@if ! $(CC) $(CFLAGS) $(DEPFLAGS) $< -o $@ 2> $(ERRORTXT); then \
		echo "$(R)$(B)\nMAKE TERMINATED!\n$(F)$(T)\n"; \
		echo "$(V)Unable to create object file: $(R)$(B)$@$(T)\n"; \
		echo "$(R)$(B)ERROR\t>>>>>>>$(T)$(Y)\n"; sed '$$d' $(ERRORTXT); \
		echo "$(R)$(B)\n$(F)\nExiting...$(T)\n"; exit 1 ; fi
	@if [ $(CNTR) ]; then \
		$(eval CNTR=$(shell echo $$(($(CNTR)+1)))) \
		echo "$(T)$(V) $<$(T)   \t $(C)>>>>>>>\t$(G)$(B)$@$(T)"; else \
		echo "$(C)$(B)MAKE START!$(T)\n$(G)$(B)$(F)$(T)\n"; \
		echo "$(T)$(V) $<$(T)   \t $(C)>>>>>>>\t$(G)$(B)$@$(T)"; fi

clean:
	@$(SCREENCLR) && echo "$(C)$(B)\nCLEAN START!\n$(G)$(F)$(T)"
	@echo "$(V)\nRemoving object and dependency file(s) for $(G)$(B)$(NAME)$(T)\n"
	@$(RM) $(OBJSDIR) $(DEPSDIR) $(ERRORTXT) $(BONUSFLG) $(DEBUGFLG)
	@echo "$(G)$(B)$(F)$(C)\nFINISHED!$(T)" && $(SLEEP)

fclean: clean
	@echo "$(C)$(B)\nFCLEAN START!\n$(G)$(F)$(T)"
	@echo "$(V)\nRemoving all binary file(s) for $(G)$(B)$(NAME)$(T)"
	@$(RM) $(NAME) $(DEBUGBIN)
	@echo "$(G)$(B)\n$(F)$(C)\nFINISHED!\n$(T)" && $(SLEEP)

re:
	@make fclean
	@make all

$(OBJSDIR) $(DEPSDIR):
	@mkdir -p $@

$(DEPS):
	include $(wildcard $(DEPS))

.PHONY: all debug clean fclean re
