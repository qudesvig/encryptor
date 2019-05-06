/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gang_bang.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:30:07 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/06 13:49:31 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

void		gangbang_rand(t_pop *elite, t_pop *pop, int i, int comeback)
{
	int				j;
	
	if (i >= POPSIZE)
		i = POPSIZE - (POPSIZE / 1000);
	while (i < POPSIZE)
	{
		pop[i].weights = tabdbl_cpy(elite[i % ELITESIZE].weights, pop[i].weights, NB_WEIGHT);
		pop[i].bias = tabdbl_cpy(elite[i % ELITESIZE].bias, pop[i].bias, NB_BIAS);
		j = (int)rand_dbl(0, NB_WEIGHT - (NB_WEIGHT / 5));
		evolve_weights(j, pop[i].weights, comeback, NB_WEIGHT / 5);
		j = (int)rand_dbl(0, NB_BIAS - (NB_BIAS / 5));
		evolve_bias(j, pop[i].bias, comeback, NB_BIAS / 5);
		i++;
	}
}

/*
void		gang_bang(t_pop *elite, t_pop *pop, int comeback)
{
	int		start;
	int		i;
	int		j;
	int		nbch;
	int		tx;

	i = 0;
	start = 0;
	tx = 0;
	while (i < ELITESIZE)
	{
		nbch = 1;
		j = 1;
		if (start < POPSIZE)
		{
			pop[start].weights = tabdbl_cpy(elite[i].weights, pop[start].weights, NB_WEIGHT);
			pop[start].bias = tabdbl_cpy(elite[i].bias, pop[start].bias, NB_BIAS);
		}
		while (j < POPSIZE / ELITESIZE + tx && start + j < POPSIZE)
		{
			if (j % (i + 1) == (i + 1) / nbch && nbch < NB_BIAS)
				nbch++;
			pop[start + j].weights = tabdbl_cpy(elite[i].weights, pop[start + j].weights, NB_WEIGHT);
			pop[start + j].weights = evolve_weights(i + j, pop[start + j].weights, comeback, nbch);
			pop[start + j].bias = tabdbl_cpy(elite[i].bias, pop[start + j].bias, NB_BIAS);
			pop[start + j].bias = evolve_bias(i + j, pop[start + j].bias, comeback, nbch);
			j++;
		}
		if (i % 20 == 0 && tx < 50)
			tx++;
		start += j;
		i++;
	}
	gangbang_rand(elite, pop, start, comeback);
	free_elite(elite);
}
*/
 void		gang_bang(t_pop *elite, t_pop *pop, int comeback)
{
	int		start;
	int		i;
	int		j;
	int		nbch;
	int		tx;

	i = 0;
	start = 0;
	tx = 0;
	while (i < ELITESIZE)
	{
		nbch = 1;
		j = 1;
		if (start < POPSIZE)
		{
			pop[start].weights = tabdbl_cpy(elite[i].weights, pop[start].weights, NB_WEIGHT);
			pop[start].bias = tabdbl_cpy(elite[i].bias, pop[start].bias, NB_BIAS);
		}
		while (j < POPSIZE / ELITESIZE + tx && start + j < POPSIZE)
		{
			if (j % (POPSIZE / (ELITESIZE * 4)) == 0)
				nbch++;
			pop[start + j].weights = tabdbl_cpy(elite[i].weights, pop[start + j].weights, NB_WEIGHT);
			pop[start + j].weights = evolve_weights(i + j, pop[start + j].weights, comeback, nbch);
			pop[start + j].bias = tabdbl_cpy(elite[i].bias, pop[start + j].bias, NB_BIAS);
			pop[start + j].bias = evolve_bias(i + j, pop[start + j].bias, comeback, nbch);
			j++;
		}
		if (i % 20 == 0 && tx < 50)
			tx += 2;
		start += j;
		i++;
	}
	gangbang_rand(elite, pop, start, comeback);
	
}
