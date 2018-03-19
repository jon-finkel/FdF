/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:24:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/19 16:57:21 by nfinkel          ###   ########.fr       */
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
			*(t_vec4 **)ft_varypush(vary) = ft_vecnew((float)++p, (float)k,\
				(float)z, 1);
			s += ft_intlen(z);
			if (!IS_WHITESPACE(*s))
				fdf_errhdl(file[k], k);
			while (IS_WHITESPACE(*s))
				++s;
		}
	}
	fdf->vec = vary->buff;
}

static void			get_data(t_fdf *fdf, const int fd)
{
	char		*line;
	t_vary		file_null;
	t_vary		*file;
	t_vary		vec_null;

	if (fd < 0)
		ft_errhdl(NULL, 0, (int)ERR_FD);
	file = &file_null;
	ft_memset(file, '\0', sizeof(t_vary));
	file->data_size = sizeof(char *);
	while (get_next_line(fd, &line))
		*(char **)ft_varypush(file) = line;
	close(fd);
	ft_memset(&vec_null, '\0', sizeof(t_vary));
	vec_null.data_size = sizeof(t_vec4 *);
	parse(fdf, &vec_null, file->buff);
	ft_varydel(&file, (t_vdtor)vdtor);
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
