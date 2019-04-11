/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:50:21 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/11 14:57:23 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libia.h"

double		id_dbl(double input)
{
	return (input);
}

double	 sigmoid(double x)
{	
    float exp_value;
    float return_value;

	exp_value = exp((double) -x);
	return_value = 1 / (1 + exp_value);
	return (return_value);
}

double		heaviside_dbl(double input)
{
	return ((input < 0) ? 0 : 1);
}
