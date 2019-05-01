/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_nw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 15:38:15 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/29 15:38:53 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libia.h"

void		reset_nw(t_netw *n)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	while (k < NB_LAYER - 1)
	{
		i = 0;	
		while (i < n->layer_size[k])
		{
			j = 0;
			while (j < n->layer_size[k + 1])
			{
				n->netw[k][i].weight[j] = rand_dbl(-1, 1);
				usleep(10);
				j++;
			}
			i++;
		}
		k++;
	}
}
