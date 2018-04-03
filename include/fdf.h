/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 21:35:11 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/04 00:37:39 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include "libft.h"
# include "mlx.h"

# define WIN_X 1200
# define WIN_Y 900
# define WIN_TITLE "FdF - A wireframe renderer, by Jon Finkel"

typedef enum		e_flag
{
	E_FILE,
	E_IMG,
	E_WIN,
	E_VARY
}					t_flag;

typedef struct		s_fdf
{
	bool			cinema;
	short			c_x;
	short			c_y;
	short			c_z;
	short			height;
	short			width;
	size_t			size;
	t_mlx			mlx;
	t_vec4			*origin;
	t_vec4			*pos;
	t_vec4			**vec;
}					t_fdf;

_Noreturn void		fdf_errhdl(const char *line, int y);
void				get_data(t_fdf *fdf, const int fd);
void				key_hook(int key, t_fdf *fdf);
void				output(t_mlx *mlx, const t_fdf fdf);
void				terminate(t_fdf *fdf);
void				vdtor(void *data, va_list ap);

#endif
