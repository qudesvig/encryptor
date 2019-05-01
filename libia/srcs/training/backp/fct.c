/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 15:25:15 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/29 18:48:05 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libia.h"

int			get_weight_index(int l, t_netw *n)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < l - 1)
	{
		ret += n->layer_size[i] * n->layer_size[i + 1];
		i++;
	}
	return (ret);
}

void		tabdbl_bzero(double *tab, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		tab[i] = 0;
		i++;
	}
}

void		tabldbl_bzero(long double *tab, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		tab[i] = 0;
		i++;
	}
}

double		*tabdbl_dup(double *srcs, unsigned int size)
{
	unsigned int	i;
	double			*dest;

	i = 0;
	if (!(dest = (double*)malloc(sizeof(double) * size)))
		return (NULL);
	while (i < size)
	{
		dest[i] = srcs[i];
		i++;
	}
	return (dest);
}

double		*tabdbl_cpy(double *srcs, double *dest, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		dest[i] = srcs[i];
		i++;
	}
	return (dest);
}
