/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:24:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/05 14:04:25 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define _USAGE "usage: ./fdf <file>\n"

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

void				output(t_mlx *mlx, const t_fdf fdf, const t_flag flag)
{
	int			k;
	t_vec4		*v;

	if (flag == E_BLUR)
		ftx_blurimg(_MLX_IMG);
	else if (flag == E_CLIP)
	{
		ftx_clipimg(_MLX_IMG, ft_p2ctor(0, 0), ft_p2ctor(200, 200));
		ftx_clipimg(_MLX_IMG, ft_p2ctor(WIN_X - 150, 0), ft_p2ctor(WIN_X, 150));
	}
	k = 0;
	while ((size_t)++k < fdf.size)
	{
		if (k % fdf.width && (v = fdf.vec[k - 1]))
			ftx_drawline(_MLX_IMG, *v, *fdf.vec[k], fdf.psy ? rand() : 0xffffff);
		if (k - fdf.width >= 0 && (v = fdf.vec[k - fdf.width]))
			ftx_drawline(_MLX_IMG, *v, *fdf.vec[k], fdf.psy ? rand() : 0xffffff);
	}
	mlx_put_image_to_window(_MLX_ID, _MLX_WIN_ID, _MLX_IMG_ID, 0, 0);
	output_data(mlx, fdf);
}

static int			cinematic(t_fdf *fdf)
{
	if (fdf->cinema)
	{
		ft_veccenter(fdf->vec, fdf->size, *fdf->origin);
		ft_veciter(fdf->vec, ft_m4rotx(2 * M_PI / fdf->c_x), fdf->size);
		ft_veciter(fdf->vec, ft_m4roty(2 * M_PI / fdf->c_y), fdf->size);
		ft_veciter(fdf->vec, ft_m4rotz(2 * M_PI / fdf->c_z), fdf->size);
		ft_veccenter(fdf->vec, fdf->size, *fdf->pos);
	}
	if (fdf->cinema || fdf->psy)
		output(fdf->mlx, *fdf, E_BLUR);
	KTHXBYE;
}

int					main(int argc, const char *argv[])
{
	t_fdf		fdf;
	t_mlx		mlx_stack;
	t_mlx		*mlx;

	if (argc != 2 && ft_printf(_USAGE))
		KTHXBYE;
	ft_memset(&fdf, '\0', sizeof(t_fdf));
	get_data(&fdf, open(argv[1], O_RDONLY));
	mlx = ftx_init(&mlx_stack);
	fdf.mlx = mlx;
	ftx_winctor(mlx, WIN_X, WIN_Y, WIN_TITLE);
	ftx_imgctor(mlx, WIN_X, WIN_Y);
	fdf_init(&fdf);
	key_hook(X_KEY_SPACE, &fdf);
	mlx_hook(_MLX_WIN_ID, X_KEYPRESS, X_KEYPRESS_MASK, key_hook, &fdf);
	mlx_loop_hook(_MLX_ID, cinematic, &fdf);
	mlx_loop(_MLX_ID);
	KTHXBYE;
}
