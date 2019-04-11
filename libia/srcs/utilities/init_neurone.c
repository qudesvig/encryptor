/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_neurone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 15:31:20 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/11 16:07:06 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libia.h"

int		init_neurone(t_neurone *n, int nb_weight, double (*f)(double))
{
	int		i;

	i = 0;
	n->act = f;
	n->in = 0;
	n->in = 0;
	n->nb_out = nb_weight;
	if (!(n->weight = (double*)malloc(sizeof(double) * nb_weight)))
		return (-1);
	while (i < nb_weight)
	{
		n->weight[i] = (rand() / (double)RAND_MAX) * (1 - -1) + -1;
		i++;
	}
	return (0);
}
