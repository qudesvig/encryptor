/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   database.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:32:38 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/01 16:46:07 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libia.h"

double				rand_dbl(double min, double max)
{
	static char        buff[BUFF_RAND + 1];
	static int         index = 0;
	static int             fd = 0;
	double             percent;
	double             ret;

	if (fd == 0)
		fd = open("/dev/random", O_RDONLY);
	if (index > BUFF_RAND - 2)
		index = 0;
	if (index == 0)
	{

		if (read(fd, buff, BUFF_RAND) == -1)
			return (0);
		buff[BUFF_RAND] = '\0';
	}
	ret = (double)((double)buff[index] * (double)buff[index + 1]);
	percent = ret / 16129;
	ret = ((max - min) * percent);
	index += 2;
	return (ret);/*
					double range = (max - min);
					double div = RAND_MAX / range;
					return min + (rand() / div);*/

}

double				**creat_database(double max, double min)
{
	double		**data;
	int			i;
	int			j;

	if (!(data = (double**)malloc(sizeof(double*) * DATASIZE)))
		return (NULL);
	i = 0;
	while (i < DATASIZE)
	{
		if (!(data[i] = (double*)malloc(sizeof(double) * NB_INPUT)))
			return (NULL);
		j = 0;
		while (j < NB_INPUT)
		{
			data[i][j] = rand_dbl(min, max);
			j++;
		}
		i++;
	}
	return (data);
}

double			**import_data(char *name)
{
	double **data;
	int		fd;
	int		i;
	int		j;
	char	*line;
	char	**input;

	i = 0;
	j = 0;
	if (!(fd = open(name, O_RDONLY)))
		return (NULL);
	if (!(data = (double**)malloc(sizeof(double*) * DATASIZE)))
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		input = ft_strsplit(line, '\t');
		j = 0;
		if (!(data[i] = (double*)malloc(sizeof(double) * NB_INPUT)))
			return (NULL);
		while (input[j])
		{
			data[i][j] = atof(input[j]);
			//			printf("data[%d][%d] = %.25f\n", i, j, data[i][j]);
			free(input[j]);
			j++;
		}
		ft_strdel(&line);
		free(input);
		i++;
	}
	return (data);
}

int				export_database(char *name, double **data)
{
	int		fd;
	int		i;
	int		j;

	if (!(fd = open(name, O_CREAT | O_WRONLY, 0777)))
		return (-1);
	i = 0;
	while (i < DATASIZE)
	{
		j = 0;
		while (j < NB_INPUT)
		{
			dprintf(fd, "%.50f\t", data[i][j]);
			j++;
		}
		dprintf(fd, "\n");
		i++;
	}
	return (0);
}
