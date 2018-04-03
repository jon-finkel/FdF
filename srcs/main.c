/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:24:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/03 20:49:16 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			make_iso(const t_fdf fdf, double scale)
{
	t_m4		ms;
	t_m4		mx;
	t_m4		mz;

	ms = ft_m4scale(scale, scale, scale);
	mx = ft_m4rotx(M_PI / 4);
	mz = ft_m4rotz(M_PI / 4);
	ft_veciter(fdf.vec, mz, fdf.size);
	ft_veciter(fdf.vec, mx, fdf.size);
	ft_veciter(fdf.vec, ms, fdf.size);
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
	fdf.origin = ft_vecnew(0, 0, 0, 1);
	fdf.pos = ft_vecnew(WIN_X / 2, WIN_Y / 2, 0, 1);
	key_hook(0, &fdf);
	mlx_hook(fdf.mlx.win[0], 2, X_KEYPRESS_MASK, (int(*)())key_hook, &fdf);
	mlx_loop(fdf.mlx.mlx);
	KTHXBYE;
}
