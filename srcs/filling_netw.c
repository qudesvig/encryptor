/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_netw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:10:45 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/23 15:55:50 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double		*fill_data(double *data, int mod)
{
	int		i;

	i = 0;
	while (i < ((mod == 0) ? NB_INPUT : NB_INPUT2))
	{
		data[i] = rand_dbl(-5, 5);
		i++;
	}
	return (data);
}

int			*init_layer_size(int *layer_size, int mod)
{
	/*int		i;
	int		size;

	i = 1;
	size = 8192;
	layer_size[0] = 10000;
	layer_size[8] = 10000;
	while (i < NB_LAYER - 1)
	{
		layer_size[i] = size;
		if (i < 4)
			size /= 2;
		else
			size *= 2;
		printf("layer_saze %d = %d\n", i, layer_size[i]);
		i++;
	}*/
	if (mod == 0)
	{
		layer_size[0] = 2;
		layer_size[1] = 1;
		layer_size[2] = 2;
	}
	else
	{
		layer_size[0] = 16;
		layer_size[1] = 8;
		layer_size[2] = 4;
		layer_size[3] = 2;
		layer_size[4] = 4;
		layer_size[5] = 8;
		layer_size[6] = 16;
	}
	return (layer_size);
}

double		*init_bias(double *bias, int mod)
{
	int		i;

	i = 0;
	while (i < ((mod == 0) ? NB_LAYER - 1 : NB_LAYER2 - 1))
	{
		bias[i] = BIAS;
		i++;
	}
	return (bias);
}

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

void		fill_nw(double *data, t_netw *n, int mod)
{
	int		i;

	i = 0;
	while (i < ((mod == 0) ? NB_INPUT : NB_INPUT2))
	{
		n->input[i] = data[i];
		n->netw[0][i].in = data[i];
		n->netw[0][i].out = n->netw[0][i].act(data[i]);
		i++;
	}
}
