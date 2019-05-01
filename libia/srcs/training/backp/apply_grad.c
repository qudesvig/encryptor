/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_grad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 15:21:37 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/29 15:22:58 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libia.h"

void		apply_grad(t_netw *n, long double *gradw, long double *gradb, double lr)
{
	int		i; //neurone of actual layer
	int		j; //neurone of next layer
	int		k; //nb weight in grad
	int		l; //for each layer
	int		b; //dor each bias

	k = 0;
	l = -1;
	b = 0;
	while (++l < NB_LAYER - 1)
	{
		i = -1;
		while (++i < n->layer_size[l])
		{
			j = 0;
			n->netw[l][i].bias += lr * (gradb[b] / DATASIZE);
			while (j < n->layer_size[l + 1])
			{
				n->netw[l][i].weight[j] -= lr * (gradw[k] / DATASIZE);
				j++;
				k++;
			}
			b++;
		}
	}
}
