//  SPDX-FileCopyrightText: 2023 Andrei Belov <belovsmail@gmail.com>
//  SPDX-License-Identifier: GPL-3.0-or-later

#ifndef AOC_2023_DAY2_GAME_H
#define AOC_2023_DAY2_GAME_H

#include <glib.h>

typedef struct s_handful {
	int red;
	int green;
	int blue;
}				handful_t;

typedef struct s_attempt {
	int		id;
	GList	*subsets;
}				attempt_t;

# ifndef MAIN
#  define MAIN {12, 13, 14}
# endif //MAIN

typedef handful_t	*(*game_dispatch_f)(handful_t *, int);

handful_t	*set_green(handful_t *this, int num);
handful_t	*set_blue(handful_t *this, int num);
handful_t	*set_red(handful_t *this, int num);

static game_dispatch_f const	handful_setter[CHAR_MAX] = {
		['r'] = set_red,
		['g'] = set_green,
		['b'] = set_blue
};

#endif //AOC_2023_DAY2_GAME_H
