/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:24:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/29 14:40:10 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIN_X 1200
#define WIN_Y 600
#define WIN_TITLE "FdF - A wireframe renderer, by Jon Finkel"

static void				parse(t_fdf *fdf, t_vary *vary, char **file)
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

static void				get_data(t_fdf *fdf, const int fd)
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

static void				make_iso(t_fdf fdf)
{
	double		scale;
	int			k;
	t_m4		m1;
	t_m4		m2;

	scale = WIN_Y / MAX(fdf.width, fdf.height);
	ft_m4scale(&m1, scale, scale, scale);
	ft_m4trans(&m2, (WIN_X - ((fdf.width - 1) * scale)) / 2,\
		(WIN_Y - ((fdf.height - 1) * scale)) / 2, 0);
	ft_m4_m4(&m2, &m1);
	ft_m4iso(&m1);
	k = -1;
	while (++k < fdf.width * fdf.height)
	{
		ft_m4_v4(&m2, fdf.vec[k]);
//		ft_m4_v4(&m1, fdf.vec[k]);
	}
}

t_mlx_img			*ftx_buffppx(t_mlx_img *img, int x, int y, int color)
{
	if (x < 0 || x > img->width || y < 0 || y > img->height)
		GIMME(img);
	if (!img->endian)
		img->addr[y * img->width + x] = ft_bswap(color);
	else
		img->addr[y * img->width + x] = color;
	GIMME(img);
}

# define SIGN(x) ((x) < 0 ? -1 : ((x) > 0))

typedef struct		s_line
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	t_mlx_img		*img;
}					t_line;

static void					init_line(const t_mlx *mlx, t_line *line,
							const int dx, const int dy)
{
	line->sx = SIGN(dx);
	line->sy = SIGN(dy);
	line->dx = ABS(dx) << 1;
	line->dy = ABS(dy) << 1;
	line->img = mlx->img[mlx->cur_img];
}

static t_mlx_img			*line_pos(t_line line, t_vec4 v1, t_vec4 v2,
							const int color)
{
	int		err;

	err = line.dy - (line.dx >> 1);
	while (v1.x != v2.x)
	{
		if (err >= 0)
		{
			v1.y += line.sy;
			err -= line.dx;
		}
		v1.x += line.sx;
		err += line.dy;
		ftx_buffppx(line.img, v1.x, v1.y, color);
	}
	GIMME(line.img);
}

static t_mlx_img			*line_neg(t_line line, t_vec4 v1, t_vec4 v2,
							const int color)
{
	int		err;

	err = line.dy - (line.dx >> 1);
	while (v1.y != v2.y)
	{
		if (err >= 0)
		{
			v1.x += line.sx;
			err -= line.dy;
		}
		v1.y += line.sy;
		err += line.dx;
		ftx_buffppx(line.img, v1.x, v1.y, color);
	}
	GIMME(line.img);
}

t_mlx_img					*ftx_drawline(t_mlx *mlx, const t_vec4 *restrict v1,
							const t_vec4 *restrict v2, const int color)
{
	t_line		l;

	if (v1->x == v2->x || v1->y == v2->y)
	{
	//	if (v1->x == v2->x && v1->y == v2->y)
			GIMME(ftx_buffppx(mlx->img[mlx->cur_img], (int)v1->x, (int)v1->y,\
				color));
/*		else if (v1->x == v2->x)
			GIMME(ftx_vline;
		else
			GIMME(ftx_hline);*/
	}
	init_line(mlx, &l, (int)v2->x - (int)v1->x, (int)v2->y - (int)v1->y);
	if (l.dx > l.dy)
		GIMME(line_pos(l, *v1, *v2, color));
	else
		GIMME(line_neg(l, *v1, *v2, color));
}

static void				do_wireframe(t_fdf fdf)
{
	int		k;

	k = 0;
	while (++k < fdf.width * fdf.height)
	{
		if (k % fdf.width)
			ftx_drawline(&_MLX, fdf.vec[k - 1], fdf.vec[k], 0xffffff);
		if (k - fdf.width >= 0)
			ftx_drawline(&_MLX, fdf.vec[k - fdf.width], fdf.vec[k], 0xffffff);
	}
	mlx_put_image_to_window(_MLX.mlx, _MLX.win[0], _MLX.img[0], 0, 0);
}

int						main(int argc, const char *argv[])
{
	t_fdf		fdf;

	if (argc == 1)
		KTHXBYE;
	ft_memset(&fdf, '\0', sizeof(t_fdf));
	get_data(&fdf, open(argv[1], O_RDONLY));
	ftx_init(&_MLX);
	ftx_addwin(&_MLX, WIN_X, WIN_Y, WIN_TITLE);
	ftx_addimg(&_MLX, WIN_X, WIN_Y);
	make_iso(fdf);
	do_wireframe(fdf);
	mlx_loop(_MLX.mlx);
	KTHXBYE;
}
