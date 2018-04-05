/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 21:35:11 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/05 16:48:50 by nfinkel          ###   ########.fr       */
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
# define _WHITE 0xffffffff

typedef enum		e_flag
{
	E_BLUR,
	E_CLIP
}					t_flag;

typedef struct		s_fdf
{
	bool			cinema;
	bool			psy;
	double			zoom;
	short			rot_x;
	short			rot_y;
	short			rot_z;
	short			spd_x;
	short			spd_y;
	short			spd_z;
	short			height;
	short			width;
	size_t			size;
	t_mlx			*mlx;
	t_p2			origin;
	t_p2			pos;
	t_vec4			**vec;
	uint8_t			move_speed;
}					t_fdf;

void				fdf_errhdl(const char *line, const int y);
void				get_data(t_fdf *fdf, const int fd);
int					key_hook(int key, t_fdf *fdf);
void				output(t_mlx *mlx, const t_fdf fdf, const t_flag flag);
void				output_data(const t_mlx *mlx, const t_fdf fdf);
void				terminate(t_fdf *fdf);
void				vdtor(void *data);

#endif
