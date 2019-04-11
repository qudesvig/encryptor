/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 18:01:45 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/11 16:24:09 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libia.h"

void		apply_weight(t_netw *n, double *weight)
{
	int		i;
	int		j;
	int		k;
	int		l;

	i = 0;
	l = 0;
	while (i < NB_LAYER - 1)
	{
		j = 0;
		while (j < n->layer_size[i])
		{
			k = 0;
			while (k < n->layer_size[i + 1])
			{
				n->netw[i][j].weight[k] = weight[l];
				k++;
				l++;
			}
			j++;
		}
		i++;
	}
}

double		*last_out(t_neurone *n, int nb_out, double **outs)
{
	int		i;

	printf("Computing last layer output\n");
	//if (!(outs = (double*)malloc(sizeof(double) * nb_out)))
	//	return (NULL);
	i = 0;
	while (i < nb_out)
	{
		(*outs)[i] = n[i].act(n[i].in);
		n[i].out = (*outs)[i];
		i++;
	}
	return (*outs);
}

double		*firing(t_netw *n, double **out)
{
	int		k;
	int		i;
	int		j;

	i = 0;
	//for each layer
	while (i < NB_LAYER - 1)
	{
		j = 0;
		//for each neurone of layer i + 1
		while (j < n->layer_size[i + 1])
		{
			n->netw[i + 1][j].in = n->bias[i];
			k = 0;
			//for each neurone of layer i
			while (k < n->layer_size[i])
			{
				//neurone j at layer i + 1 += output de neurone k at layer i * weight to neurone j
				n->netw[i + 1][j].in += n->netw[i][k].out * n->netw[i][k].weight[j];
				k++;
			}
			n->netw[i + 1][j].out = n->netw[i + 1][j].act(n->netw[i + 1][j].in);
			j++;
		}
		i++;
	}
	return (last_out(n->netw[i], n->layer_size[i], out));
}
