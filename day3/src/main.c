//  SPDX-FileCopyrightText: 2023 Andrei Belov <belovsmail@gmail.com>
//  SPDX-License-Identifier: GPL-3.0-or-later

#include "main.h"

int	get_answer(FILE *fp)
{
	ssize_t		nread;
	int			d = 0;
	size_t		len = 0;
	char		*line = NULL;

	nread = getline(&line, &len, fp);
	while (nread != -1)
	{
		ft_printf("%s", line);
		nread = getline(&line, &len, fp);
	}
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
//		read_single_file(ft_fopen("/dev/stdin", "r"));
		fp = fopen(INPUT_FILE_NAME, "r");
		result = get_answer(fp);
		fclose(fp);
		ft_printf("Answer is: \"%d\"", result);
	}
	return (EX_OK);
}