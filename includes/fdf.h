/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 21:35:11 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/18 11:36:03 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include "libft.h"

typedef struct		s_fdf
{
	t_vec4			*vec;
}					t_fdf;

_Noreturn void		fdf_errhdl(const char *line, int x, int y);
void				vdtor(void *data);

#endif
