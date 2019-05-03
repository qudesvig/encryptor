/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gang_bang.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:30:07 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/03 23:28:38 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"
/*double		*evolve_weights(int n, double *base)
{
	int		i;

	i = n / (NB_WEIGHT * 10);
	base[i] += rand_dbl(-1, 1);
	return (base);
}

double		*evolve_bias(int n, double *base)
{
	int		i;
	int		size;

	size = NB_NEURONE - NB_INPUT;
	i = n / (size * 10);
	base[i] += rand_dbl(-1, 1);
	return (base);
}*/

void		gangbang_rand(t_pop *elite, t_pop *pop, int i, int comeback)
{
	int				j;
	int				cible;
	
	while (i < POPSIZE)
	{
		pop[i].weights = tabdbl_cpy(pop[i].weights, elite[i % ELITESIZE].weights, NB_WEIGHT);
		pop[i].bias = tabdbl_cpy(pop[i].bias, elite[i % ELITESIZE].bias, NB_BIAS);
		j = (int)rand_dbl(0, NB_WEIGHT - (NB_WEIGHT / 5));
		cible = j + NB_WEIGHT / 5;
		while (j < cible)
		{
			evolve_weights(j, pop[i].weights, comeback, 1);
			j++;
		}
		j = (int)rand_dbl(0, NB_BIAS - (NB_BIAS / 5));
		cible = j + NB_BIAS / 5;
		while (j < cible)
		{
			evolve_bias(j, pop[i].bias, comeback, 1);
			j++;
		}
		i++;
	}
}


void		gang_bang(t_pop *elite, t_pop *pop, int comeback)
{
	int		start;
	int		i;
	int		j;
	int		nbch;
	int		tx;

	i = 0;
	start = 0;
	tx = 10;
	while (i < ELITESIZE)
	{
		nbch = 1;
		j = 1;
		if (start < POPSIZE)
		{
			pop[start].weights = tabdbl_cpy(elite[i].weights, pop[start].weights, NB_WEIGHT);
			pop[start].bias = tabdbl_cpy(elite[i].bias, pop[start].bias, NB_BIAS);
		}
		while (j < POPSIZE / 100 + tx && start + j < POPSIZE)
		{
			if (j % (POPSIZE / 200) == 0)
				nbch++;
			pop[start + j].weights = tabdbl_cpy(elite[i].weights, pop[start + j].weights, NB_WEIGHT);
			pop[start + j].weights = evolve_weights(i + j, pop[start + j].weights, comeback, nbch);
			pop[start + j].bias = tabdbl_cpy(elite[i].bias, pop[start + j].bias, NB_BIAS);
			pop[start + j].bias = evolve_bias(i + j, pop[start + j].bias, comeback, nbch);
			j++;
		}
		if (i % 5 == 0 && tx > 0)
			tx -= 2;
		start += j;
		i++;
	}
	gangbang_rand(elite, pop, start, comeback);
	free_elite(elite);
}
/*
void		gang_bang(t_pop *elite, t_pop *pop, int comeback)
{
	int		start;
	int		i;
	int		j;
	int		nbchw;
	int		nbchb;

	i = 0;
	start = 0;
	while (i < ELITESIZE)
	{
		nbchw = 1;
		nbchb = 1;
		j = 1;
		if (start < POPSIZE)
		{
			pop[start].weights = tabdbl_cpy(elite[i].weights, pop[start].weights, NB_WEIGHT);
			pop[start].bias = tabdbl_cpy(elite[i].bias, pop[start].bias, NB_BIAS);
		}
		while (j < POPSIZE / 100 && start + j < POPSIZE)
		{
			if (j == nbchw * NB_WEIGHT)
				nbchw++;
			if (j == nbchb * NB_BIAS)
				nbchb++;
			pop[start + j].weights = tabdbl_cpy(elite[i].weights, pop[start + j].weights, NB_WEIGHT);
			pop[start + j].weights = evolve_weights(i + j, pop[start + j].weights, comeback, nbchw);
			pop[start + j].bias = tabdbl_cpy(elite[i].bias, pop[start + j].bias, NB_BIAS);
			pop[start + j].bias = evolve_bias(i + j, pop[start + j].bias, comeback, nbchb);
			j++;
		}
		start += j;
		i++;
	}
	gangbang_rand(elite, pop, start, comeback);
	free_elite(elite);
}*/
