# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-wij <mvan-wij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/18 22:34:07 by mvan-wij      #+#    #+#                  #
#    Updated: 2022/03/30 18:07:27 by mvan-wij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

export MK_FILE := $(lastword $(MAKEFILE_LIST))
export RULE_NAMES := "make .o"
export REAL_RULES := 1

export PROJECT	:= massert
NAME			:= libmassert.a

CC		:= gcc
CFLAGS	:=
ifdef DEBUG
CFLAGS	+= -g3
endif

# Common
LIBS	:=
HEADERS	:= ./massert.h
SOURCES	:= src/massert.c

OBJDIR := obj

OBJECTS := $(addprefix $(OBJDIR)/, $(SOURCES:c=o))
INCLUDES := $(sort $(addprefix -I, $(dir $(HEADERS))))

.PHONY: all clean fclean re debug

all: $(NAME)

$(NAME): $(OBJECTS)
# @$(call print_prefix, "make")
	@$(call print_prefix, "$@")
	ar -crs $(NAME) $(OBJECTS)
# @$(call print_prefix, "make")
	@$(call print_prefix, "$@")
	@printf "$(BLUE_FG)$(NAME)$(RESET_COLOR) created\n"

ifndef DEBUG
debug:
	@$(MAKE) --no-print-directory DEBUG=1 $@
else
debug: test
	@$(call print_prefix, "$@")
	@echo ./test "\n"
	@./test
endif

test: $(NAME) src/test.c
# @$(call print_prefix, "debug")
	@$(call print_prefix, "$@")
	$(CC) $(CFLAGS) $(INCLUDES) src/test.c -L. -lmassert -o test
# @$(call print_prefix, "make")
	@$(call print_prefix, "$@")
	@printf "$(BLUE_FG)test$(RESET_COLOR) created\n"

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
# @$(call print_prefix, "make .o")
	@$(call print_prefix, "$@")
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(call print_prefix, "$@")
	rm -rf $(OBJDIR)

fclean: clean
	@$(call print_prefix, "$@")
	rm -f $(NAME)
	@$(call print_prefix, "$@")
	rm -f test

re: fclean all

include utils.mk

# @LC_ALL=C $(MAKE) -pRrq -f $(THIS_FILE) : 2>/dev/null | cat | awk -v RS='\n' -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]|^Makefile:|^.*\.mk") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$' -e '^$$'
