/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 12:33:57 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/06 16:48:11 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

int			is_under(double new, double last)
{
	double	max;
	double	min;

	max = 1000;
	min = 0.00001;
	printf("is under for %f && %f\n", new, last);
	while (max > min)
	{
		if (new < max && last > max)
		{
			ft_putendl("return (1)");
			return (1);
		}
		max /= 1.2;
	}
	ft_putendl("return (0)");
	return (0);
}

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

double		*add_dbltab_rand(double *dest, unsigned int size)
{
	unsigned int i;

	i = 0;
	while (i < size)
	{
		dest[i] += rand_dbl(-0.5, 0.5);
		i++;
	}
	return (dest);
}
