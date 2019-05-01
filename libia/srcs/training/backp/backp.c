/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:30:59 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/29 15:36:56 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libia.h"

void		calc_grad(t_netw *n, long double *gradw, long double *gradb, double *target, int l)
{
	int			i; //for each neurone of layer l - 1
	int			j; // for each nerone of layer l
	int			k; //for each weight grad
	int			b; //for each bias grad
	long double dcost;
	long double dfct;
	long double dpact;
	double		*newtarget;

	i = 0;
	b = 0;
	k = get_weight_index(l, n);
	dfct = 1;
	if (l > 1)
	{
		if (!(newtarget = (double*)malloc(sizeof(double) * n->layer_size[l - 1])))
			return ;
		tabdbl_bzero(newtarget, n->layer_size[l - 1]);
	}
	while (i < n->layer_size[l - 1])
	{
		j = 0;
		while (j < n->layer_size[l])
		{
			dcost = 2 * (n->netw[l][j].out - target[j]);
			dpact = n->netw[l - 1][i].out;
			gradw[k] += dcost * dfct * dpact;
			if (i == 0)
			{
				gradb[b] += dcost;
				b++;
			}
			if (l > 1)
				newtarget[i] += dcost * dfct * n->netw[l - 1][i].weight[j];
			j++;
			k++;
		}
		if (l > 1)
			newtarget[i] = n->netw[l - 1][i].out - newtarget[i] / j; // a diviser par le nombre de neurone de la couche l
		i++;
	}
	chain_rule(n, gradw, gradb, target, l);

}

void		chain_rule(t_netw *n, long double *gradw, long double *gradb, double *target, int l)
{
	if (l > 1) // appel de la recursive
		calc_grad(n, gradw, gradb, target, l - 1);
	if (l != NB_LAYER - 1)
		free(target);
}

long double 	*back_p(double **data, t_netw *n, long double *grad, long double *gradb, long double *cost)
{
	int		i; //for each features

	i = 0;
	while (i < DATASIZE)
	{
		fill_nw(data[i], n);
		firing(n);
		*cost = *cost + ft_calc_cost(n, data[i]);
		calc_grad(n, grad, gradb, data[i], NB_LAYER - 1);
		i++;
	}
	return (grad);
}
