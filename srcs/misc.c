/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 10:57:20 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/04 16:56:11 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

_Noreturn void			fdf_errhdl(const char *line, int y)
{
	ft_dprintf(STDERR_FILENO, "fdf: parsing error, line[%d]: %s\n", y, line);
	exit(EXIT_FAILURE);
}

void					vdtor(void *data, va_list ap)
{
	t_flag		flag;

	flag = va_arg(ap, t_flag);
	if (flag == E_FILE)
		ft_strdel((char **)data);
	else if (flag == E_VARY)
		ft_memdel((void **)&*(t_vec4 **)data);
}
