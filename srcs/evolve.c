/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evolve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:34:39 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/03 18:47:50 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double		*evolve_weights(int n, double *base, int comeback, int nb_change)
{
	int				i;
	int				j;
	static double	lr = 2;
	double			ch;

	if (comeback > 20)
		lr = 4;
	else
		lr = 2;
	j = 0;
	i = n % (NB_WEIGHT - nb_change);
	while (j < nb_change)
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
	static double	lr = 1;

	if (comeback > 20)
		lr = 3;
	else
		lr = 1;
	j = 0;
	i = n % (NB_BIAS - nb_change);
	while (j < nb_change)
	{
		base[i + j] += rand_dbl(-1 * lr, 1 * lr);
		j++;
	}
	return (base);
}
