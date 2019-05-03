/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libia.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 14:04:23 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/03 16:52:35 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBIA_H
# define LIBIA_H
# include "../../libft/libft.h"
# include "neural_network.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <pthread.h>
# define TH ((t_fire*)param)
# define NB_THREAD 4

typedef	struct		s_neurone
{
	int				nb_out;
	//res of wi * xi + bias
	double			in;
	double			bias;
	//activating function
	double			(*act)(double);
	double			out;
	//weight to next layer
	long double		*weight;
}					t_neurone;

typedef struct	s_pop
{
	double		*weights;
	double		*bias;
	double		cost;
	int			index;
}				t_pop;

typedef struct		s_netw
{
	t_neurone		**netw;
	//size of each layer
	int				*layer_size;
	//data input
	double			*input;
	//bias per layer
	double			*bias;
	//data output
	double			*out;
	int				nbth;
}					t_netw;

//struct for multithread firing
typedef struct		s_fire
{
	pthread_t		pth;
	//for testing pop
	int				i;
	int				j;
	int				comeback;
	int				index;
	t_pop			*pop;
	int				under;
	t_netw			n;
	double			**data;
}					t_fire;

//init env neural network
int					init_neurone(t_neurone *n, int nb_weight, double (*f)(double));
int					init_network(t_netw *n, double *data_in, int *layer_size, double *bias);
int					fill_data_in(t_netw *n, double *data_in);
int					free_nw(t_netw *n);
void				reset_nw(t_netw *n);

//activation function
double				id_dbl(double input);
double	 			sigmoid(double x);
double				sig_dbl(double input);
double				heaviside_dbl(double input);

void				firing(t_netw *n);
double				neurone_output(t_neurone n, int out);
void				apply_weight(t_netw *n, double *weight);
void				apply_bias(t_netw *n, double *bias);
void				fill_nw(double *data, t_netw *n);

//debug && debug fct
void				mapping_netw(t_netw n);
void				display_weight(t_netw n);
void				display_inputs(t_netw n);
void				display_outputs(t_netw n, int layer);

//save and load weight fct
int					export_bias(t_netw *n, char *name);
int					export_weight(t_netw *n, char *name);
double				*import_weight(char *file);
double				*get_weights(t_netw *n);
double				*get_bias(t_netw *n);
double				*import_bias(char *file);

//dataset fct
int					export_database(char *name, double **database);
double				**import_data(char *name);
double				**creat_database(double max, double min);
double				rand_dbl(double min, double max);

//Back propagation training mode
long double			*averaging_grad(long double *grad);
long double			ft_calc_cost(t_netw *n, double *target);
void				apply_grad(t_netw *n, long double *gradw, long double *gradb, double lr);
void				tabdbl_bzero(double *tab, int size);
void				tabldbl_bzero(long double *tab, int size);
int					get_weight_index(int l, t_netw *n);
void				chain_rule(t_netw *n, long double *gradw, long double *gradb, double *target, int l);
long double		 	*back_p(double **data, t_netw *n, long double *grad, long double *gradb, long double *cost);

//Utilities
double				*tabdbl_dup(double *srcs, unsigned int size);
double				*tabdbl_cpy(double *srcs, double *dest, unsigned int size);
#endif
