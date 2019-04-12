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
	double	fitness;
	int		i;
	int		j;
	double	*out;

	i = 0;
	j = 0;
	fitness = 0;
	while (i * 100 < DATASIZE)
	{
		j = 0;
		while (j < 100)
		{
			fill_data_in(n, data[i * 100 + j]);
			out = firing(n);
			back_prop(n, data[i * 100 + j], out);
			j++;
		}
		i++;
	}
	return (fitness);
}
