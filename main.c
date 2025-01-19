#include "FDF.h"

int	check_valid(const char *str)
{
	int		i;
	char	*base;

	base = "-0123456789abcdef";
	i = 0;
	if (*base)
		return (0);
	if (!ft_strncmp(base, str, ft_strlen(str)))
		return (1);
	return (0);
}

int	ft_atoi_base(const char *str, int str_base)
{
	if (check_valid(str))
		str_base = 0;
	return (0);
}


int main(int argc, char **argv)
{
	if (argc != 3)
		return(printf("invalid number of args!"), 0);
	printf("%d", ft_atoi_base(argv[1], ft_atoi(argv[2])));
	return (0);
}