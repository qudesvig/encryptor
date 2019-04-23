/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_encryptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:08:06 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/23 18:59:05 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

void		fill_n2_weight(t_netw *n2, double *weight)
{
	int		i;
	int		j;
	int		way;

	i = 0;
	way = 0;
	while (i < NB_LAYER - 1)
	{
		j = 0;
		if (i == NB_LAYER / 2)
			way = 1;
		while (j < n2->layer_size[i])
		{
			if (way == 0)
				n2->netw[i][j].weight[0] = weight[(j % 2 == 0) ? 0 : 1];
			else
			{
				n2->netw[i][j].weight[0] = weight[0];
				n2->netw[i][j].weight[1] = weight[1];
			}
			j++;
		}
		i++;
	}
}

void		last_out_big(t_neurone *layer, int nb_out)
{
	int		i;

	//printf("Computing last layer output\n");
	i = 0;
	while (i < nb_out)
	{
		layer[i].out = layer[i].act(layer[i].in);
		i++;
	}
}

void		firing_big(t_netw *n)
{
	int			k;
	int			i;
	int			j;
	int			way;

	i = 0;
	way = 0;
	//for each layer
	while (i < NB_LAYER2 - 1)
	{
		j = 0;
		k = 0;
		if (i == NB_LAYER / 2)
			way = 1;
		//for each neurone of layer i + 1
		while (j < n->layer_size[i + 1])
		{
			n->netw[i + 1][j].in = 0;//n->bias[i];
			//for each neurone of layer i
			while ((way == 0 && k % 3 < 2) || (way == 1 && k % 2 < 1))
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
	last_out_big(n->netw[i], n->layer_size[i]);
}

void		multi_encryptor(t_netw *n)
{
	double **data;
	int		i;
	int		j;
	long double cost;
	long double tmpcost;
	

	data = creat_database(5, -5, 1);
	i = 0;
	cost = 0;
	while (i < DATASIZE)
	{
		j = 0;
		tmpcost = 0;
		fill_nw(data[i], n, 1);
		firing_big(n);
		while (j < NB_OUTPUT2)
		{
			tmpcost += n->netw[2][j].out - data[i][j];
			j++;
		}
		cost += tmpcost * tmpcost;
		free(data[i]);
		i++;
	}
	free(data);
	cost /= DATASIZE;
	printf("in real condition average of cost = %.25Lf\n", cost);
}
