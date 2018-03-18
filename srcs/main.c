/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:24:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/18 11:43:20 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline t_vec4			*map(int x, int y, int z)
{
	t_vec4		*vec;

	vec = (t_vec4 *)ft_memalloc(sizeof(t_vec4));
	vec->x = x;
	vec->y = y;
	vec->z = z;
	vec->w = 1;
	GIMME(vec);
}

static void						parse(t_fdf *fdf, t_vary *vary, char **file)
{
	char		*s;
	int			k;
	int			p;

	k = -1;
	while (file[++k] && (p = -1))
	{
		s = file[k];
		while (*s)
		{
			if (1)
				*(t_vec4 **)ft_varypush(vary) = map(++p, k, ft_atoi(s));
			else
				fdf_errhdl(file[k], s - file[k], k);
		}
	}
	fdf->vec = vary->buff;
}

static void						get_data(t_fdf *fdf, const int fd)
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

int								main(int argc, const char *argv[])
{
	t_fdf		fdf;

	if (argc == 1)
		KTHXBYE;
	ft_memset(&fdf, '\0', sizeof(t_fdf));
	get_data(&fdf, open(argv[1], O_RDONLY));
	KTHXBYE;
}
