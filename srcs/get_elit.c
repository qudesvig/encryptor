/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:35:19 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/01 17:29:04 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

void		init_elite(t_pop *elite, t_pop *pop)
{
	int		i;

	i = 0;
	while (i < 100)
	{
		elite[i].cost = 1000000000000;
		elite[i].index = -1;
		elite[i].weights = tabdbl_dup(pop[i].weights, NB_WEIGHT);
		elite[i].bias = tabdbl_dup(pop[i].bias, NB_BIAS);
		i++;
	}
}

void		push_in(t_pop new, t_pop *elite, int i, int pos)
{
	int		j;

	j = 5;
	while (j >= i)
	{
		elite[j + 1].cost = elite[j].cost;
		elite[j + 1].index = elite[j].index;
		j--;
	}
	elite[i].cost = new.cost;
	elite[i].index = pos;
}

void		get_elite_config(t_pop *elite, t_pop *pop)
{
	int		i;

	i = 0;
	while (i < 100)
	{
		if (elite[i].index != -1)
		{
			elite[i].weights = tabdbl_dup(pop[elite[i].index].weights, NB_WEIGHT);
			elite[i].bias = tabdbl_dup(pop[elite[i].index].bias, NB_NEURONE - NB_INPUT);
		}
		i++;
	}
}

void		add_rand_to_pop(t_pop *elite, int under)
{
	int			i;
	int			j;
	static int	lr = 4;

	i = 0;
	if (under == 1)
		lr /= 2;
	while (i < ELITESIZE && elite[i].index != -1)
		i++;
	i = (i < ELITESIZE - ELITESIZE / 10) ? i : ELITESIZE - ELITESIZE / 10;
	while (i < ELITESIZE)
	{
		elite[i].weights = tabdbl_dup(elite[0].weights, NB_WEIGHT);
		elite[i].bias = tabdbl_dup(elite[0].bias, NB_BIAS);
		j = 0;
		while (j < NB_WEIGHT)
		{
			elite[i].weights[j] += rand_dbl(-1 * lr, 1 * lr);
			j++;
		}
		j = 0;
		while (j < NB_BIAS)
		{
			elite[i].bias[j] += rand_dbl(-1 * lr, 1 * lr);
			j++;
		}
		elite[i].cost = -1;
		elite[i].index = -1;
		i++;
	}
}

void		display_elite(t_pop *elite)
{
	int 	i;

	i = 0;
	while (i < 100 && elite[i].index != -1)
	{
		printf("elite[%d].cost at index %d = %.25f\n", i, elite[i].index, elite[i].cost);
		i++;
	}
}

int			videur(double newcost, t_pop *elite, int below)
{
	int				i;
	static double	taux = 0.0001;

	i = 0;
	if (below == 1)
		taux *= 10;
	while (i < 100)
	{
		if ((long int)(newcost * taux) == (long int)(elite[i].cost * taux))
			return (0);
		i++;
	}
	return (1);
}

t_pop		*get_elite(t_pop *pop, int under)
{
	int		i;
	int		j;
	t_pop	*elite;

	i = 0;
	if (!(elite = (t_pop*)malloc(sizeof(t_pop) * ELITESIZE)))
		return (NULL);
	init_elite(elite, pop);
	while (i < POPSIZE)
	{
		j = 0;
		while (j < ELITESIZE)
		{
			if (pop[i].cost < elite[j].cost)
			{
				if (videur(pop[i].cost, elite, under) == 1)
					push_in(pop[i], elite, j, i);
				j = 100;
			}
			j++;
		}
		i++;
	}
	get_elite_config(elite, pop);
	add_rand_to_pop(elite, under);
	return (elite);
}
