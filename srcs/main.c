/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:24:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/03 12:52:04 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			make_iso(t_fdf fdf, double scale)
{
	t_m4		mx;
	t_m4		mz;
	t_m4		ms;
	t_m4		mt;

	ms = ft_m4scale(scale, scale, scale);
	mt = ft_m4trans(WIN_X / 4, WIN_Y / 4, 0);
	mx = ft_m4rotx(M_PI / 4);
	mz = ft_m4rotz(M_PI / 4);
	ft_veciter(fdf.vec, mz, fdf.width * fdf.height);
	ft_veciter(fdf.vec, mx, fdf.width * fdf.height);
	ft_veciter(fdf.vec, ms, fdf.width * fdf.height);
	ft_veciter(fdf.vec, mt, fdf.width * fdf.height);
}

static void			output(t_mlx *mlx, const t_fdf fdf)
{
	int			k;
	t_vec4		v;

	k = 0;
	while (++k < fdf.width * fdf.height)
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

static void			move(t_vec4 **avec, const t_fdf fdf, const int key,
					const int value)
{
	if (key == X_KEY_A)
		ft_veciter(avec, ft_m4trans(-value, 0, 0), fdf.width * fdf.height);
	else if (key == X_KEY_D)
		ft_veciter(avec, ft_m4trans(value, 0, 0), fdf.width * fdf.height);
	else if (key == X_KEY_W)
		ft_veciter(avec, ft_m4trans(0, -value, 0), fdf.width * fdf.height);
	else if (key == X_KEY_S)
		ft_veciter(avec, ft_m4trans(0, value, 0), fdf.width * fdf.height);
}

static void			key_hook(int key, t_fdf *fdf)
{
	static uint8_t		value = 5;
	t_mlx				*mlx;

	mlx = &fdf->mlx;
	if (key == X_KEY_ESCAPE)
		terminate(fdf);
	else if (key == X_KEY_Q && value)
		value -= 5;
	else if (key == X_KEY_E && value < UCHAR_MAX)
		value += 5;
	else if ((key >= X_KEY_A && key <= X_KEY_D) || key == X_KEY_W)
		move(fdf->vec, *fdf, key, value);
	ftx_clearimg(_MLX_IMG);
	output(mlx, *fdf);
}

int					main(int argc, const char *argv[])
{
	t_fdf		fdf;

	if (argc == 1)
		KTHXBYE;
	ft_memset(&fdf, '\0', sizeof(t_fdf));
	get_data(&fdf, open(argv[1], O_RDONLY));
	ftx_init(&fdf.mlx);
	ftx_addwin(&fdf.mlx, WIN_X, WIN_Y, WIN_TITLE);
	ftx_addimg(&fdf.mlx, WIN_X, WIN_Y);
	make_iso(fdf, WIN_Y / MAX(fdf.width, fdf.height));
	output(&fdf.mlx, fdf);
	mlx_hook(fdf.mlx.win[0], 2, X_KEYPRESS_MASK, (int(*)())key_hook, &fdf);
	mlx_loop(fdf.mlx.mlx);
	KTHXBYE;
}
