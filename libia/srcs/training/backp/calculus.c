/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 15:24:16 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/30 20:42:28 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libia.h"

long double		ft_calc_cost(t_netw *n, double *target)
{
	int			i;
	long double cost;

	i = 0;
	cost = 0;
	while (i < NB_OUTPUT)
	{
		cost += (n->netw[NB_LAYER - 1][i].out - target[i]) * (n->netw[NB_LAYER - 1][i].out - target[i]);
		i++;
	}
	return (cost);
}

long double *averaging_grad(long double *grad)
{
	int		i;

	i = 0;
	while (i < NB_WEIGHT)
	{
		grad[i] /= DATASIZE;
		i++;
	}
	return (grad);
}
