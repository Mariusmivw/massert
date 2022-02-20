# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    utils.mk                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-wij <mvan-wij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/19 10:41:09 by mvan-wij      #+#    #+#                  #
#    Updated: 2022/02/19 11:12:46 by mvan-wij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include colours.mk

################################################################################

# Custom functions

if_eq_test = $(if $(shell echo "$(1) $(2) $(3)" | bc | grep 1), $(4), $(5))

min = $(shell printf "%s\n" $(1) | sort -n | head -1)
max = $(shell printf "%s\n" $(1) | sort -n | tail -1)

print_prefix = printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(PROJECT)]" $(1)

################################################################################

# Handy Variables


ifndef GETTING_RULE_LENGTH

RULE_NAMES += $(shell $(MAKE) --no-print-directory GETTING_RULE_LENGTH=1 list)
RULE_LENGTH	:= $(shell printf "%s\n" $(RULE_NAMES) | awk '{print length}' | sort -n | tail -1)

ifndef RULE_SPACING
RULE_SPACING	:= $(RULE_LENGTH)
else
RULE_SPACING	:= $(call max, $(RULE_LENGTH) $(RULE_SPACING))
endif

endif

PROJECT_LENGTH	:= $(shell printf "[$(PROJECT)]" | wc -c)
ifndef PROJECT_SPACING
PROJECT_SPACING	:= $(PROJECT_LENGTH)
else
PROJECT_SPACING	:= $(call max, $(PROJECT_LENGTH) $(PROJECT_SPACING))
endif

################################################################################

# Handy rules

.PHONY: list

ifndef REAL_RULES
list:
	@cat $(MK_FILE) | egrep -e '^[^#][^:=]*:([^=]|$$)' | egrep -o -e '^[^.][^:]*' | egrep -v -e '[$$%]' | uniq
else
list:
	@LC_ALL=C $(MAKE) -pRrq -f $(MK_FILE) : 2>/dev/null | cat | awk -v RS='\n' -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]|^Makefile:|^.*\.mk") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$' -e '^$$'
endif

################################################################################
