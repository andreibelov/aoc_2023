//  SPDX-FileCopyrightText: 2023 Andrei Belov <belovsmail@gmail.com>
//  SPDX-License-Identifier: GPL-3.0-or-later

#ifndef AOC_2023_DAY3_GAME_H
#define AOC_2023_DAY3_GAME_H

#include <glib.h>
#include "libft.h"
#include <stdbool.h>

typedef struct s_number {
	int		value;
	bool	_is_part_number;
}				number_t;

typedef struct s_blast {
	ssize_t l;
	ssize_t	r;
}				blast_t;

typedef struct s_game {
	char		*hitmap;
	size_t		len;
	number_t	**numbers;
	GList		*number_list;
}				game_t;

#define min(a, b)	(a) < (b) ? a : b
#define max(a, b)	(a) > (b) ? a : b

game_t		*new_game(size_t len);
number_t	*create_number(game_t *curr_game, game_t *prev_game,
						   char **line, const char *optr);
int			set_symbol(game_t *curr_game, game_t *prev_game, size_t offset);
#endif //AOC_2023_DAY3_GAME_H
