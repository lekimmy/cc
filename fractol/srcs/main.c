/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 02:56:50 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/03/14 19:56:20 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	parsing_error(void)
{
	ft_perror("Usage:\n./fractol mandelbrot\n./fractol tricorn\n");
	ft_perror("./fractol \"burning ship\"\n./fractol julia <x> <y>\n");
}

double	clamp_zoom_factor(double zoom_factor)
{
	if (zoom_factor < MAX_ZOOM_FACTOR)
		zoom_factor = MAX_ZOOM_FACTOR;
	return (zoom_factor);
}

// Program lifecycle :
// 1. Start
// 2. parse args
// 3. init fractal params
// 4. render
// 5. mouse zoom
// 6. update ranges
// 7. render again

// set up hooks before loop
// ESC with key_handler vs. ad hoc hook for ON_DESTROY (mouse/window)
// Julia hook : 6 = Motion Notify + (1L<<6) = PointerMotionMask
int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 1)
		return (parsing_error(), 1);
	if (!parser_init(argc, argv, &data))
		return (1);
	if (!init_data(&data))
		return (1);
	init_fractal(&data);
	render_fractal(&data);
	mlx_key_hook(data.win, &key_handler, &data);
	mlx_mouse_hook(data.win, &mouse_handler, &data);
	if (data.fractal == JULIA)
		mlx_hook(data.win, 6, 1 << 6, &julia_mouse_move, &data);
	mlx_hook(data.win, 17, 0, &close_handler, &data);
	mlx_loop(data.mlx_conn);
	return (0);
}
