/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encryptor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:55:35 by qudesvig          #+#    #+#             */
/*   Updated: 2019/04/21 18:40:36 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCRYPTOR_H
# define ENCRYPTOR_H

# include "../libia/includes/libia.h"
# include "../libft/libft.h"
# define PUT ft_putendl("there");
# define DATASIZE 10000
# define BUFF_RAND 4194304

double			*encryptor(t_netw *n);
void			init_encr(void);
double			rand_dbl(double min, double max);
void			tabdbl_bzero(long double *tab, int size);

double			*fill_data(double *data);
void			fill_nw(double *data, t_netw *n);
double			*init_bias(double *bias);
int				*init_layer_size(int *layer_size);
void			reset_nw(t_netw *n);

void			apply_grad(t_netw *n, long double *grad, double lr);
long double		*back_p(double **data, t_netw *n, long double *grad, long double *cost);

void			training(t_netw *n, double **data);

double			**creat_database(double max, double min);

long double		display_total_cost(long double *cost);
#endif
