/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:24:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/21 16:59:45 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIN_X 1200
#define WIN_Y 600

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
			*(t_vec4 **)ft_varypush(vary) = ft_vecnew((float)++p, (float)k,
				(float)z);
			s += ft_intlen(z);
			if (!IS_WHITESPACE(*s))
				fdf_errhdl(file[k], k);
			while (IS_WHITESPACE(*s))
				++s;
		}
		fdf->width = MAX(fdf->width, p + 1);
	}
	fdf->height = k + 1;
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
	float			dx;
	float			dy;
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

	brz.dx = (float)ABS(vec1->x - vec2->x);
	brz.dy = -(float)ABS(vec1->y - vec2->y);
	brz.derr = brz.dx + brz.dy;
	brz.sx = (vec1->x < vec2->x ? 1 : -1);
	brz.sy = (vec1->y < vec2->y ? 1 : -1);
	x0 = vec1->x;
	y0 = vec1->y;
	while (x0 != vec2->x || y0 != vec2->y)
	{
		mlx_pixel_put(mlx->mlx, mlx->win[0], x0, y0, color);
		err = 2 * brz.derr;
		brz.derr += (err >= brz.dy ? brz.dy : 0);
		x0 += (err >= brz.dy ? brz.sx : 0);
		brz.derr += (err <= brz.dx ? brz.dx : 0);
		y0 += (err <= brz.dx ? brz.sy : 0);
	}
}

typedef void		(t_brzctor)(t_mlx *, t_vec4 *, t_vec4 *, int);

static void			do_wireframe(t_fdf *fdf, t_mlx *mlx, (t_brzctor)brz)
{
	;
}

int					main(int argc, const char *argv[])
{
	t_fdf		fdf;

	if (argc == 1)
		KTHXBYE;
	ft_memset(&fdf, '\0', sizeof(t_fdf));
	get_data(&fdf, open(argv[1], O_RDONLY));
	ft_mlxinit(&_MLX);
	ft_mlxaddwin(&_MLX, WIN_X, WIN_Y, "FdF");
	mlx_loop(_MLX.mlx);
	KTHXBYE;
}
