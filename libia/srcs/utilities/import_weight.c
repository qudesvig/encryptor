/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_weight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 20:31:27 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/01 15:52:52 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libia.h"

double		*import_weight(char *file)
{
	int		fd;
	int		i;
	int		j;
	int		k;
	char	*line;
	char	**weight;
	double	*ret;

	if (!(fd = open(file, O_RDONLY)))
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	if (!(ret = (double*)malloc(sizeof(double) * NB_WEIGHT)))
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		weight = ft_strsplit(line, '\t');
		j = 0;
		while (weight[j])
		{
			ret[k] = atof(weight[j]);
			free(weight[j]);
			k++;
			j++;
		}
		ft_strdel(&line);
		free(weight);
		i++;
	}
	return (ret);
}

double		*import_bias(char *file)
{
	int		fd;
	int		i;
	int		j;
	int		k;
	char	*line;
	char	**bias;
	double	*ret;

	if (!(fd = open(file, O_RDONLY)))
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	if (!(ret = (double*)malloc(sizeof(double) * NB_BIAS)))
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		bias = ft_strsplit(line, '\t');
		j = 0;
		while (bias[j])
		{
			ret[k] = atof(bias[j]);
			free(bias[j]);
			k++;
			j++;
		}
		ft_strdel(&line);
		free(bias);
		i++;
	}
	return (ret);
}
