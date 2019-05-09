/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evolve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:34:39 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/09 04:49:53 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double		*evolve_weights(int n, double *base, int comeback, int nb_change)
{
	int				i;
	int				j;
	double			lr;
	double			ch;

	lr = 1;
	if (comeback > 10)
		lr = 0.05 / 16;
	else
		lr = 0.1 / 16;
	j = 0;
	i = n % (NB_WEIGHT - nb_change);
	while (j < nb_change && i + j < NB_WEIGHT && i + j > 0)
	{
		ch = rand_dbl((-1 * lr), (1 * lr));
		base[i + j] += ch;
		j++;
	}
	return (base);
}

double		*evolve_bias(int n, double *base, int comeback, int nb_change)
{
	int				i;
	int				j;
	double			lr;

	lr = 2;
	if (comeback > 10)
		lr = 0.05 / 8;
	else
		lr = 0.1 / 8;
	j = 0;
	i = n % (NB_BIAS - nb_change);
	while (j < nb_change && i + j < NB_BIAS && i + j > 0)
	{
		base[i + j] += rand_dbl(-1 * lr, 1 * lr);
		j++;
	}
	return (base);
}
