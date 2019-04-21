/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_netw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:10:45 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/21 18:07:48 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double		*fill_data(double *data)
{
	int		i;

	i = 0;
	while (i < NB_INPUT)
	{
		data[i] = rand_dbl(-5, 5);
		i++;
	}
	return (data);
}

int			*init_layer_size(int *layer_size)
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
	layer_size[0] = 2;
	layer_size[1] = 1;
	layer_size[2] = 2;
	return (layer_size);
}

double		*init_bias(double *bias)
{
	int		i;

	i = 0;
	while (i < NB_LAYER - 1)
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
