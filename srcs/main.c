/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:24:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/07 22:38:30 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define BUFF_SIZE (128)
#define _USAGE "usage: ./fdf <file>\n"

static void			fdf_init(t_fdf *fdf)
{
	t_m4		ms;
	t_m4		mx;
	t_m4		mz;

	fdf->move_speed = 5;
	fdf->zoom = WIN_Y / MAX(fdf->width, fdf->height);
	mz = ft_m4rotz(M_PI / 4);
	mx = ft_m4rotx(M_PI / 4);
	ms = ft_m4scale(fdf->zoom, fdf->zoom, fdf->zoom);
	ft_veciter(fdf->vec, mz, fdf->size);
	ft_veciter(fdf->vec, mx, fdf->size);
	ft_veciter(fdf->vec, ms, fdf->size);
	fdf->spd_x = 180;
	fdf->spd_y = 180;
	fdf->spd_z = 180;
	fdf->origin = ft_p2ctor(0, 0);
	fdf->pos = ft_p2ctor(WIN_X / 2, WIN_Y / 2);
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
		ft_veccenter(fdf->vec, fdf->size, fdf->origin);
		ft_veciter(fdf->vec, ft_m4rotx(2 * M_PI / fdf->spd_x), fdf->size);
		ft_veciter(fdf->vec, ft_m4roty(2 * M_PI / fdf->spd_y), fdf->size);
		ft_veciter(fdf->vec, ft_m4rotz(2 * M_PI / fdf->spd_z), fdf->size);
		ft_veccenter(fdf->vec, fdf->size, fdf->pos);
	}
	if (fdf->cinema || fdf->psy)
		output(fdf->mlx, *fdf, E_BLUR);
	KTHXBYE;
}

int					main(int argc, const char *argv[])
{
	char		title[BUFF_SIZE];
	char		*map_name;
	t_fdf		fdf;
	t_mlx		mlx;

	if (argc != 2 && ft_printf(_USAGE))
		KTHXBYE;
	ft_memset(&fdf, '\0', sizeof(t_fdf));
	map_name = get_data(&fdf, argv[1]);
	fdf_init(&fdf);
	fdf.mlx = ftx_init(&mlx);
	ft_snprintf(title, BUFF_SIZE, "FdF, by Jon Finkel - map: %s", map_name);
	ft_strdel(&map_name);
	ftx_winctor(fdf.mlx, WIN_X, WIN_Y, title);
	ftx_imgctor(fdf.mlx, WIN_X, WIN_Y);
	key_hook(X_KEY_SPACE, &fdf);
	mlx_hook(fdf.mlx->win[0], X_KEYPRESS, X_KEYPRESS_MASK, key_hook, &fdf);
	mlx_loop_hook(fdf.mlx->mlx, cinematic, &fdf);
	mlx_loop(fdf.mlx->mlx);
	KTHXBYE;
}
