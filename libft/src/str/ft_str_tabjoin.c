#include "libft.h"

char			*ft_str_tabjoin(char const **tab)
{
	int		i;
	int		i2;
	char	*fresh;

	if (!tab)
		return (NULL);
	i2 = -1;
	i = 0;
	while (tab[++i2])
		i += ft_strlen(tab[i2]);
	if (!(fresh = ft_strnew(i + 1)))
		return (NULL);
	i2 = -1;
	while (tab[++i2])
		ft_strcat(fresh, tab[i2]);
	return (fresh);
}
