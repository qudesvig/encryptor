/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_weight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 20:31:27 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/21 20:45:28 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libia.h"

int		inport_weight(char *file, t_netw *n)
{
	int		fd;
	int		i;
	int		j;
	int		k;
	char	*line;
	char	**weight;

	if (!(fd = open(file, O_RDONLY)))
		return (-1);
	i = 0;
	j = 0;
	while (read(fd, &line, 54) > 0)
	{
		weight = ft_strsplit(line, '\t');
		j = 0;
		while (weight[j])
		{
			k = 0;
			while (k < n->layer_size[i + 1])
			{
				n->netw[i][j].weight[k] = atof(weight[i]);
				k++;
			}
			j++;
		}
		free(line);
		i++;
	}
	return (0);
}
