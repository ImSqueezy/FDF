#include "FDF.h"

int	mini_atoi_base(char *line) {
	int		result;
	char	c;

	line += 2;
	result = 0;
	while (*line)
	{
		c = ft_tolower(*line);
		if (c >= '0' && c <= '9')
			result = result * 16 + (c - '0');
		else if (c >= 'a' && c <= 'f')
			result = result * 16 + (c - 'a' + 10);
		else
			break ;
		line++;
	}
	return (result);
}
