/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:30:59 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/23 17:23:05 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

long double	chain_rule(long double dcost, long double dact, long double dfct)
{
	return (dcost * dfct * dact);
}

long double *averaging_grad(long double *weight_grad)
{
	int		i;

	i = 0;
	while (i < NB_WEIGHT)
	{
		weight_grad[i] /= DATASIZE;
		i++;
	}
	return (weight_grad);
}

void	apply_grad(t_netw *n, long double *grad, double lr)
{
	int		i; //neurone of actual layer
	int		j; //neurone of next layer
	int		k; //nb weight in grad
	int		l; //for each layer

	k = 0;
	l = 0;
	while (l < NB_LAYER - 1)
	{
		i = 0;
//		ft_putendl("applygrad 1eme boucle");
		while (i < n->layer_size[l])
		{
//			ft_putendl("\tapplygrad 2eme boucle");
			j = 0;
			while (j < n->layer_size[l + 1])
			{
//				ft_putendl("\t\tapplygrad 3eme boucle");
//				printf("\t\tgrad[%d] = %.25Lf\n", k, grad[k] / DATASIZE);
				n->netw[l][i].weight[j] -= lr * (grad[k] / DATASIZE);
				j++;
				k++;
			}
			i++;
		}
		l++;
	}
}

int			get_weight_index(int l, t_netw *n)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < l - 1)
	{
		ret += n->layer_size[i] * n->layer_size[i + 1];
		i++;
	}
	return (ret);
}

void		tabdbl2_bzero(double *tab, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		tab[i] = 0;
		i++;
	}
}

void		calc_grad(t_netw *n, long double *grad, double *target, int l)
{
	int			i; //for each neurone of layer l - 1
	int			j; // for each nerone of layer l
	int			k; //for each weight grad
	long double dcost;
	long double dfct;
	long double dpact;
	double		*newtarget;

	i = 0;
	k = get_weight_index(l, n);
	dfct = 1;
	//printf("for backp of layer %d target = %.10f %.10f %.10f\n", l, target[0], target[1], target[2]);
	if (l > 1)
	{
		if (!(newtarget = (double*)malloc(sizeof(double) * n->layer_size[l - 1])))
			return ;
		tabdbl2_bzero(newtarget, n->layer_size[l - 1]);
	}
	while (i < n->layer_size[l - 1])
	{
		j = 0;
		//printf("from neurone %d of layer %d : %d\n", i, l - 1, n->layer_size[l - 1]);
		while (j < n->layer_size[l])
		{
		//	printf("\tto neurone %d of layer %d : %d\n", j, l, n->layer_size[l]);
			dcost = 2 * (n->netw[l][j].out - target[j]);
		//	printf("\tdcost = %.25Lf : out = %.25f - target = %.25f\n", dcost, n->netw[i][j].out, target[j]);
			dpact = n->netw[l - 1][i].out;
		//	printf("\tdpact = %.25Lf\n", dpact);
			grad[k] += dcost * dfct * dpact;
		//	printf("\tgrad[%d] += %.25Lf\n", k, dcost * dpact * dfct);
			if (l > 1)
				newtarget[i] += dcost * dfct * n->netw[l - 1][i].weight[j];
			j++;
			k++;
		}
		if (l > 1)
			newtarget[i] = n->netw[l - 1][i].out - newtarget[i]; // a diviser par le nombre de neurone de la couche l
		i++;
	}
	if (l > 1) // appel de la recursive
		calc_grad(n, grad, newtarget, l - 1);
	if (l != NB_LAYER - 1)
		free(target);
}

long double		ft_calc_cost(t_netw *n, double *data)
{
	int		i;
	long double cost;

	i = 0;
	cost = 0;
//	display_weight(*n);
	while (i < NB_OUTPUT)
	{
//		printf("cost += %.25f - %.25f\n", n->netw[NB_LAYER - 1][i].out, data[i]);
		cost += n->netw[NB_LAYER - 1][i].out - data[i];
		//cost += n->netw[2][i].out - data[i];
		i++;
	}
	return (cost * cost);
}

long double 	*back_p(double **data, t_netw *n, long double *grad, long double *cost)
{
	int		i; //for each features

	i = 0;
	while (i < DATASIZE)
	{
		//printf("computing data %d\n", i);
		fill_nw(data[i], n, 0);
		//ft_putendl("\tfiring");
		firing(n);
		//ft_putendl("\tfiring : Done!");
		*cost = *cost + ft_calc_cost(n, data[i]);
		//printf("\tcost = %.25Lf\n", *cost);
		//ft_putendl("\tback P");
		calc_grad(n, grad, data[i], NB_LAYER - 1);
		//ft_putendl("\tback P : Done!");
		i++;
	}
	*cost = *cost / DATASIZE;
	printf("average cost = %.80Lf\n", *cost);
	return (grad);
}
