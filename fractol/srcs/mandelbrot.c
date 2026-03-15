/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 02:56:58 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/03/14 19:38:24 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_data_mandelbrot(t_data *data)
{
	data->max_iter = MB_MAX_ITER;
	data->x_min = MB_XMIN;
	data->x_max = MB_XMAX;
	data->y_min = MB_YMIN;
	data->y_max = MB_YMAX;
	data->x_range = data->x_max - data->x_min;
	data->y_range = data->y_max - data->y_min;
}

// Initial calculation = multiplication
// r.c.x = data->x_min + r.x * r.dx;
// r.c.y = data->y_min + r.y * r.dy;
// Equivalent to incrementing along r.x++ and r.y++
// Addition is much cheaper than multiplication for CPU :)
void	render_mandelbrot(t_data *data)
{
	t_render	r;

	init_render(&r, data);
	r.c.y = data->y_min;
	while (r.y < WINDOW_HEIGHT)
	{
		r.x = 0;
		r.c.x = data->x_min;
		while (r.x < WINDOW_WIDTH)
		{
			r.z.x = 0;
			r.z.y = 0;
			r.iter = mandelbrot(&r.c, &r.z, data->max_iter);
			r.color = color_handler(data, r.iter, r.z);
			my_pixel_put(&data->img, r.x, r.y, r.color);
			r.c.x += r.dx;
			r.x++;
		}
		r.c.y += r.dy;
		r.y++;
	}
	mlx_put_image_to_window(data->mlx_conn, data->win, data->img.img, 0, 0);
}

// iter : before divergence
// zz = z**2 + c (z = 0 ; c = cx + cyi = constant complex)
// until norm |z| > 2 = x**2 + y**2 > 4 = diverge or max_iter
// absolute value (distance to 0 on real line)
//		vs. norm (distance on a plan = Pythagore)
// z = x + yi > xx = x**2 - y**2 + cx ; yy = 2xy + cy
// Mandelbrot set always starts at z = 0
// + is roughly contained in -2 ≤ Re(c) ≤ 1, -1.5 ≤ Im(c) ≤ 1.5.
// Each px = fixed c, and we follow z journey starting 0
// ***mag = distance from origin (0,0)
// if |z| > 2 == |z|^z > 4 then return iter == diverges
// needs to be updated at each iteration
// faster > * are expensive when done hundreds of millions of times
// ***tmp vars to avoid recomputing floats = costly
int	mandelbrot(t_complex *c, t_complex *z, int max_iter)
{
	double	tmp_x;
	int		i;
	double	x2;
	double	y2;
	double	xy;

	i = 0;
	x2 = z->x * z->x;
	y2 = z->y * z->y;
	while (x2 + y2 <= 4 && i < max_iter)
	{
		xy = z->x * z->y;
		tmp_x = x2 - y2;
		z->y = 2 * xy + c->y;
		z->x = tmp_x + c->x;
		x2 = z->x * z->x;
		y2 = z->y * z->y;
		i++;
	}
	return (i);
}
