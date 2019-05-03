/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encryptor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:46:30 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/03 23:20:25 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double		*irc_test(t_netw *n)
{
	int			i;
	long double cost;
	char		*line;

	i = 0;
	cost = 0;
	ft_putendl("irc test");
	while (i < 5)
	{
		get_next_line(0, &line);
		n->netw[0][i].out = atof(line);
		n->netw[0][i].in = n->netw[0][i].out;
		ft_strdel(&line);
		i++;
	}
	firing(n);
	i = 0;
	while (i < NB_OUTPUT)
	{
		printf("input[%d] = %f && output[%d] = %f\n", i, n->netw[0][i].in, i, n->netw[NB_LAYER - 1][i].out);
		cost += (n->netw[NB_LAYER - 1][i].out - n->netw[0][i].in) * (n->netw[NB_LAYER - 1][i].out - n->netw[0][i].in);
		i++;
	}
	printf("in real condition cost = %Lf\n", cost);
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
	return (n);
}

void		init_encr(int mod)
{
	t_netw	n;
	double	**data;
	double	*weights;
	double	*bias;

	data = import_data("data/data_s5");
	prepare_init_netw(&n, data[0]);
	weights = import_weight("config/weightssave");
	bias = import_bias("config/bias");
	apply_weight(&n, weights);
	apply_bias(&n, bias);
	if (mod == 0)
		genetic_training(&n, data);
	else
		irc_test(&n);
	free_nw(&n);
	free(weights);
	free(bias);
	free_data(data);
}
