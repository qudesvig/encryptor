/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_weight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:57:04 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/30 18:52:07 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libia.h"

int			export_weight(t_netw *n, char *name)
{
	int		i;
	int		j;
	int		k;
	int		fd;

	if (!(fd = open(name, O_CREAT | O_WRONLY, 0777)))
		return (-1);
	i = -1;
	while (++i < NB_LAYER - 1)
	{
		j = -1;
		while (++j < n->layer_size[i])
		{
			k = -1;
			while (++k < n->layer_size[i + 1])
				dprintf(fd, "%.50Lf\t", n->netw[i][j].weight[k]);
		}
		dprintf(fd, "\n");
	}
	close(fd);
	return (0);
}

double		*get_weights(t_netw *n)
{
	int		i;
	int		j;
	int		k;
	int		l;
	double	*weights;

	l = 0;
	k = 0;
	if (!(weights = (double*)malloc(sizeof(double) * NB_WEIGHT)))
		return (NULL);
	while (l < NB_LAYER - 1)
	{
		i = 0;
		while (i < n->layer_size[l])
		{
			j = 0;
			while (j < n->layer_size[l + 1])
			{
				weights[k] = n->netw[l][i].weight[j];
				j++;
				k++;
			}
			i++;
		}
		l++;
	}
	return (weights);
}

double		*get_bias(t_netw *n)
{
	int		i;
	int		k;
	int		l;
	double	*bias;

	l = 1;
	k = 0;
	if (!(bias = (double*)malloc(sizeof(double) * (NB_NEURONE - NB_INPUT))))
		return (NULL);
	while (l < NB_LAYER)
	{
		i = 0;
		while (i < n->layer_size[l])
		{
			bias[k] = n->netw[l][i].bias;
			k++;
			i++;
		}
		l++;
	}
	return (bias);
}

int			export_bias(t_netw *n, char *name)
{
	int		i;
	int		j;
	int		fd;

	if (!(fd = open(name, O_CREAT | O_WRONLY, 0777)))
		return (-1);
	i = 0;
	while (++i < NB_LAYER)
	{
		j = -1;
		while (++j < n->layer_size[i])
		{
				dprintf(fd, "%.50f\t", n->netw[i][j].bias);
		}
		dprintf(fd, "\n");
	}
	close(fd);
	return (0);
}
