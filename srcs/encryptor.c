/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encryptor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:46:30 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/12 15:15:50 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double		*encryptor(t_netw *n)
{
	(void)n;
	return (NULL);
}

t_netw		*prepare_init_netw(t_netw *n, double *data)
{
	double	*bias;
	int		*layer_size;
	
	if ((!(data = (double*)malloc(sizeof(double) * NB_INPUT)))
		|| (!(bias = (double*)malloc(sizeof(double) * (NB_LAYER - 1))))
		|| (!(layer_size = (int*)malloc(sizeof(int) * NB_LAYER))))
		return (NULL);
	data = fill_data(data);
	layer_size = init_layer_size(layer_size);
	bias = init_bias(bias);
	PUT
	if (init_network(n, data, layer_size, bias))
		return (NULL);
	PUT
	return (n);
}

void		init_encr(void)
{
	t_netw	n;
	double	**data;
	int		i;

	i = 0;
	data = creat_database(1, -1);
	prepare_init_netw(&n, data[0]);
	printf("last fitness = %f\n", training(&n, data));
}
