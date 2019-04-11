/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:30:59 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/11 16:36:43 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

void	back_prop(t_netw *n, double *out)
{
	int		i;
	double	error;

	(void)n;
	(void)out;
	i = 0;
	//error for 1st output
	while (i < NB_OUTPUT)
	{
		error = (out[i] - n->input[i]) * (out[i] - n->input[i]) / 2;
		printf("error for %d out = %f : out = %f in = %f\n", i, error, out[i], n->input[i]);
		i++;
	}
}
