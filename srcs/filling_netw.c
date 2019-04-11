/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_netw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:10:45 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/11 16:37:34 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double		*fill_data(double *data)
{
	int		i;

	i = 0;
	while (i < NB_INPUT)
	{
		data[i] = (rand() / (double)RAND_MAX) * (1 - -1) + -1;
		i++;
	}
	return (data);
}

int			*init_layer_size(int *layer_size)
{
	int		i;
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
	}
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
