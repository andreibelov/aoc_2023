//  SPDX-FileCopyrightText: 2023 Andrei Belov <belovsmail@gmail.com>
//  SPDX-License-Identifier: GPL-3.0-or-later

#include "main.h"

int get_game_id(char *str)
{
	int			id;
	const char	*prefix = GAME_REFIX;

	if(!str)
		return (-1);
	while (*prefix++ == *str)
		str++;
	id = ft_atoi(str);
	return (id);
}

attempt_t	*new_attempt(char *line)
{
	attempt_t	*game;
	char		*saveptr[4] = {NULL};
	handful_t	*handful;
	char		*colour = NULL;
	char		*try = NULL;
	char		*cubes = NULL;
	char		*set = NULL;
	GList		*subsets = NULL;

	game = (attempt_t *) malloc(sizeof(attempt_t) * 1);
	if (!game)
		return (NULL);
	game->id = get_game_id(strtok_r(line, ":", &saveptr[0]));

	try = strtok_r(NULL, ":", &saveptr[0]);
	set = strtok_r(try, ";", &saveptr[1]);
	while (set) {
		handful = malloc(sizeof(handful_t) * 1);
		if (!handful)
			return (NULL);
		cubes = strtok_r(set, ",", &saveptr[2]);
		while (cubes)
		{
			int num = ft_atoi(strtok_r(cubes, " ", &saveptr[3]));
			colour = strtok_r(NULL, " ", &saveptr[3]);
			if(*colour && handful_setter[*colour])
				handful = handful_setter[*colour](handful, num);
			cubes = strtok_r(NULL, ",", &saveptr[2]);
		}
		subsets = g_list_append(subsets, handful);
		set = strtok_r(NULL, ";", &saveptr[1]);
	}
	game->subsets = subsets;
	return (game);
}

void	validate_handful(gpointer       data,
						 gpointer       user_data)
{
	int			*valid = (int *)user_data;
	handful_t	*handful = (handful_t *)data;
	handful_t	main =  MAIN;
	if (handful->red > main.red
			|| handful->green > main.green
			|| handful->blue > main.blue)
		*valid *= 0;
	else
		*valid *= 1;
}

int	validate_attempt(attempt_t *att)
{
	int valid = 1;
	int ret = 0;
	g_list_foreach(att->subsets, validate_handful, &valid);
	if (valid)
		ret = att->id;
	g_list_free(att->subsets);
	free(att);
	return (ret);
}

void	get_handful_max(gpointer       data,
						gpointer       user_data)
{
	handful_t	*max = (handful_t *)user_data;
	handful_t	*handful = (handful_t *)data;

	if (handful->red > max->red)
		max->red = handful->red;
	if (handful->green > max->green)
		max->green = handful->green;
	if (handful->blue > max->blue)
		max->blue = handful->blue;
}

int	calculate_power(attempt_t *att)
{
	handful_t	max = {0};

	g_list_foreach(att->subsets, get_handful_max, &max);
	g_list_free(att->subsets);
	free(att);
	return (max.red * max.green * max.blue);
}

int	get_answer(FILE *fp)
{
	ssize_t		nread;
	int			d = 0;
	size_t		len = 0;
	char		*line = NULL;

	nread = getline(&line, &len, fp);
	while (nread != -1)
	{
# ifndef PART2
		d += validate_attempt(new_attempt(line));
# else
		d += calculate_power(new_attempt(line));
# endif
		nread = getline(&line, &len, fp);
	}
	free(line);
	return (d);
}

int	main(int argc, char **argv)
{
	FILE	*fp;
	int 	result;
	char	*str = INPUT_FILE_NAME;

	if (argc < 1)
		return (EX_NOINPUT);
	(void) argv;
	fp = fopen(str, "r");
	result = get_answer(fp);
	fclose(fp);
	ft_printf("Answer is: \"%d\"", result);
	return (EX_OK);
}
