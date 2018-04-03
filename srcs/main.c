/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:24:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/04 00:42:12 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			fdf_init(t_fdf *fdf, double scale)
{
	t_m4		ms;
	t_m4		mx;
	t_m4		mz;

	mx = ft_m4rotx(M_PI / 4);
	mz = ft_m4rotz(M_PI / 4);
	ms = ft_m4scale(scale, scale, scale);
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
	ftx_addwin(&fdf.mlx, WIN_X, WIN_Y, WIN_TITLE);
	ftx_addimg(&fdf.mlx, WIN_X, WIN_Y);
	fdf_init(&fdf, WIN_Y / MAX(fdf.width, fdf.height));
	key_hook(0, &fdf);
	mlx_hook(fdf.mlx.win[0], 2, X_KEYPRESS_MASK, (int(*)())key_hook, &fdf);
	mlx_loop_hook(fdf.mlx.mlx, (int (*)())cinematic, &fdf);
	mlx_loop(fdf.mlx.mlx);
	KTHXBYE;
}
