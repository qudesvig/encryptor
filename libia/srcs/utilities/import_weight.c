/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_weight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 20:31:27 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/23 19:24:03 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libia.h"

double		*import_weight(char *file)
{
	int		fd;
	int		i;
	int		j;
	char	*line;
	char	**weight;
	double	*ret;

	if (!(fd = open(file, O_RDONLY)))
		return (NULL);
	i = 0;
	j = 0;
	if (!(ret = (double*)malloc(sizeof(double) * 4)))
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		weight = ft_strsplit(line, '\t');
		j = 0;
		while (weight[j])
		{
			ret[i * 2 + j] = atof(weight[j]);
			free(weight[j]);
			j++;
		}
		ft_strdel(&line);
		free(weight);
		i++;
	}
	return (ret);
}
