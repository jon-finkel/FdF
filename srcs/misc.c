/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 10:57:20 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/18 11:42:59 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void					vdtor(void *data)
{
	ft_strdel((char **)data);
}

_Noreturn void			fdf_errhdl(const char *line, int x, int y)
{
	ft_dprintf(STDERR_FILENO, "fdf: parsing error, line[%d]: %s\n", y, line);
	ft_dprintf(STDERR_FILENO, "%*.c{1c}%*s{eoc}\n", 28, ' ', x, "~^~");
	exit(EXIT_FAILURE);
}
