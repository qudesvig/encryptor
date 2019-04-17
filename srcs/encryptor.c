/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encryptor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:46:30 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/17 22:04:22 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double		*encryptor(t_netw *n)
{
	double	*out;

	if (!(out = (double*)malloc(sizeof(double) * NB_OUTPUT)))
	{
		ft_putendl("mallox error");
		return (NULL);
	}
	(void)n;
	return (out);
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
	data = creat_database(5, -5);
	prepare_init_netw(&n, data[0]);
	training(&n, data);
	encryptor(&n);
}
