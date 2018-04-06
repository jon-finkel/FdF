/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:50:38 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/06 18:18:14 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vary		g_vary_stack = {NULL, 0, 0, sizeof(t_vec4 *)};
static t_vary		*g_vary = &g_vary_stack;

void				vdtor(void *data)
{
	ft_memdel((void **)&*(t_vec4 **)data);
}

void				terminate(t_fdf *fdf)
{
	ft_varydel(&g_vary, (t_vdtor)vdtor);
	ftx_mlxdtor(fdf->mlx);
	exit(EXIT_SUCCESS);
}

static void			parse(t_fdf *fdf, char *line, const int y)
{
	int		x;
	int		z;

	x = -1;
	while (*line)
	{
		while (IS_WHITESPACE(*line))
			++line;
		z = ft_atoi(line);
		*(t_vec4 **)ft_varypush(g_vary) = ft_vecnew(++x, y, z, true);
		line += ft_intlen(z);
		if (*line && !IS_WHITESPACE(*line))
			fdf_errhdl(line, y);
		while (IS_WHITESPACE(*line))
			++line;
	}
	fdf->size += ++x;
	fdf->width = MAX(fdf->width, x);
}

char				*get_data(t_fdf *fdf, const char *map)
{
	char		*line;
	int			fd;
	int			y;

	if ((fd = open(map, O_RDONLY)) < 0)
		ft_errhdl(NULL, 0, (int)ERR_OPEN);
	line = NULL;
	y = -1;
	while (get_next_line(fd, &line) && line)
	{
		parse(fdf, line, ++y);
		ft_strdel(&line);
	}
	if (!g_vary->buff)
		fdf_errhdl(NULL, y);
	close(fd);
	fdf->height = y;
	fdf->vec = g_vary->buff;
	GIMME(ft_strdup((line = ft_strrchr(map, '/')) ? line + 1 : map));
}
