//  SPDX-FileCopyrightText: 2023 Andrei Belov <belovsmail@gmail.com>
//  SPDX-License-Identifier: GPL-3.0-or-later

#include "main.h"
#include "stdio.h"

int	read_single_file(FILE *fp)
{
	char	*line = NULL;
	char	*ptr = NULL;
	size_t	len = 0;
	ssize_t	nread;
	GList	*number_list = NULL;
	int 	d = 0;
	size_t 	i;
	char	*dict[10] = {
			"zero",
			"one",
			"two",
			"three",
			"four",
			"five",
			"six",
			"seven",
			"eight",
			"nine"
	};

	nread = getline(&line, &len, fp);
	while (nread != -1)
	{
		ptr = line - 1;
		while (*++ptr)
			if (isdigit(*ptr))
				number_list = g_list_append(number_list,
											GINT_TO_POINTER (*ptr - '0'));
			else if (isalpha(*ptr))
				if (i = ft_strstr_fixed(ptr, &dict))
				{
					number_list = g_list_append(number_list,
												GINT_TO_POINTER (i - 1));
					ptr += (ft_strlen(dict[i - 1]) - 2);
				}
		if (g_list_length(number_list) > 0) {
			int left = GPOINTER_TO_INT(g_list_first(number_list)->data);
			int right = GPOINTER_TO_INT(g_list_last(number_list)->data);
//			ft_printf("s: \"%s\", \"%d%d\"\n", line, left, right);
			d +=  left * 10 + right;
		}
		g_list_free(number_list);
		number_list = NULL;
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
	result = read_single_file(fp);
	fclose(fp);
	ft_printf("Answer is: \"%d\"", result);
	return (EX_OK);
}
