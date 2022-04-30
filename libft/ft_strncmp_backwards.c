#include "libft.h"

int	ft_strncmp_backwards(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	k = 0;
	while (i > k && k < n && s1[i] == s2[j])
	{
		k++;
		i--;
		j--;
	}
	return ((unsigned char)*(s1 + i) - (unsigned char)*(s2 + j));
}
