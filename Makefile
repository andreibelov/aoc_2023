# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/18 20:29:32 by abelov            #+#    #+#              #
#    Updated: 2023/11/20 15:50:09 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Set some vars for our architecture
uname_s := $(shell uname -s)

ifeq ($(uname_s),Linux)
SHELL := /bin/bash
endif

# the most important line in any shell script (exit on uncaught errors)
SHELL := $(SHELL) -e

## Since we do not actually compile anything, the builtin rules just clutter debugging
MAKEFLAGS += --no-builtin-variables
MAKEFLAGS += --no-builtin-rules

default:: help

.PHONY : help

# Magic help adapted: from https://gitlab.com/depressiveRobot/make-help/blob/master/help.mk (MIT License)
## This help screen
help:
	@printf "Available targets:\n\n"
	@awk -F: '/^[a-zA-Z\-_0-9%\\ ]+:/ { \
			helpMessage = match(lastLine, /^## (.*)/); \
			if (helpMessage) { \
					helpCommand = $$1; \
					helpMessage = substr(lastLine, RSTART + 3, RLENGTH); \
					printf "  \x1b[32;01m%-35s\x1b[0m %s\n", helpCommand, helpMessage; \
			} \
	} \
	{ lastLine = $$0 }' $(MAKEFILE_LIST) | sort -u
	@printf "\n"


## Create a new day from the project_template
new-day%:
	@mkdir day$*
	@rsync -a ./template/ day$*
	@perl -pi -e 's/dayX/day$*/g;' day$*/CMakeLists.txt
	@echo -ne "\nadd_subdirectory(day$*)" >> CMakeLists.txt
	@git add day$*
	@echo "created project \"day$*\""