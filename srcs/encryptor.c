/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encryptor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:46:30 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/01 17:32:50 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double		*irc_test(t_netw *n)
{
	double 		**data;
	int			i;
	int			j;
	long double cost;
	long double tmpcost;
	

	data = creat_database(50, -50);
	i = 0;
	cost = 0;
	while (i < DATASIZE)
	{
		j = 0;
		tmpcost = 0;
		fill_nw(data[i], n);
		firing(n);
		//printf("firing on data[%d]\n", i);
		while (j < NB_OUTPUT)
		{
			tmpcost += n->netw[NB_LAYER - 1][j].out - data[i][j];
			printf("\tout : %.50f - target %.50f\n", n->netw[NB_LAYER - 1][j].out, data[i][j]);
			j++;
		}
		cost += tmpcost * tmpcost;
		free(data[i]);
		i++;
	}
	free(data);
//	cost /= DATASIZE;
	printf("in real condition average of cost = %.25Lf\n", cost);
	if (cost < 0.000001)
		export_weight(n, "in_real_conditions");
	return (0);
}

t_netw		*prepare_init_netw(t_netw *n, double *data)
{
	double	*bias;
	int		*layer_size;
	
	if ((!(data = (double*)malloc(sizeof(double) * NB_INPUT)))
		|| (!(bias = (double*)malloc(sizeof(double) * NB_LAYER - 1)))
		|| (!(layer_size = (int*)malloc(sizeof(int) * NB_LAYER))))
		return (NULL);
	data = fill_data(data);
	layer_size = init_layer_size(layer_size);
	bias = init_bias(bias);
	if (init_network(n, data, layer_size, bias))
		return (NULL);
	reset_nw(n);
	return (n);
}

void		init_encr(void)
{
	t_netw	n;
	double	**data;
//	double	*weights;
//	double	*bias;

	data = import_data("data/data_s5");
//	weights = import_weight("config/weights");
//	bias = import_bias("config/bias");
	prepare_init_netw(&n, data[0]);
//	apply_weight(&n, weights);
//	apply_bias(&n, bias);
//	display_weight(n);
	genetic_training(&n, data);
	irc_test(&n);
	free_nw(&n);
//	free(weights);
}
