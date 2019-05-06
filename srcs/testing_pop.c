/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_pop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 21:58:59 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/04 07:10:45 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

void		*test_pop_pth(void *param)
{
	
	while (TH->i < POPSIZE / NB_THREAD)
	{
		TH->j = 0;
		TH->pop[TH->i + TH->index].cost = 0;
		apply_weight(&TH->n, TH->pop[TH->i + TH->index].weights);
		apply_bias(&TH->n, TH->pop[TH->i + TH->index].bias);
		while (TH->j < DATASIZE)
		{
			fill_nw(TH->data[TH->j], &TH->n);
			firing(&TH->n);
			TH->pop[TH->i + TH->index].cost += ft_calc_cost(&TH->n, TH->data[TH->j]);
			TH->j++;
		}
		TH->pop[TH->i + TH->index].cost /= DATASIZE;
		TH->i++;
	}
	pthread_exit(NULL);
}

void		init_test_pth(t_fire *pth, t_pop *pop, double **data, int comeback, int i)
{
	pth->pop = pop;
	pth->data = data;
	pth->comeback = comeback;
	pth->index = i * (POPSIZE / NB_THREAD);
	pth->i = 0;
	prepare_init_netw(&(pth->n), data[0]);
}

t_pop		*test_pop(t_pop *pop, double **data, int comeback)
{
	int		i;
	t_fire	f[NB_THREAD];

	i = 0;
	while (i < NB_THREAD)
	{
		init_test_pth(&f[i], pop, data, comeback, i);
		i++;
	}
	i = 0;
	while (i < NB_THREAD)
	{
		pthread_create(&(f[i].pth), NULL, test_pop_pth, (void*)&f[i]);
		i++;
	}
	i = 0;
	while (i < NB_THREAD)
	{
		pthread_join(f[i].pth, NULL);
		free_nw(&f[i].n);
		i++;
	}
	return (get_elite(pop, comeback));
}
