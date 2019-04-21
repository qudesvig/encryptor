/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:40:56 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/21 21:28:13 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double		rand_dbl(double min, double max)
{
	/*static char        buff[BUFF_RAND + 1];
	static int         index = 0;
	static int         step = 0;
	static int             fd = 0;
	double             percent;
	double             ret;

	if (fd == 0)
		fd = open("/dev/urandom", O_RDONLY);
	if (index > BUFF_RAND - 2)
	{
		index = 0;
		step++;
	}
	if (index == 0 && step == 10)
	{
		if (read(fd, buff, BUFF_RAND) == -1)
		{
			ft_putendl("read error!");
			return (0);
		}
		buff[BUFF_RAND] = '\0';
		step = 0;
	}
	ret = (double)((double)buff[index] * (double)buff[index + 1]);
	printf("buff = %s\n", buff);
	printf("btw index %d : %d & index %d : %d\n", index, buff[index], index + 1, buff[index + 1]);
	percent = ret / 16129;
	printf("%.10f - %.10f\n", max - min, percent);
	ret = ((max - min) * percent);
	index += 2;
	printf("in rnd_dbl ret = %.50f\n", ret);
	return (ret);*/
	double range = (max - min);
	double div = RAND_MAX / range;
	return min + (rand() / div);
}

void	tabdbl_bzero(long double *tab, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		tab[i] = 0;
		i++;
	}
}

long double	display_total_cost(long double *cost)
{
	int	i;
	long double totalc;


	i = 0;
	totalc = 0;
	while (i < DATASIZE)
	{
		totalc += cost[i];
		//printf("localcost = %.25Lf\n", cost[i]);
		i++;
	}
	printf("\naverage of totalc = %.25Lf\n", totalc / DATASIZE);
	return (totalc / DATASIZE);
}

void	training(t_netw *n, double **data)
{
	int			epoch;
	long double cost;
	long double newcost;
	long double	*weight_grad;
	double		lr;
	int			i; //for test

	i = 0;
	epoch = 0;
	lr = 0.1;
	cost = 0;
	newcost = 0;
	if (!(weight_grad = (long double*)malloc(sizeof(long double) * NB_WEIGHT)))
		return ;
	tabdbl_bzero(weight_grad, NB_WEIGHT);
	weight_grad = back_p(data, n, weight_grad, &cost);
	apply_grad(n, weight_grad, lr);
	while (epoch < 1000000)
	{
		printf("---------------epoch %d--------------\n", epoch);
		tabdbl_bzero(weight_grad, NB_WEIGHT);
		weight_grad = back_p(data, n, weight_grad, &newcost);
		printf("cost = %.50Lf vs newcost = %.50Lf\n", cost, newcost);
		if (newcost > cost)
		{
			if (newcost < 0.0000001)
			{
				printf("end at epoch %d\n", epoch);
				return ;
			}
			epoch = 0;
			cost = 0;
			lr = 0.1;
			reset_nw(n);
			tabdbl_bzero(weight_grad, NB_WEIGHT);
			weight_grad = back_p(data, n, weight_grad, &cost);
			apply_grad(n, weight_grad, lr);
		}
		else
		{
			cost = newcost;
			newcost = 0;
			if (cost < lr * 20)
				lr /= 1.1;
			apply_grad(n, weight_grad, lr);
			epoch++;
		}
	}
	free(weight_grad);
	return ;
}
