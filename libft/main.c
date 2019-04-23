#include "libft.h"

int		main(int ac, char **av)
{
	char	*opt;
	char	*ret;

	opt = ft_strdup("arRlvf");
	ret = get_opt(ac, av, opt);
	ft_putendl(ret);
	return (0);
}
