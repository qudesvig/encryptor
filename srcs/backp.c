/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:30:59 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/12 16:41:57 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double	ft_cost_fct(double *out, double *in)
{
	double	cost;
	int		i;

	cost = 0;
	i = 0;
	while (i < NB_INPUT)
	{
		cost += (out[i] - in[i]) * (out[i] - in[i]);
		i++;
	}
	return (cost);
}

void	back_prop(t_netw *n, double *data, double *out)
{
	double	cost;
	int		i;
	
	i = 0;
	while (i < NB_INPUT)
	{
		cost = (out[i] - data[i]) * (out[i] - data[i]);
		
		i++;
	}
}
