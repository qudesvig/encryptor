/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 12:33:57 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/01 17:28:28 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

void		put_dbltab(double *tab, unsigned int size)
{
	unsigned int i;

	i = 0;
	while (i < size)
	{
		printf("%.25f\n", tab[i]);
		i++;
	}
}

int			is_under(double new, double last)
{
	double	max;
	double	min;

	max = 10000000;
	min = 0.00001;
	while (max > min)
	{
		if (new > max && last < max)
			return (1);
		max /= 4;
	}
	return (0);
}

