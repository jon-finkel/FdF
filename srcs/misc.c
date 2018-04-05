/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 10:57:20 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/05 13:36:50 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define BUFF_SIZE (128)
#define _PSY (WIN_X - 150)

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

	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 135, _WHITE, " ---- CIN ----");
	ft_snprintf(data, BUFF_SIZE, " Spd X : %.2f", (fdf.c_x == 1 ? 0\
		: 360.0 / fdf.c_x));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 150, _WHITE, data);
	ft_snprintf(data, BUFF_SIZE, " Spd Y : %.2f", (fdf.c_y == 1 ? 0\
		: 360.0 / fdf.c_y));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 165, _WHITE, data);
	ft_snprintf(data, BUFF_SIZE, " Spd Z : %.2f", (fdf.c_z == 1 ? 0\
		: 360.0 / fdf.c_z));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 180, _WHITE, data);
}

void					output_data(const t_mlx *mlx, const t_fdf fdf)
{
	char		data[BUFF_SIZE];

	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 0, _WHITE, " ---- CAM ----");
	ft_snprintf(data, BUFF_SIZE, " Zoom  : %.2f", fdf.zoom);
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 15, _WHITE, data);
	ft_snprintf(data, BUFF_SIZE, " Pos X : %.f", fdf.pos->x - (WIN_X / 2));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 30, _WHITE, data);
	ft_snprintf(data, BUFF_SIZE, " Pos Y : %.f", fdf.pos->y - (WIN_Y / 2));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 45, _WHITE, data);
	ft_snprintf(data, BUFF_SIZE, " MvSpd : %hhu", fdf.trans_speed);
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 60, _WHITE, data);
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 75, _WHITE, " ---- ROT ----");
	ft_snprintf(data, BUFF_SIZE, " Rot X : %.2f", (fdf.c_x == 1 ? 0\
		: 360.0 / fdf.c_x));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 90, _WHITE, data);
	ft_snprintf(data, BUFF_SIZE, " Rot Y : %.2f", (fdf.c_y == 1 ? 0\
		: 360.0 / fdf.c_y));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 105, _WHITE, data);
	ft_snprintf(data, BUFF_SIZE, " Rot Z : %.2f", (fdf.c_z == 1 ? 0\
		: 360.0 / fdf.c_z));
	mlx_string_put(_MLX_ID, _MLX_WIN_ID, 0, 120, _WHITE, data);
	if (fdf.psy)
		mlx_string_put(_MLX_ID, _MLX_WIN_ID, _PSY, 0, rand(), "PSYCH MODE ON!");
	if (fdf.cinema)
		output_cinema_data(mlx, fdf);
}
