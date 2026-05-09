#include "txtfile.h"

static int	is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	count_words(char **lines)
{
	int	words;
	int	i;
	int	j;

	if (!lines)
		return (-1);
	words = 0;
	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (!is_separator(lines[i][j])
				&& (j == 0 || is_separator(lines[i][j - 1])))
				words++;
			j++;
		}
		i++;
	}
	return (words);
}