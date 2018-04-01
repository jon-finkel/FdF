/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:24:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/01 17:44:48 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIN_X 1200
#define WIN_Y 600
#define WIN_TITLE "FdF - A wireframe renderer, by Jon Finkel"

static void						parse(t_fdf *fdf, t_vary *vary, char **file)
{
	char		*s;
	int			k;
	int			p;
	int			z;

	k = -1;
	while (file[++k])
	{
		s = file[k];
		p = -1;
		while (*s)
		{
			z = ft_atoi(s);
			*(t_vec4 **)ft_varypush(vary) = ft_vecnew(++p, k, z, true);
			s += ft_intlen(z);
			if (*s && !IS_WHITESPACE(*s))
				fdf_errhdl(file[k], k);
			while (IS_WHITESPACE(*s))
				++s;
		}
		fdf->width = MAX(fdf->width, p + 1);
	}
	fdf->height = k;
	fdf->vec = vary->buff;
}

static void						get_data(t_fdf *fdf, const int fd)
{
	char		*line;
	t_vary		file_null;
	t_vary		*file;
	t_vary		vary_null;

	if (fd < 0)
		ft_errhdl(NULL, 0, (int)ERR_FD);
	file = &file_null;
	ft_memset(file, '\0', sizeof(t_vary));
	file->data_size = sizeof(char *);
	while (get_next_line(fd, &line))
		*(char **)ft_varypush(file) = line;
	close(fd);
	ft_memset(&vary_null, '\0', sizeof(t_vary));
	vary_null.data_size = sizeof(t_vec4 *);
	parse(fdf, &vary_null, file->buff);
	ft_varydel(&file, (t_vdtor)vdtor);
}

static void						make_iso(t_fdf fdf, double scale)
{
	t_m4		mx;
	t_m4		mz;
	t_m4		ms;
	t_m4		mt;

	ms = ft_m4scale(scale, scale, scale);
	mt = ft_m4trans(WIN_X / 4, WIN_Y / 4, 0);
	mx = ft_m4rotx(M_PI / 4);
	mz = ft_m4rotz(M_PI / 4);
//	ft_veciter(fdf.vec, mz, fdf.width * fdf.height);
//	ft_veciter(fdf.vec, mx, fdf.width * fdf.height);
	ft_veciter(fdf.vec, ms, fdf.width * fdf.height);
	ft_veciter(fdf.vec, mt, fdf.width * fdf.height);
}

/*void			ftx_drawline(t_mlx *mlx, const t_vec4 v1, const t_vec4 v2,
				int color)
{
	int			k;
	double		x;
	double		y;

	if ((k = MAX(fabs(v1.x - v2.x), fabs(v1.y - v2.y) + 1)) == 1)
		BYEZ;
	x = (v2.x - v1.x) / k;
	y = (v2.y - v1.y) / k;
	while (k--)
		mlx_pixel_put(mlx->mlx, mlx->win[0], (v1.x + x * k), (v1.y + y * k),
			color);
}*/

typedef struct		s_line
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
}					t_line;

static void			pos_line(t_mlx_img *img, const t_line line, const int color)
{

}

static void			init_line(t_line *line, const int dx, const int dy)
{
	line->sx = SIGN(dx);
	line->sy = SIGN(dy);
	line->dx = fabs(dx) << 1;
	line->dy = fabs(dy) << 1;
}

t_mlx_img			*ftx_drawline(t_mlx_img *img, const t_vec4 v1,
					const t_vec4 v2, int color)
{
	t_line		line;

	if (v1.x == v2.x || v1.y == v2.y)
	{
		if (v1.x == v2.x && v1.y == v2.y)
			GIMME(ftx_buffpixel(img, (int)v1.x, (int)v1.y, color));
		else if (v1.x == v2.x)
			GIMME(ftx_vline(img, v1, v2, color));
		else
			GIMME(ftx_hline(img, v1, v2, color));
	}
	init_line(&line, (int)(v2.x - v1.x), (int)(v2.y - v1.y));
	ftx_buffpixel(img, (int)v1.x, (int)v1.y, color);
	if (line.dx > line.dy)
		pos_line(img, line, color);
	else
		neg_line(img, line, color);
	GIMME(img);
}

static void						do_wireframe(t_mlx *mlx, const t_fdf fdf)
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

int								main(int argc, const char *argv[])
{
	t_fdf		fdf;

	if (argc == 1)
		KTHXBYE;
	ft_memset(&fdf, '\0', sizeof(t_fdf));
	get_data(&fdf, open(argv[1], O_RDONLY));
	ftx_init(&_MLX);
	ftx_addwin(&_MLX, WIN_X, WIN_Y, WIN_TITLE);
	ftx_addimg(&_MLX, WIN_X, WIN_Y);
	make_iso(fdf, WIN_Y / MAX(fdf.width, fdf.height));
	do_wireframe(&fdf.mlx, fdf);
	mlx_loop(_MLX.mlx);
	KTHXBYE;
}
