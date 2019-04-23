/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_weight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:57:04 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/23 19:18:46 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libia.h"

int			export_weight(t_netw *n, char *name)
{
	int		i;
	int		j;
	int		k;
	int		fd;

	if (!(fd = open(name, O_CREAT | O_WRONLY, 0777)))
		return (-1);
	i = -1;
	while (++i < NB_LAYER - 1)
	{
		j = -1;
		while (++j < n->layer_size[i])
		{
			k = -1;
			while (++k < n->layer_size[i + 1])
				dprintf(fd, "%.50Lf\t", n->netw[i][j].weight[k]);
		}
		dprintf(fd, "\n");
	}
	close(fd);
	return (0);
}
