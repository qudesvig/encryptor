/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gang_bang.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:30:07 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/01 16:48:45 by qudesvig         ###   ########.fr       */
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

void		*pth_gb(void *param)
{
	while (TH->i + TH->index < POPSIZE / NB_THREAD)
	{
		if (TH->i + TH->index % POPSIZE == 100)
			TH->acte++;
		TH->pop[TH->i + TH->index].cost = 0;
		TH->pop[TH->i + TH->index].weights = tabdbl_cpy(TH->elit[TH->acte].weights, TH->pop[TH->i + TH->index].weights, NB_WEIGHT);
		TH->pop[TH->i + TH->index].bias = tabdbl_cpy(TH->elit[TH->acte].bias, TH->pop[TH->i + TH->index].bias, NB_BIAS);
		if (TH->i + TH->index < NB_NEURONE)
			TH->pop[TH->i + TH->index].weights = evolve_weights(TH->i + TH->index, TH->pop[TH->i + TH->index].weights, TH->under);
		else
			TH->pop[TH->i + TH->index].bias = evolve_bias(TH->i + TH->index, TH->pop[TH->i + TH->index].bias, TH->under);
		TH->i++;
	}
	pthread_exit(NULL);
}

void		init_pth(t_fire *pth, t_pop *elite, t_pop *pop, int under, int i)
{
	pth->i = 0;
	pth->index = i * (POPSIZE / NB_THREAD);
	pth->acte = pth->index / 100;
	pth->under = under;
	pth->elit = elite;
	pth->pop = pop;
}

void		gang_bang(t_pop *elit, t_pop *pop, int under)
{
	t_fire	f[NB_THREAD];
	int		i;

	i = 0;
	while (i < NB_THREAD)
	{
		init_pth(&f[i], elit, pop, under, i);
		i++;
	}
	i = 0;
	while (i < NB_THREAD)
	{
		ft_putendl("there2");
		pthread_create(&(f[i].pth), NULL, pth_gb, (void*)&f[i]);
		i++;
	}
	i = 0;
	while (i < NB_THREAD)
	{
		ft_putendl("there3");
		pthread_join(f[i].pth, NULL);
		i++;
	}
}
