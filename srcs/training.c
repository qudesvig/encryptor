/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:40:56 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/06 18:50:01 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

t_pop		*init_pop(t_netw *n)
{
	int		i;
	double	*weights;
	double	*bias;
	t_pop	*pop;

	i = 0;
	if (!(pop = (t_pop*)malloc(sizeof(t_pop) * POPSIZE))
			|| !(weights = get_weights(n))
			|| !(bias = get_bias(n)))
		return (NULL);
	while (i < POPSIZE)
	{
		pop[i].cost = 0;
		if (!(pop[i].bias = tabdbl_dup(bias, NB_BIAS))
				|| !(pop[i].weights = tabdbl_dup(weights, NB_WEIGHT)))
			return (NULL);
		if (i > 0 && i < NB_NEURONE)
			pop[i].weights = add_dbltab_rand(pop[i].weights, NB_WEIGHT - i % NB_WEIGHT);
		else if (i > 0)
			pop[i].bias = add_dbltab_rand(pop[i].bias, NB_BIAS - i % NB_BIAS);
		i++;
	}
	return (pop);
}

double		elitecost(t_pop *elite)
{
	int		i;
	double	cost;

	i = 0;
	cost = 0;
	while (i < ELITESIZE && elite[i].index != -1)
	{
		if (i % (ELITESIZE / 10) == 0)
			printf("cost %d : index %d = %f\n", i, elite[i].index, elite[i].cost);
		cost += elite[i].cost;
		i++;
	}
	return (cost / i);
}

int			genetic_training(t_netw *n, double **data)
{
	int			epoch;
	t_pop		*elite;
	t_pop		*pop;
	t_pop		save;
	double		best;
	double		cost;
	int			comeback;

	epoch = 0;
	best = 10000000000;
	cost = 10000000000;
	save.index = -1;
	comeback = 0;
	if (!(pop = init_pop(n)))
		return (-1);
	while (epoch < 1000)
	{
		printf("-----------gen %d-----------------\n", epoch);
		elite = test_pop(pop, data, comeback);
		cost = elitecost(elite);
		printf("cost = %f\ncomeback = %d\n", cost, comeback);
		if (elite[0].cost < best)
		{
			saving_for_cmb(&save, elite[0]);
			saving_config(elite[0], n, 2);
			comeback = 0;
			best = elite[0].cost;
		}
		printf("best = %f\n", best);
		if (comeback > 25)
		{
			reinit_pop(elite[0], pop);
			comeback = 0;
		}
		else
			gang_bang_pth(elite, pop, comeback);
		ft_putendl("-----------end new gen-----------------");
		comeback++;
		epoch++;
	}
	saving_config(elite[0], n, 0);
	return (0);
}
