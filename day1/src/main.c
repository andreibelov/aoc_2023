//  SPDX-FileCopyrightText: 2023 Andrei Belov <belovsmail@gmail.com>
//  SPDX-License-Identifier: GPL-3.0-or-later

#include "main.h"
#include "stdio.h"

int	*ft_strstr(char *haystack, char *words[])
{
	char		*s;
	char		*needle = NULL;
	size_t		i;

	if (!haystack || !*haystack)
		return (NULL);
	i = -1;
	while (++i < 11)
	{
		s = haystack;
		needle = words[i];
		while (*needle++ == *s++)
			if (*needle == '\0')
				return (i + 1);
	}
	return (NULL);
}


int	read_single_file(FILE *fp)
{
	char	*line = NULL;
	char	*ptr = NULL;
	size_t	len = 0;
	ssize_t	nread;
	GList	*number_list = NULL;
	int 	d = 0;
	int 	i;
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
				if (i = ft_strstr(ptr, &dict))
				{
					number_list = g_list_append(number_list,
												GINT_TO_POINTER (i - 1));
					ptr += (ft_strlen(dict[i - 1]) - 2);
				}
		if (g_list_length(number_list) > 0) {
			int left = GPOINTER_TO_INT(g_list_first(number_list)->data);
			int right = GPOINTER_TO_INT(g_list_last(number_list)->data);
//			printf("s: \"%s\", \"%d%d\"\n", line, left, right);
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
	printf("Answer is: \"%d\"", result);
	return (EX_OK);
}
