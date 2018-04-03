/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 13:17:30 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/03 20:49:56 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			output(t_mlx *mlx, const t_fdf fdf)
{
	int			k;
	t_vec4		v;

	k = 0;
	while (++k < fdf.size)
	{
		if (k % fdf.width)
		{
			v = *fdf.vec[k - 1];
			ftx_drawline(_MLX_IMG, v, *fdf.vec[k], 0xffffff);
		}
		if (k - fdf.width >= 0)
		{
			v = *fdf.vec[k - fdf.width];
			ftx_drawline(_MLX_IMG, v, *fdf.vec[k], 0xffffff);
		}
	}
	mlx_put_image_to_window(_MLX_ID, _MLX_WIN_ID, _MLX_IMG_ID, 0, 0);
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

static void			zoom(t_vec4 **avec, const t_fdf fdf, const int key)
{
	float		z;

	if (key == X_KEY_MINUS)
		z = 0.9f;
	else
		z = 1.1f;
	ft_veciter(avec, ft_m4scale(z, z, z), fdf.size);
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

void				key_hook(int key, t_fdf *fdf)
{
	static uint8_t		value = 5;
	t_mlx				*mlx;

	mlx = &fdf->mlx;
	ftx_veccenter(fdf->vec, fdf->size, *fdf->origin);
	if (key == X_KEY_ESCAPE)
		terminate(fdf);
	else if (key == X_KEY_Q && value)
		value -= 5;
	else if (key == X_KEY_E && value < UCHAR_MAX)
		value += 5;
	else if ((key >= X_KEY_A && key <= X_KEY_D) || key == X_KEY_W)
		move(fdf, key, value);
	else if (key == X_KEY_EQUAL || key == X_KEY_MINUS)
		zoom(fdf->vec, *fdf, key);
	else
		spin(fdf->vec, *fdf, key);
	ftx_clearimg(_MLX_IMG);
	ftx_veccenter(fdf->vec, fdf->size, *fdf->pos);
	output(mlx, *fdf);
}
