//  SPDX-FileCopyrightText: 2023 Andrei Belov <belovsmail@gmail.com>
//  SPDX-License-Identifier: GPL-3.0-or-later

#include "main.h"


int	get_answer(FILE *fp)
{
	return (0);
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