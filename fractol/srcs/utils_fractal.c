/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fractal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 02:04:15 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/03/14 19:56:47 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int init_data(t_data *data)
{
	data->mlx_conn = mlx_init();
	if (!data->mlx_conn)
		return (0);
	data->win = mlx_new_window(data->mlx_conn, WINDOW_WIDTH, WINDOW_HEIGHT,
							   "fractal");
	if (!data->win)
		// return (mlx_destroy_display(data->mlx_conn), free(data->mlx_conn), 0);
		return (free(data->mlx_conn), 0);
	if (!create_img(data))
		// return (mlx_destroy_display(data->mlx_conn), free(data->mlx_conn), 0);
		return (free(data->mlx_conn), 0);
	return (1);
}

// Init first, render afterwards
// Otherwise every render resets the view = fractal state is constantly reset
// Zoom never survives the render
void init_fractal(t_data *data)
{
	if (data->fractal == MANDELBROT)
		init_data_mandelbrot(data);
	if (data->fractal == JULIA)
		init_data_julia(data);
	if (data->fractal == TRICORN)
		init_data_tricorn(data);
	if (data->fractal == BURNING_SHIP)
		init_data_bs(data);
}

void render_fractal(t_data *data)
{
	if (data->fractal == MANDELBROT)
		render_mandelbrot(data);
	if (data->fractal == JULIA)
		render_julia(data);
	if (data->fractal == TRICORN)
		render_tricorn(data);
	if (data->fractal == BURNING_SHIP)
		render_bs(data);
}

static int get_max_iter(t_data *data)
{
	if (data->fractal == MANDELBROT)
		return (MB_MAX_ITER);
	if (data->fractal == JULIA)
		return (J_MAX_ITER);
	if (data->fractal == TRICORN)
		return (T_MAX_ITER);
	if (data->fractal == BURNING_SHIP)
		return (BS_MAX_ITER);
	return (J_MAX_ITER);
}

// Keep far-out renders fast, but still show detail on zoom
// Scale iter according to min baseline + zoom factor
// 1 / zoom_factor grows fast when zooming in
// log to troubleshoot exponential growth > gradual increase
// log(1/zoom) = how deep zoom is
// zf 	// log(1/zf) // iter
// 1 	// 0 		// 50
// 0.1 	// 2.3 		// 52
// 0.01 // 4.6 		// 54
// *20 = how strongly zoom affects iterations
// 0.01 // 4.6 		// 142
void scale_max_iter(t_data *data)
{
	double zoom_factor;
	int max_iter;
	int fractal_max_iter;

	zoom_factor = data->x_max - data->x_min;
	fractal_max_iter = get_max_iter(data);
	max_iter = 50 + log(1 / zoom_factor) * 20;
	if (max_iter > fractal_max_iter)
		max_iter = fractal_max_iter;
	data->max_iter = max_iter;
}
