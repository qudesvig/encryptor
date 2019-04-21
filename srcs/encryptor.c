/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encryptor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:46:30 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/21 21:28:33 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double		*encryptor(t_netw *n)
{
	double **data;
	int		i;
	int		j;
	long double cost;
	long double tmpcost;
	

	data = creat_database(5, -5);
	i = 0;
	cost = 0;
	while (i < DATASIZE)
	{
		j = 0;
		tmpcost = 0;
		fill_nw(data[i], n);
		firing(n);
		while (j < NB_OUTPUT)
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
	if (cost < 0.0000005)
		export_weight(n);
	return (0);
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
	return (n);
}

void		init_encr(void)
{
	t_netw	n;
	double	**data;
	int		i;

	i = 0;
	ft_putendl("init data");
	data = creat_database(5, -5);
	ft_putendl("init netw");
	prepare_init_netw(&n, data[0]);
	training(&n, data);
	encryptor(&n);
	free_nw(&n);
}
