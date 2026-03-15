/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 05:18:52 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/03/12 03:00:24 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_data_julia(t_data *data)
{
	data->max_iter = J_MAX_ITER;
	data->x_min = J_MIN;
	data->x_max = J_MAX;
	data->y_min = J_MIN;
	data->y_max = J_MAX;
	data->x_range = data->x_max - data->x_min;
	data->y_range = data->y_max - data->y_min;
	data->locked = 0;
}

// Mandelbrot : z starts at 0 ; c varies per px
// Julia : z starts at pixel's coordinates ; c is fixed
// Move out c of the pixel loop for better performance
// Initialize the pixel which will initialize z
void	render_julia(t_data *data)
{
	t_render	r;
	t_complex	c;
	t_complex	p;

	c = data->c;
	init_render(&r, data);
	p.y = data->y_min;
	while (r.y < WINDOW_HEIGHT)
	{
		r.x = 0;
		p.x = data->x_min;
		while (r.x < WINDOW_WIDTH)
		{
			r.z.x = p.x;
			r.z.y = p.y;
			r.iter = mandelbrot(&c, &r.z, data->max_iter);
			r.color = color_handler(data, r.iter, r.z);
			my_pixel_put(&data->img, r.x, r.y, r.color);
			p.x += r.dx;
			r.x++;
		}
		p.y += r.dy;
		r.y++;
	}
	mlx_put_image_to_window(data->mlx_conn, data->win, data->img.img, 0, 0);
}

// Map mouse position to a reasonable complex range
// Render the julia set with new c
// frame = increments each time the code runs
// throttling / skipping : render Julia only every 8 frames (smoother)
int	julia_mouse_move(int mouse_x, int mouse_y, void *param)
{
	t_data		*data;
	static int	frame;
	double		dx;
	double		dy;

	data = (t_data *)param;
	if (frame++ % 8 != 0)
		return (0);
	if (data->locked)
		return (0);
	dx = data->x_max / (double)WINDOW_WIDTH;
	dy = data->y_max / (double)WINDOW_HEIGHT;
	data->c.x = data->x_min + dx * (double)mouse_x;
	data->c.y = data->y_min + dy * (double)mouse_y;
	render_julia(data);
	return (0);
}
