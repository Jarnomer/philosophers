# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 12:17:02 by jmertane          #+#    #+#              #
#    Updated: 2024/02/25 20:50:23 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	philo
BONUSBIN	:=	$(NAME)
DEBUGBIN	:=	$(NAME)
EMPTY		:=	${null}
SRCSDIR		:=	philo/
OBJSDIR		:=	build/
DEPSDIR		:=	.deps/
BONUSDIR	:=	philo_bonus/
ERRORTXT	:=	error.txt
BONUSEXT	:=	_bonus
BONUSFLG	:=	.bonus
DEBUGFLG	:=	.debug

RM			:=	rm -rf
AR			:=	ar -rcs
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra -pthread -g
DEBUGFLAGS	=	-g -fsanitize=address
DEPFLAGS	=	-c -MT $@ -MMD -MP -MF $(DEPSDIR)$*.d
SCREENCLR	:=	printf "\033c"
SLEEP		:=	sleep .20

FILES		:=	main \
				valid \
				init \
				manager \
				monitor \
				mutexop \
				threadop \
				synchro \
				mutacc \
				timer \
				logger \
				error

BONUS		:=	$(EMPTY)

HEADERS		:=	philo

SRCS		:=	$(addsuffix .c, $(FILES))
SRCS		+=	$(addsuffix .h, $(HEADERS))
SRCS		:=	$(addprefix $(SRCSDIR), $(SRCS))
SRCS_BNS	:=	$(addsuffix $(BONUSEXT).c, $(FILES) $(BONUS))
SRCS_BNS	+=	$(addsuffix $(BONUSEXT).h, $(HEADERS))
SRCS_BNS	:=	$(addprefix $(BONUSDIR), $(SRCS_BNS))
SRCS_DEBUG	:=	$(SRCS)

OBJS		=	$(patsubst %.c, $(OBJSDIR)%.o, $(SRCS))
OBJS_BNS	=	$(patsubst %.c, $(OBJSDIR)%.o, $(SRCS_BNS))
OBJS_DEBUG	=	$(patsubst %.c, $(OBJSDIR)%.o, $(SRCS_DEBUG))
DEPS		=	$(patsubst %.c, $(DEPSDIR)%.d, $(SRCS) $(SRCS_BNS))

F			=	=================================================
B			=	\033[1m		# bold
T			=	\033[0m		# reset
G			=	\033[32m	# green
V			=	\033[35m	# violet
C			=	\033[36m	# cyan
R			=	\033[31m	# red
Y			=	\033[33m	# yellow

all: $(NAME)
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $(SRCSDIR)$@
	@echo "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)\n" && $(SLEEP)
	@echo "$(V)Compiled $(G)$(CNTR)$(V) object file(s).$(T)\n"
	@echo "$(V)Using compiler $(G)$(CC)$(V) with flags: $(G)$(CFLAGS)$(T)\n"
	@echo "$(V)Successfully compiled binary: $(G)$(B)$2$(T)\n"

bonus: $(BONUSFLG)
$(BONUSFLG): $(OBJS_BNS)
	@$(CC) $(CFLAGS) $^ -o $(BONUSDIR)$(BONUSBIN) && touch $@
	@echo "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)\n" && $(SLEEP)
	@echo "$(V)Compiled $(G)$(CNTR)$(V) object file(s).$(T)\n"
	@echo "$(V)Using compiler $(G)$(CC)$(V) with flags: $(G)$(CFLAGS)$(T)\n"
	@echo "$(V)Successfully compiled binary: $(G)$(B)$(BONUSBIN)$(T)\n"

debug: $(DEBUGFLG)
$(DEBUGFLG): $(OBJS_DEBUG)
	@$(CC) $(CFLAGS) $(DEBUGFLAGS) $^ -o $(SRCSDIR)$(DEBUGBIN) && touch $@
	@echo "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)\n" && $(SLEEP)
	@echo "$(V)Compiled $(G)$(CNTR)$(V) object file(s).$(T)\n"
	@echo "$(V)Using compiler $(G)$(CC)$(V) with flags: $(G)$(CFLAGS) $(DEBUGFLAGS)$(T)\n"
	@echo "$(V)Successfully compiled binary: $(G)$(B)$(DEBUGBIN)$(T)\n"

$(OBJSDIR)%.o: %.c | $(OBJSDIR) $(DEPSDIR)
	@if ! $(CC) $(CFLAGS) $(DEPFLAGS) $< -o $@ 2> $(ERRORTXT); then \
		echo "$(R)$(B)\nMAKE TERMINATED!\n$(F)$(T)\n"; \
		echo "$(V)Unable to create object file: $(R)$(B)$@$(T)\n"; \
		echo "$(R)$(B)ERROR\t>>>>>>>>$(T)$(Y)\n"; sed '$$d' $(ERRORTXT); \
		echo "$(R)$(B)\n$(F)\nExiting...$(T)\n"; exit 1 ; fi
	@if [ $(CNTR) ]; then \
		$(eval CNTR=$(shell echo $$(($(CNTR)+1)))) \
		echo "$(T)$(V) $<$(T)\t$(C)>>>>>>>>\t$(G)$(B)$@$(T)"; else \
		echo "$(C)$(B)MAKE START!$(T)\n$(G)$(B)$(F)$(T)\n"; \
		echo "$(T)$(V) $<$(T)\t$(C)>>>>>>>>\t$(G)$(B)$@$(T)"; fi

clean:
	@$(SCREENCLR) && echo "$(C)$(B)\nCLEAN START!\n$(G)$(F)$(T)\n"
	@echo "\n$(V)Removing object and dependency file(s) for $(G)$(B)$(NAME)$(T)\n"
	@$(RM) $(OBJSDIR) $(DEPSDIR) $(ERRORTXT) $(BONUSFLG) $(DEBUGFLG)
	@echo "$(G)$(B)$(F)$(C)\nFINISHED!$(T)\n" && $(SLEEP)

fclean: clean
	@echo "$(C)$(B)\nFCLEAN START!\n$(G)$(F)$(T)\n"
	@echo "$(V)Removing all binary file(s) for $(G)$(B)$(NAME)$(T)"
	@$(RM) $(SRCSDIR)$(NAME) $(BONUSDIR)$(BONUSBIN) $(SRCSDIR)$(DEBUGBIN)
	@echo "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)" && $(SLEEP)

re: fclean all

reb: fclean bonus

$(OBJSDIR) $(DEPSDIR):
	@mkdir -p $@/$(SRCSDIR)$(BONUSDIR)

$(DEPS):
	include $(wildcard $(DEPS))

.PHONY: all bonus debug clean fclean re reb
