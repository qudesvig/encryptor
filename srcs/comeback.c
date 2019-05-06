/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comeback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:43:25 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/04 02:26:23 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

void		saving_for_cmb(t_pop *dest, t_pop srcs)
{
	if (dest->index == -1)
	{
		dest->weights = tabdbl_dup(srcs.weights, NB_WEIGHT);
		dest->bias = tabdbl_dup(srcs.bias, NB_BIAS);
	}
	else
	{
		dest->weights = tabdbl_cpy(srcs.weights, dest->weights, NB_WEIGHT);
		dest->bias = tabdbl_cpy(srcs.bias, dest->bias, NB_BIAS);
	}
	dest->index = srcs.index;
	dest->cost = srcs.cost;
}

void		reinit_pop(t_pop base, t_pop *pop)
{
	int		i;
	int		j;
	int		cible;

	i = 0;
	while (i < POPSIZE)
	{
		pop[i].weights = tabdbl_cpy(base.weights, pop[i].weights, NB_WEIGHT);
		pop[i].bias = tabdbl_cpy(base.bias, pop[i].bias, NB_BIAS);
		j = (int)rand_dbl(0, NB_WEIGHT - (NB_WEIGHT / 4));
		cible = j + NB_WEIGHT / 4;
		while (j < cible)
		{
			evolve_weights(j, pop[i].weights, (i < POPSIZE / 2) ? 0 : 10, 1);
			j++;
		}
		j = (int)rand_dbl(0, NB_BIAS - (NB_BIAS / 4));
		cible = j + NB_BIAS / 4;
		while (j < cible)
		{
			evolve_bias(j, pop[i].bias, (i < POPSIZE / 2) ? 0 : 10, 1);
			j++;
		}
		pop[i].cost = -1;
		pop[i].index = i;
		i++;
	}
}
