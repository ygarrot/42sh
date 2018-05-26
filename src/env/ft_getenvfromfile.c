#include "sh.h"

char	*ft_getenvfromfile(char *str)
{
	char	*file;
	int		fd;
	size_t	len;

	if ((len = ft_strlen(str)) == 0)
		return (0);
	if (!(file = ft_getenvfile(CODE_ENVGET)))
		return (0);
	fd = open(file, O_RDONLY);
	ft_strdel(&file);
	if (fd < 0)
		return (0);
	while (get_filetochar(fd, &file, '\v') == 1)
	{
		if (len > 0 && !ft_strncmp(str, file, len) && file[len] == '=')
		{
			len = 0;
			str = file;
		}
		else
			ft_strdel(&file);
	}
	close(fd);
	return (len > 0 ? 0 : str);
}
