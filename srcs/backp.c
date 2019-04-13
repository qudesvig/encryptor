/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:30:59 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/12 16:41:57 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double	ft_cost_fct(double *out, double *in)
{
	double	cost;
	int		i;

	cost = 0;
	i = 0;
	while (i < NB_INPUT)
	{
		cost += (out[i] - in[i]) * (out[i] - in[i]);
		i++;
	}
	return (cost);
}

t_neurone find_neur(int nw, int nout, t_netw *n)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	tmp = 0;
	tmp += n->layer_size[i] * n->layer_size[i + 1]
	while (tmp < nw)
	{
		tmp += n->layer_size[i] * n->layer_size[i + 1];
		i++;
	}
	j = nw - (tmp = n->layer_size[i] * n->layer_size[i + 1]);
	return (n->netw[i][j]);

}

double	chain_rule(t_neurone n, double target)
{
	return ((n.out - target) * (1 - n.out * n.out) * in);
}

void	calc_grad(double *in, double *out, double *grad, t_netw *n)
{
	int	i;
	int	j;
	double	cost;

	i = NB_WEIGHT - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < NB_INPUT)
		{
			cost = (out[j] - in[j]) * (out[j] - in[j]);
			//working for lqst lqyer only
			grad[j] += chain_rule(find_neur(i, j, n), in[i]);
			//so 
			return ;
			j++;
		}
		i++;
	}
}

void	apply_grad(t_netw *n, double *grad, double lr)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (i < NB_LAYER - 1)
	{
		j = 0;
		while (j < n->layer_size[i + 1])
		{
			n[i][j] -= lr * grad[k];
			j++;
			k++;
		}
		i++;
	}
}
