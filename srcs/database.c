/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   database.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:32:38 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/23 15:52:15 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

static double		rand_dbltmp(double min, double max)
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

double	**creat_database(double max, double min, int mod)
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
		while (j < ((mod == 0) ? NB_INPUT : NB_INPUT2))
		{
			data[i][j] = rand_dbltmp(min, max);
			//printf("data[%d][%d] = %.100f\n", i, j, data[i][j]);
			j++;
		}
		i++;
	}
	return (data);
}
