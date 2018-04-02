/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 21:35:11 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/02 12:52:11 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include "libft.h"
# include "mlx.h"

# define WIN_X 1200
# define WIN_Y 600
# define WIN_TITLE "FdF - A wireframe renderer, by Jon Finkel"

typedef struct		s_fdf
{
	short			height;
	short			width;
	t_mlx			mlx;
	t_vec4			**vec;
}					t_fdf;

_Noreturn void		fdf_errhdl(const char *line, int y);
void				vdtor(void *data);

#endif
