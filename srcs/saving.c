/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:00:59 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/06 14:19:42 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

int			export_weight_tab(double *tab, char *name)
{
	int		i;
	int		fd;

	if (!(fd = open(name, O_CREAT | O_WRONLY, 0777)))
		return (-1);
	i = -1;
	while (++i < NB_WEIGHT)
		dprintf(fd, "%.50f\t", tab[i]);
	close(fd);
	return (0);
}

void		saving_config(t_pop best, t_netw *n, int mod)
{
	apply_weight(n, best.weights);
	apply_bias(n, best.bias);
	if (mod == 0)
	{
		export_weight(n, "config/weights");
		export_bias(n, "config/bias");
	}
	else if (mod == 1)
	{
		export_weight_tab(best.weights, "config/weightssave");
		export_bias(n, "config/biassave");
	}
	else
	{
		export_weight_tab(best.weights, "config/weightssaveth");
		export_bias(n, "config/biassaveth");
	}
}
