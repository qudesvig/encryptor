/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_neurone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 15:31:20 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/21 19:26:02 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libia.h"
#define BUFF_RAND 1000

static double		rand_dbl(double min, double max)
{
	char		buff[BUFF_RAND + 1];
	static int 		index = 0;
	int 			fd;
	double 			percent;
	double 			ret;

	if (index > BUFF_RAND - 2)
		index = 0;
	if (index == 0)
	{
		fd = open("/dev/random", O_RDONLY);
		if (read(fd, buff, BUFF_RAND) == -1)
			return (0);
		buff[BUFF_RAND] = '\0';
		close (fd);
	}
	ret = (double)((double)buff[index] * (double)buff[index + 1]);
	percent = ret / 32258;
	ret = (max - min) * percent;
	index += 2;
	return (ret);
}

int					init_neurone(t_neurone *n, int nb_weight, double (*f)(double))
{
	int		i;

	i = 0;
	n->act = f;
	n->in = 0;
	n->in = 0;
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
