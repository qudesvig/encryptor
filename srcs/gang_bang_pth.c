/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gang_bang_pth.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 00:20:21 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/07 00:35:49 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

void		*gb_th(void *param)
{
	GB->i = 0;
	while (GB->i < ELITESIZE / 4)
	{
		GB->nbch = 1;
		GB->j = 1;
		if (GB->start < POPSIZE)
		{
			GB->pop[GB->start].weights = tabdbl_cpy(GB->elite[GB->i + GB->index].weights, GB->pop[GB->start].weights, NB_WEIGHT);
			GB->pop[GB->start].bias = tabdbl_cpy(GB->elite[GB->i + GB->index].bias, GB->pop[GB->start].bias, NB_BIAS);
		}
		while (GB->j < POPSIZE / ELITESIZE + GB->tx && GB->start + GB->j < POPSIZE)
		{
			if (GB->j % (POPSIZE / (ELITESIZE / 4)) == 0)
				GB->nbch++;
			GB->pop[GB->start + GB->j].weights = tabdbl_cpy(GB->elite[GB->i + GB->index].weights, GB->pop[GB->start + GB->j].weights, NB_WEIGHT);
			GB->pop[GB->start + GB->j].weights = evolve_weights(GB->i + GB->j, GB->pop[GB->start + GB->j].weights, GB->comeback, GB->nbch);
			GB->pop[GB->start + GB->j].bias = tabdbl_cpy(GB->elite[GB->i + GB->index].bias, GB->pop[GB->start + GB->j].bias, NB_BIAS);
			GB->pop[GB->start + GB->j].bias = evolve_bias(GB->i + GB->j, GB->pop[GB->start + GB->j].bias, GB->comeback, GB->nbch);
			GB->j++;
		}
		if (GB->i % 5 == 0 && GB->tx > 0)
			GB->tx--;
		GB->start += GB->j;
		GB->i++;
	}
	pthread_exit(NULL);
}

void		init_gb_th(t_gb *th, t_pop *elite, t_pop *pop, int quart, int comeback)
{
	th->i = 0;
	th->index = quart * (ELITESIZE / 4);
	th->elite = elite;
	th->pop = pop;
	th->comeback = comeback;
	if (th->index == 0)
	{
		th->start = 0; 
		th->tx = 10;
	}
	else
		th->tx = 0;
	if (th->index == 250)
		th->start = 25110; 
	if (th->index == 500)
		th->start = 50110; 
	if (th->index == 750)
		th->start = 75110; 
}

void		gang_bang_pth(t_pop *elite, t_pop *pop, int comeback)
{
	int		i;
	t_gb	pth[NB_THREAD];

	i = 0;
	while (i < NB_THREAD)
	{
		init_gb_th(&pth[i], elite, pop, i, comeback);
		i++;
	}
	i = 0;
	while (i < NB_THREAD)
	{
		pthread_create(&(pth[i].pth), NULL, gb_th, (void*)&pth[i]);
		i++;
	}
	i = 0;
	while (i < NB_THREAD)
	{
		pthread_join(pth[i].pth, NULL);
		i++;
	}
	gangbang_rand(elite, pop, pth[3].start, comeback);
	free_elite(elite);
}
