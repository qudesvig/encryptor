/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encryptor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:55:35 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/17 22:04:20 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCRYPTOR_H
# define ENCRYPTOR_H

# include "../libia/includes/libia.h"
# include "../libft/libft.h"
# define PUT ft_putendl("there");
# define DATASIZE 10
# define BUFF_RAND 1000

double			*encryptor(t_netw *n);
void			init_encr(void);
double			rand_dbl(double min, double max);

double			*fill_data(double *data);
double			*init_bias(double *bias);
int				*init_layer_size(int *layer_size);

long double		**computing_data(t_netw *n, double **data, long double **out);
long double		*ft_cost(long double **out, double **data, long double *cost);
long double		*calc_gradient(t_netw *n, long double **out, long double **data, long double *weight_grad);
void			apply_grad(t_netw *n, long double *grad, double lr);

void			training(t_netw *n, double **data);

double			**creat_database(double max, double min);
#endif
