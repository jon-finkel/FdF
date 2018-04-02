/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 21:35:11 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/23 18:41:55 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include "libft.h"
# include "mlx.h"

# define _MLX fdf.mlx

typedef struct		s_fdf
{
	short			height;
	short			width;
	t_mlx			mlx;
	t_vec4			**vec;
}					t_fdf;

_Noreturn void		fdf_errhdl(const char *line, int y);
void				vdtor(void *data);

#endif
