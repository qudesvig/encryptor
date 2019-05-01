/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:40:56 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/01 14:17:55 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double		*fill_dbltab_rand(double *dest, unsigned int size)
{
	unsigned int i;

	i = 0;
	while (i < size)
	{
		dest[i] = rand_dbl(-5, 5);
		i++;
	}
	return (dest);
}

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
		if (!(pop[i].bias = tabdbl_dup(bias, NB_NEURONE - NB_INPUT))
				|| !(pop[i].weights = tabdbl_dup(weights, NB_WEIGHT)))
			return (NULL);
		if (i < NB_NEURONE)
			pop[i].weights = fill_dbltab_rand(pop[i].weights, NB_WEIGHT);
		else
			pop[i].bias = fill_dbltab_rand(pop[i].bias, NB_NEURONE - NB_INPUT);
		i++;
	}
	return (pop);
}

t_pop		*test_pop(t_pop *pop, double **data, t_netw *n, int under)
{
	int		i;
	int		j;

	i = 0;
	while (i < POPSIZE)
	{
		j = 0;
		pop[i].cost = 0;
		apply_weight(n, pop[i].weights);
		apply_bias(n, pop[i].bias);
		while (j < DATASIZE)
		{
			fill_nw(data[j], n);
			firing(n);
			pop[i].cost += ft_calc_cost(n, data[j]);
			j++;
		}
		i++;
	}
	return (get_elite(pop, under));
}

double		elitecost(t_pop *elite)
{
	int		i;
	double	cost;

	i = 0;
	cost = 0;
	while (i < 100 && elite[i].index != -1)
	{
		printf("cost %d : index %d = %.25f\n", i, elite[i].index, elite[i].cost);
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
	double		best;
	double		cost;
	int			under;

	epoch = 0;
	best = 10000000000;
	cost = 10000000000;
	under = 0;
	if (!(pop = init_pop(n)))
		return (-1);
	while (epoch < 100)
	{
		printf("-----------gen %d-----------------\n", epoch);
		elite = test_pop(pop, data, n, under);
		cost = elitecost(elite);
		printf("cost = %.25f\n", cost);
		under = is_under(cost, best);
		if (cost < best)
			best = cost;
		printf("best = %.25f\n", best);
		gang_bang(elite, pop, under);
		ft_putendl("-----------end new gen-----------------");
		epoch++;
	}
	apply_weight(n, elite[0].weights);
	apply_bias(n, elite[0].bias);
	export_weight(n, "config/weights");
	export_bias(n, "config/bias");
	return (0);
}
