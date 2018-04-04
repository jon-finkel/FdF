/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 13:17:30 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/04 21:54:18 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define _5D_MODE 5

static void			cinema(t_fdf *fdf, const int key)
{
	if (key == X_KEY_0)
		fdf->cinema = (fdf->cinema ? false : true);
	else if (key == X_KEY_1)
		fdf->c_x += (fdf->c_x == 1 ? 179 : 5);
	else if (key == X_KEY_2 && (fdf->c_x > 5 || fdf->c_x == 1))
		fdf->c_x -= (fdf->c_x == 1 ? -179 : 5);
	else if (key == X_KEY_3)
		fdf->c_y += (fdf->c_y == 1 ? 179 : 5);
	else if (key == X_KEY_4 && (fdf->c_y > 5 || fdf->c_y == 1))
		fdf->c_y -= (fdf->c_y == 1 ? -179 : 5);
	else if (key == X_KEY_5)
		fdf->c_z += (fdf->c_z == 1 ? 179 : 5);
	else if (key == X_KEY_6 && (fdf->c_z > 5 || fdf->c_z == 1))
		fdf->c_z -= (fdf->c_z == 1 ? -179 : 5);
	else if (key == X_KEY_7)
		fdf->c_x = 1;
	else if (key == X_KEY_8)
		fdf->c_y = 1;
	else if (key == X_KEY_9)
		fdf->c_z = 1;
	else if (key == X_KEY_BACKTICK && (fdf->c_x = _5D_MODE))
	{
		fdf->c_y = _5D_MODE;
		fdf->c_z = _5D_MODE;
	}
}

static void			spin(t_vec4 **avec, const t_fdf fdf, const int key)
{
	if (key == X_KEY_L_ARROW)
		ft_veciter(avec, ft_m4roty(M_PI / -60), fdf.size);
	else if (key == X_KEY_R_ARROW)
		ft_veciter(avec, ft_m4roty(M_PI / 60), fdf.size);
	else if (key == X_KEY_U_ARROW)
		ft_veciter(avec, ft_m4rotx(M_PI / -60), fdf.size);
	else if (key == X_KEY_D_ARROW)
		ft_veciter(avec, ft_m4rotx(M_PI / 60), fdf.size);
	else if (key == X_KEY_Z)
		ft_veciter(avec, ft_m4rotz(M_PI / -60), fdf.size);
	else if (key == X_KEY_C)
		ft_veciter(avec, ft_m4rotz(M_PI / 60), fdf.size);
}

static void			move(t_fdf *fdf, const int key, const int value)
{
	if (key == X_KEY_A)
		fdf->pos->x -= value;
	else if (key == X_KEY_D)
		fdf->pos->x += value;
	else if (key == X_KEY_W)
		fdf->pos->y -= value;
	else if (key == X_KEY_S)
		fdf->pos->y += value;
}

static void			transfo(t_fdf *fdf, int key, const uint8_t value)
{
	t_mlx		*mlx;

	mlx = &fdf->mlx;
	ftx_veccenter(fdf->vec, fdf->size, *fdf->origin);
	if ((key >= X_KEY_A && key <= X_KEY_D) || key == X_KEY_W)
		move(fdf, key, value);
	else if (key == X_KEY_MINUS)
		ft_veciter(fdf->vec, ft_m4scale(0.9f, 0.9f, 0.9f), fdf->size);
	else if (key == X_KEY_EQUAL)
		ft_veciter(fdf->vec, ft_m4scale(1.1f, 1.1f, 1.1f), fdf->size);
	else if (key == X_KEY_SPACE)
	{
		ftx_clearimg(_MLX_IMG);
		mlx_put_image_to_window(_MLX_ID, _MLX_WIN_ID, _MLX_IMG_ID, 0, 0);
		fdf->pos->x = WIN_X / 2;
		fdf->pos->y = WIN_Y / 2;
	}
	else
		spin(fdf->vec, *fdf, key);
	ftx_veccenter(fdf->vec, fdf->size, *fdf->pos);
}

void				key_hook(int key, t_fdf *fdf)
{
	static uint8_t		value = 5;

	if (key == X_KEY_ESCAPE)
		terminate(fdf);
	else if (key == X_KEY_Q && value)
		value -= 5;
	else if (key == X_KEY_E && value < UCHAR_MAX)
		value += 5;
	else if ((key >= X_KEY_1 && key <= X_KEY_0) || key == X_KEY_BACKTICK)
		cinema(fdf, key);
	else
		transfo(fdf, key, value);
	output(&fdf->mlx, *fdf);
}
