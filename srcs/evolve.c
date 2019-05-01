/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evolve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:34:39 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/01 17:28:08 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double		*evolve_weights(int n, double *base, int under)
{
	int		i;
	static int lr = 2;
	double		ch;

	if (under == 1)
		lr /= 2;
	i = n % NB_WEIGHT;
	ch = rand_dbl((-1 * lr), (1 * lr));
	base[i] += ch;
	return (base);
}

double		*evolve_bias(int n, double *base, int under)
{
	int			i;
	static int	lr = 4;

	if (under == 1)
		lr /= 2;
	i = n % NB_BIAS;
	base[i] += rand_dbl(-1 * lr, 1 * lr);
	return (base);
}
