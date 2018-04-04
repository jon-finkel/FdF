/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 10:57:20 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/05 01:27:38 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define BUFF_SIZE (128)
#define _ROT (90)

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

	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, _ROT, _DEBUG_COLOR, " CINEMA : ON");
	ft_snprintf(data, BUFF_SIZE, " SpeedX:%.2f", (fdf.c_x == 1 ? 0\
		: 360.0 / fdf.c_x));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, _ROT + 15, _DEBUG_COLOR, data);
	ft_snprintf(data, BUFF_SIZE, " SpeedY:%.2f", (fdf.c_y == 1 ? 0\
		: 360.0 / fdf.c_y));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, _ROT + 30, _DEBUG_COLOR, data);
	ft_snprintf(data, BUFF_SIZE, " SpeedZ:%.2f", (fdf.c_z == 1 ? 0\
		: 360.0 / fdf.c_z));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, _ROT + 45, _DEBUG_COLOR, data);
}

void					output_rot_data(const t_mlx *mlx, const t_fdf fdf)
{
	char		data[BUFF_SIZE];

	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, _ROT, _DEBUG_COLOR, " --- ROT ---");
	ft_snprintf(data, BUFF_SIZE, " RotX:%.2f", (fdf.c_x == 1 ? 0\
		: 360.0 / fdf.c_x));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, _ROT + 15, _DEBUG_COLOR, data);
	ft_snprintf(data, BUFF_SIZE, " RotY:%.2f", (fdf.c_y == 1 ? 0\
		: 360.0 / fdf.c_y));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, _ROT + 30, _DEBUG_COLOR, data);
	ft_snprintf(data, BUFF_SIZE, " RotZ:%.2f", (fdf.c_z == 1 ? 0\
		: 360.0 / fdf.c_z));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, _ROT + 45, _DEBUG_COLOR, data);

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
	ft_snprintf(data, BUFF_SIZE, " MOVE FX:%hhu", fdf.trans_speed);
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 60, _DEBUG_COLOR, data);
	if (fdf.psy)
		mlx_string_put(_MLX_ID, _MLX_WIN_ID, WIN_X - 150, 0, rand(),\
			"PSYCH MODE ON!");
	if (fdf.cinema)
		output_cinema_data(mlx, fdf);
	else
		output_rot_data(mlx, fdf);
}
