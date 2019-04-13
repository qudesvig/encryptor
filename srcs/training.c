/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:40:56 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/12 16:42:01 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double		training(t_netw *n, double **data)
{
	int		epoch;
	int		i;
	int		j;
	double	*out;
	double	*weight_grad;

	i = 0;
	j = 0;
	while (i * 100 < DATASIZE)
	{
		epoch = 0;
		while (epoch < 100)
		{
			j = 0;
			while (j < 100)
			{
				fill_data_in(n, data[i * 100 + j]);
				out = firing(n);
				calc_gradient(data[i * 100 + j], out, weight_grad);
				j++;
			}
			apply_grad(n, weight_grad, 0.1);
			epoch++;
		}
		i++;
	}
	return (fitness);
}
