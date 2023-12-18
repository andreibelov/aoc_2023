/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 07:32:06 by abelov            #+#    #+#             */
/*   Updated: 2023/12/18 07:32:09 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int set_symbol(game_t *curr_game, game_t *prev_game, size_t offset)
{
	blast_t b;
	number_t *number;

	if (!curr_game)
		return (-1);
	b.l = max((long long)(offset - 1), 0);
	b.r = min((offset + 1), curr_game->len);
	curr_game->hitmap[offset] = '1';

	if (prev_game) {
		if (number = prev_game->numbers[b.l])
			number->_is_part_number = true;
		if (prev_game->numbers[offset])
			prev_game->numbers[offset]->_is_part_number = true;
		if (prev_game->numbers[b.r])
			prev_game->numbers[b.r]->_is_part_number = true;
	}
	return (0);
}

number_t	*new_number(int digit)
{
	number_t	*number;

	number = (number_t *) malloc(sizeof(number_t) * 1);
	if (!number)
		return NULL;
	number->value = digit;
	number->_is_part_number = false;
	return (number);
}

number_t	*create_number(game_t *curr_game, game_t *prev_game,
						   char **line, const char *optr)
{
	int			digit;
	size_t		len = 0;
	number_t	*number;
	size_t		offset;
	blast_t		b;

	if (!curr_game)
		return (-1);
	if (!line)
		return NULL;

	digit = ft_atoi(*line);
	number = new_number(digit);
	offset = (*line - optr);
	b.l = max((long long)(offset - 1), 0);
	while (digit)
	{
		digit /= 10;
		if (prev_game)
			if(prev_game->hitmap[offset])
				number->_is_part_number = true;
		curr_game->numbers[offset++] = number;
		len++;
	}
	*line += len;
	b.r = min((offset), curr_game->len);
	if (prev_game && (prev_game->hitmap[b.l]
			|| prev_game->hitmap[offset]
			|| prev_game->hitmap[b.r]))
		number->_is_part_number = true;
	if (curr_game->hitmap[b.l] || curr_game->hitmap[b.r])
		number->_is_part_number = true;
	curr_game->number_list = g_list_append(curr_game->number_list, number);
	return (number);
}

game_t *new_game(size_t len)
{
	game_t		*game;
	number_t	**numbers;

	game = (game_t *) malloc(sizeof(game_t) * 1);
	if(!game)
		return (NULL);
	game->len = len;
	game->number_list = NULL;
	numbers = (number_t **) ft_calloc(sizeof(number_t *), len + 1);
	if (!numbers) {
		free(game);
		return (NULL);
	}
	game->numbers = numbers;
	game->hitmap = ft_empty_string(len);
	return (game);
}
