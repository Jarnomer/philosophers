# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 12:17:02 by jmertane          #+#    #+#              #
#    Updated: 2024/03/05 14:43:36 by jmertane         ###   ########.fr        #
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
CFLAGS		:=	-Wall -Werror -Wextra -pthread
DEBUGFLAGS	=	-g -fsanitize=thread
DEPFLAGS	=	-c -MT $@ -MMD -MP -MF $(DEPSDIR)$*.d
SCREENCLR	:=	printf "\033c"
SLEEP		:=	sleep .20

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
	@printf "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)\n" && $(SLEEP)
	@printf "$(V)Compiled $(G)$(CNTR)$(V) object file(s).$(T)\n"
	@printf "$(V)Using compiler $(G)$(CC)$(V) with flags: $(G)$(CFLAGS)$(T)\n"
	@printf "$(V)Successfully compiled binary: $(G)$(B)$2$(T)\n"

bonus: $(BONUSFLG)
$(BONUSFLG): $(OBJS_BNS)
	@$(CC) $(CFLAGS) $^ -o $(BONUSDIR)$(BONUSBIN) && touch $@
	@printf "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)\n" && $(SLEEP)
	@printf "$(V)Compiled $(G)$(CNTR)$(V) object file(s).$(T)\n"
	@printf "$(V)Using compiler $(G)$(CC)$(V) with flags: $(G)$(CFLAGS)$(T)\n"
	@printf "$(V)Successfully compiled binary: $(G)$(B)$(BONUSBIN)$(T)\n"

debug: $(DEBUGFLG)
$(DEBUGFLG): $(OBJS_DEBUG)
	@$(CC) $(CFLAGS) $(DEBUGFLAGS) $^ -o $(SRCSDIR)$(DEBUGBIN) && touch $@
	@printf "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)\n" && $(SLEEP)
	@printf "$(V)Compiled $(G)$(CNTR)$(V) object file(s).$(T)\n"
	@printf "$(V)Using compiler $(G)$(CC)$(V) with flags: $(G)$(CFLAGS) $(DEBUGFLAGS)$(T)\n"
	@printf "$(V)Successfully compiled binary: $(G)$(B)$(DEBUGBIN)$(T)\n"

$(OBJSDIR)%.o: %.c | $(OBJSDIR) $(DEPSDIR)
	@if ! $(CC) $(CFLAGS) $(DEPFLAGS) $< -o $@ 2> $(ERRORTXT); then \
		printf "$(R)$(B)\nMAKE TERMINATED!\n$(F)$(T)\n"; \
		printf "$(V)Unable to create object file: $(R)$(B)$@$(T)\n"; \
		printf "$(R)$(B)ERROR\t>>>>>>>>$(T)$(Y)\n"; sed '$$d' $(ERRORTXT); \
		printf "$(R)$(B)\n$(F)\nExiting...$(T)\n"; exit 1 ; fi
	@if [ $(CNTR) ]; then \
		$(eval CNTR=$(shell echo $$(($(CNTR)+1)))) \
		printf "$(T)$(V) $<$(T)\t$(C)>>>>>>>>\t$(G)$(B)$@$(T)"; else \
		printf "$(C)$(B)MAKE START!$(T)\n$(G)$(B)$(F)$(T)\n"; \
		printf "$(T)$(V) $<$(T)\t$(C)>>>>>>>>\t$(G)$(B)$@$(T)"; fi

clean:
	@$(SCREENCLR) && printf "$(C)$(B)\nCLEAN START!\n$(G)$(F)$(T)\n"
	@printf "\n$(V)Removing object and dependency file(s) for $(G)$(B)$(NAME)$(T)\n"
	@$(RM) $(OBJSDIR) $(DEPSDIR) $(ERRORTXT) $(BONUSFLG) $(DEBUGFLG)
	@printf "$(G)$(B)$(F)$(C)\nFINISHED!$(T)\n" && $(SLEEP)

fclean: clean
	@printf "$(C)$(B)\nFCLEAN START!\n$(G)$(F)$(T)\n"
	@printf "$(V)Removing all binary file(s) for $(G)$(B)$(NAME)$(T)"
	@$(RM) $(SRCSDIR)$(NAME) $(BONUSDIR)$(BONUSBIN) $(SRCSDIR)$(DEBUGBIN)
	@printf "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)" && $(SLEEP)

re: fclean all

reb: fclean bonus

nm:
	norminette $(SRCSDIR)$(SRCS)

$(OBJSDIR) $(DEPSDIR):
	@mkdir -p $@/$(SRCSDIR)$(BONUSDIR)

$(DEPS):
	include $(wildcard $(DEPS))

.PHONY: all bonus debug clean fclean re reb
