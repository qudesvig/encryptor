/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudesvig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:46:23 by qudesvig          #+#    #+#             */
/*   Updated: 2019/05/03 23:05:28 by qudesvig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/encryptor.h"

int	main(int ac, char **av)
{
	char *opt;

	opt = get_opt(ac, av, "t");
	if (opt && opt[0] == 't')
		init_encr(1);
	else
		init_encr(0);
	if (opt)
		free(opt);
	return (0);
}
