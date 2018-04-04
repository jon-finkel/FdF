/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 10:57:20 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/04 23:46:26 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define BUFF_SIZE (128)
#define _CIN (75)

_Noreturn void			fdf_errhdl(const char *line, int y)
{
	ft_dprintf(STDERR_FILENO, "fdf: parsing error, line[%d]: %s\n", y, line);
	exit(EXIT_FAILURE);
}

void					vdtor(void *data, va_list ap)
{
	t_flag		flag;

	flag = va_arg(ap, t_flag);
	if (flag == E_FILE)
		ft_strdel((char **)data);
	else if (flag == E_VARY)
		ft_memdel((void **)&*(t_vec4 **)data);
}

void					output_cinema_data(const t_mlx *mlx, const t_fdf fdf)
{
	char		data[BUFF_SIZE];

	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, _CIN, _DEBUG_COLOR, " CINEMA : ON");
	ft_snprintf(data, BUFF_SIZE, " SpeedX:%.2f", (fdf.c_x == 1 ? 0\
		: 360.0 / fdf.c_x));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, _CIN + 15, _DEBUG_COLOR, data);
	ft_snprintf(data, BUFF_SIZE, " SpeedY:%.2f", (fdf.c_y == 1 ? 0\
		: 360.0 / fdf.c_y));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, _CIN + 30, _DEBUG_COLOR, data);
	ft_snprintf(data, BUFF_SIZE, " SpeedZ:%.2f", (fdf.c_z == 1 ? 0\
		: 360.0 / fdf.c_z));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, _CIN + 45, _DEBUG_COLOR, data);
}

void					output_debug(const t_mlx *mlx, const t_fdf fdf)
{
	char		data[BUFF_SIZE];

	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 0, _DEBUG_COLOR, " --- CAM ---");
	ft_snprintf(data, BUFF_SIZE, " ZOOM:%.2f", fdf.zoom);
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 15, _DEBUG_COLOR, data);
	ft_snprintf(data, BUFF_SIZE, " PosX:%.f", fdf.pos->x - (WIN_X / 2));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 30, _DEBUG_COLOR, data);
	ft_snprintf(data, BUFF_SIZE, " PosY:%.f", fdf.pos->y - (WIN_Y / 2));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 45, _DEBUG_COLOR, data);
	if (fdf.cinema)
		output_cinema_data(mlx, fdf);
}
