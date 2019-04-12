/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   database.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:32:38 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/12 15:14:53 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

double	**creat_database(double max, double min)
{
	double	**data;
	int		i;
	int		j;

	if (!(data = (double**)malloc(sizeof(double*) * DATASIZE)))
		return (NULL);
	i = 0;
	while (i < DATASIZE)
	{
		j = 0;
		if (!(data[i] = (double*)malloc(sizeof(double) * NB_INPUT)))
			return (NULL);
		while (j < NB_INPUT)
		{
			data[i][j] = (rand() / (double)RAND_MAX) * (max - min) + min;
			j++;
		}
		i++;
	}
	return (data);
}
