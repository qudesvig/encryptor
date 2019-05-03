/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 23:20:30 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/03 23:21:34 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

void		free_data(double **data)
{
	int		i;

	i = 0;
	while (i < DATASIZE)
	{
		free(data[i]);
		i++;
	}
	free(data);
}

void		free_elite(t_pop *elite)
{
	int		i;

	i = 0;
	while (i < ELITESIZE)
	{
		free(elite[i].weights);
		free(elite[i].bias);
		i++;
	}
	free(elite);
}
