/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 18:01:45 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/30 13:03:07 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libia.h"

void		fill_nw(double *data, t_netw *n)
{
	int		i;

	i = 0;
	while (i < NB_INPUT)
	{
		n->input[i] = data[i];
		n->netw[0][i].in = data[i];
		n->netw[0][i].out = n->netw[0][i].act(data[i]);
		i++;
	}
}

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

void		apply_bias(t_netw *n, double *bias)
{
	int		i;
	int		j;
	int		l;

	i = 0;
	l = 0;
	while (i < NB_LAYER - 1)
	{
		j = 0;
		while (j < n->layer_size[i])
		{
			n->netw[i][j].bias = bias[l];
			l++;
			j++;
		}
		i++;
	}
}

void		last_out(t_neurone *n, int nb_out)
{
	int		i;
	int		j;

	//printf("Computing last layer output\n");
	i = 0;
	j = NB_NEURONE - NB_OUTPUT;
	while (i < nb_out)
	{
		n[i].out = n[i].act(n[i].in);
		j++;
		i++;
	}
}

void		firing(t_netw *n)
{
	int			k;
	int			i;
	int			j;

	i = 0;
	//for each layer
	while (i < NB_LAYER - 1)
	{
		j = 0;
		//for each neurone of layer i + 1
		while (j < n->layer_size[i + 1])
		{
			n->netw[i + 1][j].in = n->netw[i + 1][j].bias;
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
	last_out(n->netw[i], n->layer_size[i]);
}
