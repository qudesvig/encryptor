/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:30:59 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/17 22:04:16 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

long double **computing_data(t_netw *n, double **data, long double **out)
{
	int		i;

	i = 0;
	while (i < DATASIZE)
	{
		n->netw[0][0].in = data[i][0];
		n->netw[0][1].in = data[i][1];
		out[i] = firing(n);
		n->netw[0][0].out = out[i][0];
		n->netw[0][1].out = out[i][1];
		i++;
	}
	return (out);
}

long double	*ft_cost(long double **out, double **data, long double *cost)
{
	int		i;
	int		j;

	i = 0;
	while (i < DATASIZE)
	{
		j = 0;
		while (j < NB_OUTPUT)
		{
			cost[i] += out[i][j] - data[i][j];
			j++;
		}
		cost[i] *= cost[i];
		i++;
	}
	return (cost);
}

long double	chain_rule(long double dcost, long double dact, long double dfct)
{
	return (dcost * dfct * dact);
}

long double	*calc_gradient(t_netw *n, long double **out, long double **data, long double *weight_grad)
{
	int			i;
	int			j;
	int			k;
	long double dact;

	i = 0;
			dact = 0;
			k = 0;
	while (i < n->layer_size[0])
	{
		j = 0;
		while (j < n->layer_size[1])
		{
			j++;
		}
		i++;
	}
	return (weight_grad);
}

void	apply_grad(t_netw *n, long double *grad, double lr)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (i < n->layer_size[0])
	{
		j = 0;
		while (j < n->layer_size[1])
		{
			n->netw[0][i].weight[j] -= lr * (grad[k] / DATASIZE);
			j++;
			k++;
		}
		i++;
	}
}
