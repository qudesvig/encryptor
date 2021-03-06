/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_neurone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 15:31:20 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/29 15:07:16 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libia.h"

int					init_neurone(t_neurone *n, int nb_weight, double (*f)(double))
{
	int		i;

	i = 0;
	n->act = f;
	n->in = 0;
	n->in = 0;
	n->bias = BIAS;
	n->nb_out = nb_weight;
	if (!(n->weight = (long double*)malloc(sizeof(long double) * nb_weight)))
		return (-1);
	while (i < nb_weight)
	{
		n->weight[i] = rand_dbl(-5, 5);
		i++;
	}
	return (0);
}
