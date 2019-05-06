/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:35:19 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/07 00:03:17 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

void		init_elite(t_pop *elite, t_pop *pop)
{
	int		i;

	i = 0;
	while (i < ELITESIZE)
	{
		elite[i].cost = 1000000000000;
		elite[i].index = -1;
		elite[i].weights = tabdbl_dup(pop[i].weights, NB_WEIGHT);
		elite[i].bias = tabdbl_dup(pop[i].bias, NB_BIAS);
		i++;
	}
}

void		push_in(t_pop new, t_pop *elite, int i, int pos, int mod)
{
	int		j;

	j = ELITESIZE - 2;
	while (j >= i && mod == 0)
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
	while (i < ELITESIZE)
	{
		if (elite[i].index != -1)
		{
			elite[i].weights = tabdbl_dup(pop[elite[i].index].weights, NB_WEIGHT);
			elite[i].bias = tabdbl_dup(pop[elite[i].index].bias, NB_NEURONE - NB_INPUT);
		}
		i++;
	}
}

void		display_elite(t_pop *elite)
{
	int 	i;

	i = 0;
	while (i < ELITESIZE && elite[i].index != -1)
	{
		printf("elite[%d].cost at index %d = %.25f\n", i, elite[i].index, elite[i].cost);
		i++;
	}
}

int			videur(double newcost, t_pop *elite, int j, int below)
{
	static double	taux = 10;

	if (newcost > elite[0].cost * 2)
		return (-1);
	if (below > 10)
		taux = 50;
	else
		taux = 10;
	while (j > 0)
	{
		if ((long int)(newcost * taux) == (long int)(elite[j].cost * taux))
			return (-1);
		else if ((long int)(newcost * taux) > (long int)(elite[j].cost * taux))
			return (0);
		j--;
	}
	return (1);
}

t_pop		*get_elite(t_pop *pop, int comeback)
{
	int		i;
	int		j;
	int		pass;
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
				if ((pass = videur(pop[i].cost, elite, j, comeback)) == 1)
					push_in(pop[i], elite, j, i, 0);
				else if (pass == 0)
					push_in(pop[i], elite, j, i, 1);
				j = ELITESIZE;
			}
			j++;
		}
		i++;
	}
	get_elite_config(elite, pop);
	return (elite);
}
