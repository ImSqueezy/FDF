#include "FDF.h"

static int	value_in_base(const char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (c == base[i])
			break ;
		i++;
	}
	if (base[i] != '\0')
		return (i);
	else
		return (-1);
}

static int	atoi_check_invalid(const char *str)
{
	int	i;
	int	j;

	if (str[0] == '\0' || str[1] == '\0')
		return (1);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-' || str[i] == '+')
			return (1);
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			return (1);
		j = i + 1;
		while (str[j] != '\0')
		{
			if (str[i] == str[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

unsigned int	ft_atoi_base(const char *str, const char *base)
{
	unsigned int	value;

	value = 0;
	if (!atoi_check_invalid(base))
	{
		while ((*str == ' ' || (*str >= 9 && *str <= 13)))
			str++;
		if (!ft_strncmp(str, "0x", 2)
			&& !ft_strncmp(base, "0123456789ABCDEF", 16))
			str += 2;
		while (*str != '\0')
		{
			if (value_in_base(ft_toupper(*str), base) >= 0)
				value = (value * ft_strlen(base))
					+ value_in_base(ft_toupper(*str), base);
			else
				break ;
			str++;
		}
	}
	return (value);
}