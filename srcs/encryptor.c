/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encryptor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:46:30 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/23 20:30:43 by qudesvig         ###   ########.fr       */
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
	

	data = creat_database(5, -5, 0);
	i = 0;
	cost = 0;
	while (i < DATASIZE)
	{
		j = 0;
		tmpcost = 0;
		fill_nw(data[i], n, 0);
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
	if (cost < 0.000001)
		export_weight(n, "in_real_conditions");
	return (0);
}

t_netw		*prepare_init_netw(t_netw *n, double *data, int mod)
{
	double	*bias;
	int		*layer_size;
	
	if ((!(data = (double*)malloc(sizeof(double) * ((mod == 0) ? NB_INPUT : NB_INPUT2))))
		|| (!(bias = (double*)malloc(sizeof(double) * (((mod == 0) ? NB_LAYER : NB_LAYER2) - 1))))
		|| (!(layer_size = (int*)malloc(sizeof(int) * ((mod == 0) ? NB_LAYER : NB_LAYER2)))))
		return (NULL);
	data = fill_data(data, mod);
	layer_size = init_layer_size(layer_size, mod);
	bias = init_bias(bias, mod);
	if (mod == 0)
	{
		if (init_network(n, data, layer_size, bias))
			return (NULL);
	}
	else if (mod == 1)
	{
		if (!init_multi_encryptor(n, layer_size, bias))
			return (NULL);
	}
	return (n);
}

void		init_encr(void)
{
	t_netw	n;
//	t_netw	n2;
	double	**data;
//	double	*weights;

	ft_putendl("init data");
	data = creat_database(5, -5, 0);
	ft_putendl("init netw");
	prepare_init_netw(&n, data[0], 0);
	training(&n, data);
	encryptor(&n);/*
	weights = import_weight("config/in_real_condition");
	prepare_init_netw(&n2, data[0], 1);
	fill_n2_weight(&n2, weights);
	multi_encryptor(&n2);*/
	free_nw(&n, 0);
//	free_nw(&n2, 1);
//	free(weights);
}
