//  SPDX-FileCopyrightText: 2023 Andrei Belov <belovsmail@gmail.com>
//  SPDX-License-Identifier: GPL-3.0-or-later

#include "main.h"

void	get_sum(gpointer       data,
				gpointer       user_data)
{
	int			*val = (int *)user_data;
	number_t	*number = (number_t *)data;

	if (number->_is_part_number)
		*val += number->value;
}

int	validate_line(const char *curr_line, size_t len)
{
	game_t			*curr_game;
	static game_t	*prev_game = NULL;
	const char		*curr;
	int 			ret = 0;
	int 			prev = 0;

	if (len == (-3) && prev_game != NULL) {
		g_list_foreach(prev_game->number_list, get_sum, &prev);
		return (prev);
	}
	curr_game = new_game(len);
	if (!curr_game)
		return (-1);
	curr = curr_line;
	while (*curr)
	{
		if (!(*curr == '.' || ft_isdigit(*curr)))
			if (set_symbol(curr_game, prev_game, (curr - curr_line)))
				return (-1);
		curr++;
	}
	curr = curr_line;
	while (*curr)
	{
		if (ft_isdigit(*curr)) {
			if (!create_number(curr_game, prev_game, &curr, curr_line))
				return (0);
			else
				continue ;
		}
		curr++;
	}

	if (prev_game != NULL) {
		g_list_foreach(prev_game->number_list, get_sum, &prev);
		ret = prev;
	} else {
		g_list_foreach(curr_game->number_list, get_sum, &ret);
	}
	prev_game = curr_game;
	return (ret);
}

int	get_answer(FILE *fp)
{
	ssize_t		nread;
	int			d = 0;
	size_t		len = 0;
	char		*line = NULL;

	nread = getline(&line, &len, fp);
	if (nread != -1) {
		line[nread - 1] ='\0';
		validate_line(line, nread - 2);
		nread = getline(&line, &len, fp);
	}
	while (nread != -1)
	{
		line[nread - 1] ='\0';
		d += validate_line(line, nread - 2);
		nread = getline(&line, &len, fp);
	}
	d += validate_line(line, nread - 2);
	free(line);
	return (d);
}

int	main(int argc, char **argv)
{
	FILE	*fp;
	int		argg;
	int 	result;

	argg = 1;
	if (argc < 1)
		return (EX_NOINPUT);
	if (argc > 1)
		while (argg < argc) {
			fp = fopen(argv[argg++], "r");
			result = get_answer(fp);
			fclose(fp);
			ft_printf("Answer is: \"%d\"", result);
		}
	else {
		fp = fopen(INPUT_FILE_NAME, "r");
		result = get_answer(fp);
		fclose(fp);
		ft_printf("Answer is: \"%d\"", result);
	}
	return (EX_OK);
}