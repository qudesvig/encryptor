/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encryptor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:55:35 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/01 15:31:37 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCRYPTOR_H
# define ENCRYPTOR_H

# include "../libia/includes/libia.h"
# include "../libft/libft.h"
# define PUT ft_putendl("there");

double			*irc_test(t_netw *n);
void			multi_encryptor(t_netw *n);
void			init_encr(void);
void			tabldbl_bzero(long double *tab, int size);

double			*fill_data(double *data);
double			*init_bias(double *bias);
int				*init_layer_size(int *layer_size);

int				genetic_training(t_netw *n, double **data);
void			gang_bang(t_pop *elit, t_pop *pop, int under);
double			*evolve_weights(int n, double *weights, int under);
double			*evolve_bias(int n, double *bias, int under);
t_pop			*get_elite(t_pop *pop, int under);
int				is_under(double new, double last);

void			put_dbltab(double *tab, unsigned int size);
void		display_elite(t_pop *elite);
#endif
