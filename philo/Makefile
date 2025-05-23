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

NAME = philo

SOURCEDIR := sources
HEADERDIR := include
BUILDDIR  := build
BUILDLOG  := build.log

TESTCASE  := ./$(NAME) 2 1000 200 200 2

# **************************************************************************** #
#    COMMANDS
# **************************************************************************** #

RM          := rm -rf
SCREENCLEAR := printf "\033c"

# **************************************************************************** #
#    COMPILATION
# **************************************************************************** #

CC         := cc
CFLAGS     := -Wall -Werror -Wextra
CPPFLAGS   := -c -MMD -MP
DEBUGFLAGS := -g -fsanitize=address
MAKEFLAGS  += --no-print-directory -j4

# **************************************************************************** #
#    VALGRIND
# **************************************************************************** #

LEAKSLOG := leaks.log
VLGFLAGS := --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --trace-children=yes \
            --verbose \
            --log-file=$(LEAKSLOG)
HELFLAGS := --tool=helgrind \
            --verbose \
            --log-file=$(LEAKSLOG)

# **************************************************************************** #
#    SOURCES
# **************************************************************************** #

SOURCES := main \
           valid \
           init \
           simu \
           routine \
           monitor \
           opmutex \
           opthread \
           optimer \
           getset \
           synchro \
           logger \
           utils

SOURCES := $(addsuffix .c, $(SOURCES))

OBJECTS := $(addprefix $(BUILDDIR)/, $(SOURCES:.c=.o))

INCS := $(addprefix -I, $(HEADERDIR))

DEPS := $(OBJECTS:.o=.d)

vpath %.c $(SOURCEDIR)

# **************************************************************************** #
#    RULES
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCS) $^ -o $@
	printf "$(V)$(B)Binary:$(T)$(Y) $(NAME) $(T)\n"

run: all
	$(SCREENCLEAR)
	$(TESTCASE)

re: fclean
	make all

debug: CFLAGS += $(DEBUGFLAGS)
debug: re

nm:
ifneq ($(shell command -v norminette >/dev/null 2>&1 && echo 1 || echo 0), 1)
	@printf "$(R)$(B)Error: norminette: $(Y)command not found$(T)\n"; exit 1
endif
	$(foreach h, $(HEADERDIR), norminette -R CheckDefine $(h))
	$(foreach s, $(SOURCEDIR), norminette -R CheckForbiddenSourceHeader $(s))

leaks: all
	valgrind $(VLGFLAGS) $(TESTCASE)
	$(call report_cmd, $(LEAKSLOG))

# IMPORTANT! Using 'threads_spinlocked' will freeze race condition test

races: all
	valgrind $(HELFLAGS) $(TESTCASE)
	$(call report_cmd, $(LEAKSLOG))

define report_cmd
	$(SCREENCLEAR)
	sed -n '/ERROR SUMMARY/,$$p' $1 | cut --complement -d' ' -f1
endef

# **************************************************************************** #
#    BUILD
# **************************************************************************** #

define build_cmd
$1/%.o: %.c | $(BUILDDIR)
	if ! $(CC) $(CFLAGS) $(CPPFLAGS) $(INCS) $$< -o $$@ 2> $(BUILDLOG); then \
		printf "$(R)$(B)\nError: \
		$(V)Unable to create object file: \
		$(R)$(B)$$@$(Y)\n\n"; \
		sed '$$d' $(BUILDLOG); exit 1 ; \
	else \
		printf "$(C)$(B)Object: $(G)$$@ $(T)\n"; \
	fi
endef

# **************************************************************************** #
#    CLEAN
# **************************************************************************** #

clean:
	$(call delete_cmd, $(BUILDDIR), $(BUILDLOG), $(LEAKSLOG))

fclean: clean
	$(call delete_cmd, $(NAME), $(BONUSBIN))

define delete_cmd
	printf "$(R)$(B)Delete:$(T)$(Y)$1$2$3$4$5$(T)\n"
	$(RM) $1 $2 $3 $4 $5
endef

# **************************************************************************** #
#    COLORS
# **************************************************************************** #

T = \033[0m
B = \033[1m
G = \033[32m
V = \033[35m
C = \033[36m
Y = \033[33m
R = \033[31m

# **************************************************************************** #
#    UTILS
# **************************************************************************** #

-include $(DEPS)

$(BUILDDIR):
	mkdir -p $@

$(foreach build, $(BUILDDIR), $(eval $(call build_cmd, $(build))))

# **************************************************************************** #
#    PHONY
# **************************************************************************** #

.PHONY: all re run nm
.PHONY: debug leaks
.PHONY: clean fclean

.SILENT:
