/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:24:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/05 00:09:39 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			fdf_init(t_fdf *fdf)
{
	t_m4		ms;
	t_m4		mx;
	t_m4		mz;

	fdf->trans_speed = 5;
	fdf->zoom = WIN_Y / MAX(fdf->width, fdf->height);
	mx = ft_m4rotx(M_PI / 4);
	mz = ft_m4rotz(M_PI / 4);
	ms = ft_m4scale(fdf->zoom, fdf->zoom, fdf->zoom);
	ft_veciter(fdf->vec, mz, fdf->size);
	ft_veciter(fdf->vec, mx, fdf->size);
	ft_veciter(fdf->vec, ms, fdf->size);
	fdf->c_x = 180;
	fdf->c_y = 180;
	fdf->c_z = 180;
	fdf->origin = ft_vecnew(0, 0, 0, 1);
	fdf->pos = ft_vecnew(WIN_X / 2, WIN_Y / 2, 0, 1);
}

/*static int			check_args(int argc, const char *argv[])
{
	if (argc > 2)
	{

	}
}*/

void				output(t_mlx *mlx, const t_fdf fdf)
{
	int			k;
	t_vec4		v;

	ftx_blurrimg(_MLX_IMG);
	k = 0;
	while ((size_t)++k < fdf.size)
	{
		if (k % fdf.width)
		{
			v = *fdf.vec[k - 1];
			ftx_drawline(_MLX_IMG, v, *fdf.vec[k], fdf.psych ? rand() : INT_MAX);
		}
		if (k - fdf.width >= 0)
		{
			v = *fdf.vec[k - fdf.width];
			ftx_drawline(_MLX_IMG, v, *fdf.vec[k], fdf.psych ? rand() : INT_MAX);
		}
	}
	mlx_put_image_to_window(_MLX_ID, _MLX_WIN_ID, _MLX_IMG_ID, 0, 0);
	if (!fdf.debug)
		output_debug(mlx, fdf);
}

static void			cinematic(t_fdf *fdf)
{
	if (fdf->cinema)
	{
		ftx_veccenter(fdf->vec, fdf->size, *fdf->origin);
		ft_veciter(fdf->vec, ft_m4rotx(2 * M_PI / fdf->c_x), fdf->size);
		ft_veciter(fdf->vec, ft_m4roty(2 * M_PI / fdf->c_y), fdf->size);
		ft_veciter(fdf->vec, ft_m4rotz(2 * M_PI / fdf->c_z), fdf->size);
		ftx_veccenter(fdf->vec, fdf->size, *fdf->pos);
		output(&fdf->mlx, *fdf);
	}
}

int					main(int argc, const char *argv[])
{
	t_fdf		fdf;

	if (argc == 1)
		KTHXBYE;
	ft_memset(&fdf, '\0', sizeof(t_fdf));
//	if (check_args(argc, argv))
//		KTHXBYE;
	get_data(&fdf, open(argv[1], O_RDONLY));
	ftx_init(&fdf.mlx);
	ftx_winctor(&fdf.mlx, WIN_X, WIN_Y, WIN_TITLE);
	ftx_imgctor(&fdf.mlx, WIN_X, WIN_Y);
	fdf_init(&fdf);
	key_hook(0, &fdf);
	mlx_hook(fdf.mlx.win[0], 2, X_KEYPRESS_MASK, (int(*)())key_hook, &fdf);
	mlx_loop_hook(fdf.mlx.mlx, (int (*)())cinematic, &fdf);
	mlx_loop(fdf.mlx.mlx);
	KTHXBYE;
}
