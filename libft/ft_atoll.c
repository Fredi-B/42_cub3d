

#include "libft.h"

static const char	*isspacechar(const char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	return ((str));
}

void	isnbr(const char *str)
{
	if (*str < '0' || *str > '9')
	{
		write(2, "Error\nft_atoll: not a number\n", 30);
		exit(2);
	}
}

long	ft_atoll(const char *str)
{
	size_t			i;
	unsigned long long	nbr;

	str = isspacechar(str);
	nbr = 0;
	i = 0;
	isnbr(str);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nbr <= 9223372036854775807)
			nbr = nbr * 10 + str[i] - '0';
		else
			break ;
		i++;
	}
	if (str[i] != '\0')
	{
		write(2, "Error\nft_atoll: invalid input\n", 30);
		exit(2);
	}
	return (nbr);
}
