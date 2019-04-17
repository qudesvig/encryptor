/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:40:56 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/17 22:04:23 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double		rand_dbl(double min, double max)
{
	char		buff[BUFF_RAND + 1];
	static int 		index = 0;
	int 			fd;
	double 			percent;
	double 			ret;

	if (index > BUFF_RAND - 2)
		index = 0;
	if (index == 0)
	{

		fd = open("/dev/random", O_RDONLY);
		if (read(fd, buff, BUFF_RAND) == -1)
			return (0);
		buff[BUFF_RAND] = '\0';
		close (fd);
	}
	ret = (double)((double)buff[index] * (double)buff[index + 1]);
	percent = ret / 32258;
	ret = (max - min) * percent;
	index += 2;
	return (ret);
}

/*double	adapt_lr(double lr, double act, double last)
{
	int		abs;

	abs = (int)(last * act) / 100;
	if (abs > 50)
		return (lr )
}*/

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

void	training(t_netw *n, double **data)
{
	int			epoch;
	long double	*cost; //the cost for each features
	int			i; //actual neurone
	long double	**out; // output of NW for each feature
	long double *weight_grad; //grad for each weight

	epoch = 0;
	i = 0;
	if (!(cost = (long double*)malloc(sizeof(long double) * DATASIZE)))
		return ;
	tabdbl_bzero(cost, DATASIZE);
	if (!(out = (long double**)malloc(sizeof(long double*) * DATASIZE)))
		return ;
	if (!(weight_grad = (long double*)malloc(sizeof(long double) * NB_WEIGHT)))
		return ;
	tabdbl_bzero(weight_grad, NB_WEIGHT);
	while (epoch < 1000)
	{
		display_weight(*n);
		out = computing_data(n, data, out);
		cost = ft_cost(out, data, cost);
		weight_grad = calc_gradient(n, cost, weight_grad);
		while (i < NB_WEIGHT)
		{
			printf("cost for out[%d]: %.25Lf\n", i, cost[i]);
			i++;
		}
		return ;
	}
}
