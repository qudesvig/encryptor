/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_multi_encryptor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 17:06:03 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/23 18:58:35 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

void		fill_layer_size_big(int *dest, int *srcs)
{
	int		i;

	i = 0;
	while (i < NB_LAYER2)
	{
		dest[i] = srcs[i];
		i++;
	}
}

void		fill_bias_big(double *dest, double *srcs)
{
	int i;

	i = 0;
	while (i < NB_LAYER2)
	{
		dest[i] = srcs[i];
		i++;
	}
}

int			init_cell(t_neurone *n, int nb_weight, double (*act)(double))
{
	int	i;

	i = 0;
	n->nb_out = nb_weight;
	n->in = 0;
	n->act = act;
	n->out = 0;
	if (!(n->weight = (long double*)malloc(sizeof(long double) * nb_weight)))
		return (-1);
	while (i < nb_weight)
	{
		n->weight[i] = 0;
		i++;
	}
	return (0);
}

int			init_multi_encryptor(t_netw *n, int *layer_size, double *bias)
{
	
	int		i;
	int		j;

	i = 0;
	if (!(n->netw = (t_neurone**)malloc(sizeof(t_neurone) * NB_LAYER2))
			|| !(n->layer_size = (int*)malloc(sizeof(int) * NB_LAYER2))
			|| !(n->input = (double*)malloc(sizeof(double) * NB_INPUT2))
			|| !(n->bias = (double*)malloc(sizeof(double) * NB_LAYER2)))
		return (-1);
	fill_layer_size_big(n->layer_size, layer_size);
	fill_bias_big(n->bias, bias);
	if (!(n->out = (double*)malloc(sizeof(double) * n->layer_size[NB_LAYER2 - 1])))
		return (-1);
	while (i < NB_LAYER2)
	{
		j = 0;
		if (!(n->netw[i] = (t_neurone*)malloc(sizeof(t_neurone) * layer_size[i])))
			return (-1);
		while (j < layer_size[i])
		{
			//init_neurone(&(n->netw[i][j]), layer_size[i + ((i == NB_LAYER - 1) ? 0 : 1)], id_dbl);
			init_cell(&(n->netw[i][j]), ((i <= NB_LAYER / 2) ? 2 : 1), id_dbl);
			if (i == 0)
			{
				n->netw[i][j].in = n->input[j];
				n->netw[i][j].out = n->netw[i][j].act(n->input[j]);
			}
			j++;
		}
		i++;
	}
	return (0);
}
