/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encryptor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:55:35 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/04 00:52:22 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCRYPTOR_H
# define ENCRYPTOR_H

# include "../libia/includes/libia.h"
# include "../libft/libft.h"
# define PUT ft_putendl("there");
# define GB ((t_gb*)param)
typedef struct	s_gb
{
	pthread_t	pth;
	//for testing pop
	int			i;
	int			j;
	int			start;
	int			nbch;
	int			tx;
	int			comeback;
	int			index;
	t_pop		*pop;
	t_pop		*elite;
}				t_gb;

double			*irc_test(t_netw *n);
void			multi_encryptor(t_netw *n);
void			init_encr(int mod);
void			tabldbl_bzero(long double *tab, int size);

double			*fill_data(double *data);
double			*init_bias(double *bias);
int				*init_layer_size(int *layer_size);
t_netw			*prepare_init_netw(t_netw *n, double *data);

int				genetic_training(t_netw *n, double **data);
void			gang_bang(t_pop *elit, t_pop *pop, int comeback);
void			gangbang_rand(t_pop *elite, t_pop *pop, int start, int comeback);
double			*evolve_weights(int n, double *weights, int comeback, int nb_change);
double			*evolve_bias(int n, double *bias, int comeback, int nb_change);
t_pop			*get_elite(t_pop *pop, int under);
int				is_under(double new, double last);

void			gang_bang_pth(t_pop *elite, t_pop *pop, int comeback);

void			put_dbltab(double *tab, unsigned int size);
double			*add_dbltab_rand(double *dest, unsigned int size);
void			display_elite(t_pop *elite);

void			saving_for_cmb(t_pop *dest, t_pop src);
void			reinit_pop(t_pop base, t_pop *pop);

t_pop			*test_pop(t_pop *pop, double **data, int comeback);

void			saving_config(t_pop best, t_netw *n, int mod);
int				export_weight_tab(double *tab, char *name);

void			free_elite(t_pop *elite);
void			free_data(double **data);
#endif
