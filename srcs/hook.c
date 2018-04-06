/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 13:17:30 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/06 15:46:59 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define _ZOOM_MAX 909999

static void			cinema(t_fdf *fdf, const int key)
{
	if (key == X_KEY_0)
		fdf->cinema = (fdf->cinema ? false : true);
	else if (key == X_KEY_1)
		fdf->spd_x += (fdf->spd_x == 1 ? 179 : 5);
	else if (key == X_KEY_2 && (fdf->spd_x > 5 || fdf->spd_x == 1))
		fdf->spd_x -= (fdf->spd_x == 1 ? -179 : 5);
	else if (key == X_KEY_3)
		fdf->spd_y += (fdf->spd_y == 1 ? 179 : 5);
	else if (key == X_KEY_4 && (fdf->spd_y > 5 || fdf->spd_y == 1))
		fdf->spd_y -= (fdf->spd_y == 1 ? -179 : 5);
	else if (key == X_KEY_5)
		fdf->spd_z += (fdf->spd_z == 1 ? 179 : 5);
	else if (key == X_KEY_6 && (fdf->spd_z > 5 || fdf->spd_z == 1))
		fdf->spd_z -= (fdf->spd_z == 1 ? -179 : 5);
	else if (key == X_KEY_7)
		fdf->spd_x = 1;
	else if (key == X_KEY_8)
		fdf->spd_y = 1;
	else if (key == X_KEY_9)
		fdf->spd_z = 1;
}

static void			spin(t_vec4 **avec, t_fdf *fdf, const int key)
{
	if (key == X_KEY_U_ARROW)
		ft_veciter(avec, ft_m4rotx(M_PI / 45), fdf->size);
	else if (key == X_KEY_D_ARROW)
		ft_veciter(avec, ft_m4rotx(M_PI / -45), fdf->size);
	else if (key == X_KEY_R_ARROW)
		ft_veciter(avec, ft_m4roty(M_PI / 45), fdf->size);
	else if (key == X_KEY_L_ARROW)
		ft_veciter(avec, ft_m4roty(M_PI / -45), fdf->size);
	else if (key == X_KEY_C)
		ft_veciter(avec, ft_m4rotz(M_PI / 45), fdf->size);
	else if (key == X_KEY_Z)
		ft_veciter(avec, ft_m4rotz(M_PI / -45), fdf->size);
}

static void			move(t_fdf *fdf, const int key, const int value)
{
	if (key == X_KEY_A)
		fdf->pos.x -= value;
	else if (key == X_KEY_D)
		fdf->pos.x += value;
	else if (key == X_KEY_W)
		fdf->pos.y -= value;
	else if (key == X_KEY_S)
		fdf->pos.y += value;
}

static void			transfo(t_fdf *fdf, t_mlx *mlx, int key, uint8_t value)
{
	ft_veccenter(fdf->vec, fdf->size, fdf->origin);
	if ((key >= X_KEY_A && key <= X_KEY_D) || key == X_KEY_W)
		move(fdf, key, value);
	else if (key == X_KEY_MINUS && fdf->zoom > 0.1)
	{
		fdf->zoom *= 0.9f;
		ft_veciter(fdf->vec, ft_m4scale(0.9f, 0.9f, 0.9f), fdf->size);
	}
	else if (key == X_KEY_EQUAL && fdf->zoom < _ZOOM_MAX)
	{
		fdf->zoom *= 1.1f;
		ft_veciter(fdf->vec, ft_m4scale(1.1f, 1.1f, 1.1f), fdf->size);
	}
	else if (key == X_KEY_SPACE)
	{
		ftx_clearimg(_MLX_IMG);
		mlx_put_image_to_window(_MLX_ID, _MLX_WIN_ID, _MLX_IMG_ID, 0, 0);
		fdf->pos.x = WIN_X / 2;
		fdf->pos.y = WIN_Y / 2;
	}
	else
		spin(fdf->vec, fdf, key);
	ft_veccenter(fdf->vec, fdf->size, fdf->pos);
}

int					key_hook(int key, t_fdf *fdf)
{
	if (key == X_KEY_ESCAPE)
		terminate(fdf);
	else if ((key == X_KEY_Q && fdf->move_speed > 5)
		|| (key == X_KEY_E && fdf->move_speed < UINT8_MAX))
	{
		fdf->move_speed += (key == X_KEY_Q ? -5 : 5);
		output(fdf->mlx, *fdf, E_CLIP);
	}
	else if (key >= X_KEY_1 && key <= X_KEY_0 && key != X_KEY_EQUAL
		&& key != X_KEY_MINUS)
	{
		cinema(fdf, key);
		output(fdf->mlx, *fdf, E_CLIP);
	}
	else if (key == X_KEY_L_ALT)
	{
		fdf->psy = (fdf->psy ? false : true);
		output(fdf->mlx, *fdf, E_CLIP);
	}
	else
	{
		transfo(fdf, fdf->mlx, key, fdf->move_speed);
		output(fdf->mlx, *fdf, E_BLUR);
	}
	KTHXBYE;
}
