/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:24:23 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/14 00:59:30 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void				parse(t_vary *vary)
{
}

static t_vary			*get_data(t_vary *vary, const int fd)
{
	char		*line;

	if (fd < 0)
		ft_errhdl(NULL, 0, (int)ERR_FD);
	while (get_next_line(fd, &line))
		*(char **)ft_varypush(vary) = line;
	GIMME(vary);
}

int						main(int argc, const char *argv[])
{
	t_vary		vary_null;

	ft_memset(&vary_null, '\0', sizeof(t_vary));
	vary_null.data_size = sizeof(char *);
	parse(get_data(&vary_null, open(argv[1], O_RDONLY)));
	KTHXBYE;
}
