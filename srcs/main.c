/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:24:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/24 19:39:57 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIN_X 1200
#define WIN_Y 600
#define WIN_TITLE "FdF - A wireframe renderer, by Jon Finkel"

static void			parse(t_fdf *fdf, t_vary *vary, char **file)
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
			if (!IS_WHITESPACE(*s))
				fdf_errhdl(file[k], k);
			while (IS_WHITESPACE(*s))
				++s;
		}
		fdf->width = MAX(fdf->width, p + 1);
	}
	fdf->height = k;
	fdf->vec = vary->buff;
}

static void			get_data(t_fdf *fdf, const int fd)
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

typedef struct		s_brz
{
	double			dx;
	double			dy;
	int				derr;
	int8_t			sx;
	int8_t			sy;
}					t_brz;

void			ft_bresenham2(t_mlx *mlx, t_vec4 *vec1, t_vec4 *vec2, int color)
{
	int			err;
	int			x0;
	int			y0;
	t_brz		brz;

	brz.dx = ABS(vec1->x - vec2->x);
	brz.dy = -ABS(vec1->y - vec2->y);
	brz.derr = brz.dx + brz.dy;
	brz.sx = (vec1->x < vec2->x ? 1 : -1);
	brz.sy = (vec1->y < vec2->y ? 1 : -1);
	x0 = (int)vec1->x;
	y0 = (int)vec1->y;
	while (x0 != (int)vec2->x || y0 != (int)vec2->y)
	{
		mlx_pixel_put(mlx->mlx, mlx->win[0], x0, y0, color);
		err = 2 * brz.derr;
		brz.derr += (err >= brz.dy ? brz.dy : 0);
		x0 += (err >= brz.dy ? brz.sx : 0);
		brz.derr += (err <= brz.dx ? brz.dx : 0);
		y0 += (err <= brz.dx ? brz.sy : 0);
	}
}

static void			make_iso(t_fdf fdf)
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
	ft_m4_iso(&m1);
//	ft_printf("%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%d, %d, %d, %d\n", m2.a, m2.b, m2.c, m2.d, m2.e, m2.f, m2.g, m2.h, m2.i, m2.j, m2.k, m2.l, m2.m, m2.n, m2.o, m2.p);
	k = -1;
	while (++k < fdf.width * fdf.height)
	{
//		ft_m4_v4(&m2, fdf.vec[k]);
		ft_m4_v4(&m1, fdf.vec[k]);
	}
}

static void			do_wireframe(t_fdf fdf)
{
	int		k;

	k = 0;
	while (++k < fdf.width * fdf.height)
	{
		if (k % fdf.width)
			ft_bresenham2(&_MLX, fdf.vec[k - 1], fdf.vec[k], 0xffffff);
		if (k - fdf.width >= 0)
			ft_bresenham2(&_MLX, fdf.vec[k - fdf.width], fdf.vec[k], 0xffffff);
	}
}

int					main(int argc, const char *argv[])
{
	t_fdf		fdf;

	if (argc == 1)
		KTHXBYE;
	ft_memset(&fdf, '\0', sizeof(t_fdf));
	get_data(&fdf, open(argv[1], O_RDONLY));
	ft_mlxinit(&_MLX);
	ft_mlxaddwin(&_MLX, WIN_X, WIN_Y, WIN_TITLE);
	make_iso(fdf);
	do_wireframe(fdf);
	mlx_loop(_MLX.mlx);
	KTHXBYE;
}
