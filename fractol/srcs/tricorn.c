/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 05:18:52 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/03/12 03:00:26 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_data_tricorn(t_data *data)
{
	data->max_iter = T_MAX_ITER;
	data->x_min = T_MIN;
	data->x_max = T_MAX;
	data->y_min = T_MIN;
	data->y_max = T_MAX;
	data->x_range = data->x_max - data->x_min;
	data->y_range = data->y_max - data->y_min;
}

// z = conj(z)^2 + c
// conj(z) flips the sign of the imaginary part
// Negate at new calculation level
// Move x2 and y2 before loop + at end of loop for better CPU performance
// Escape in while is better than if > break
static int	tricorn(t_complex *c, t_complex *z, int max_iter)
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
		z->y = -2 * xy + c->y;
		z->x = tmp_x + c->x;
		x2 = z->x * z->x;
		y2 = z->y * z->y;
		i++;
	}
	return (i);
}

// Mandelbrot : z starts at 0 ; c varies per px
// Julia : z starts at pixel's coordinates ; c is fixed
// Initial calculation = multiplication
// r.c.x = data->x_min + r.x * r.dx;
// r.c.y = data->y_min + r.y * r.dy;
// Equivalent to incrementing along r.x++ and r.y++
// Addition is much cheaper than multiplication for CPU :)
void	render_tricorn(t_data *data)
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
			r.iter = tricorn(&r.c, &r.z, data->max_iter);
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
