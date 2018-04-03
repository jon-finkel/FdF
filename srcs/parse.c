/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:50:38 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/03 22:26:05 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vary		g_vary_null = {NULL, 0, 0, sizeof(t_vec4 *)};
static t_vary		*g_vary = &g_vary_null;

void				terminate(t_fdf *fdf)
{
	ft_memdel((void **)&fdf->origin);
	ft_memdel((void **)&fdf->pos);
	ft_varydel(&g_vary, vdtor, E_VARY);
	ft_varydel(&g_mlx_img_vary, vdtor, E_IMG);
	ft_varydel(&g_mlx_win_vary, vdtor, E_WIN);
	exit(EXIT_SUCCESS);
}

static void			parse(t_fdf *fdf, char **file)
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
			while (IS_WHITESPACE(*s))
				++s;
			z = ft_atoi(s);
			*(t_vec4 **)ft_varypush(g_vary) = ft_vecnew(++p, k, z, true);
			s += ft_intlen(z);
			if (*s && !IS_WHITESPACE(*s))
				fdf_errhdl(file[k], k);
		}
		fdf->size += ++p;
		fdf->width = MAX(fdf->width, p);
	}
	fdf->height = k;
	fdf->vec = g_vary->buff;
}

void				get_data(t_fdf *fdf, const int fd)
{
	char		*line;
	t_vary		file_null;
	t_vary		*file;

	if (fd < 0)
		ft_errhdl(NULL, 0, (int)ERR_OPEN);
	file = &file_null;
	ft_memset(file, '\0', sizeof(t_vary));
	file->data_size = sizeof(char *);
	while (get_next_line(fd, &line))
		*(char **)ft_varypush(file) = line;
	close(fd);
	parse(fdf, file->buff);
	ft_varydel(&file, vdtor, E_FILE);
}
