/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 00:35:07 by fousse            #+#    #+#             */
/*   Updated: 2022/01/20 18:26:51 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

void	arrange_color_force(int *color, double height, int y)
{
	double	shift_force;

	*color = g_game.map.ceiling_c;
	shift_force = fmod(y, height / 2.0) / (height / 2.0);
	if (y >= height / 2)
	{
		*color = g_game.map.floor_c;
		shift_force = (double)1 - shift_force;
	}
	*color = color_shift_int(*color, BLACK, shift_force / 1.5);
}

t_img	create_background(double width, double height)
{
	t_img	img;
	int		x;
	int		y;
	int		color;

	x = 0;
	y = 0;
	my_mlx_new_image(get_mlx()->mlx, &img, width, height);
	while (x + y * width < width * height)
	{
		arrange_color_force(&color, height, y);
		my_mlx_pixel_put(img, x, y, color);
		if (++x == width)
		{
			x = 0;
			y++;
		}
	}
	return (img);
}

void	draw_background(t_img img)
{
	t_img	*win_img;
	int		x;
	int		y;
	int		back_y;
	int		color;

	x = 0;
	y = 0;
	back_y = 0;
	win_img = &g_game.game_img;
	while (x + back_y * (img.width / 4) < (img.width / 4) * img.height)
	{
		color = *(unsigned int *)
			(img.addr + (back_y * img.width + x * (img.bpp / 8)));
		my_mlx_pixel_put(*win_img, x, y, color);
		if (++x == img.width / 4)
		{
			x = 0;
			y++;
			back_y++;
		}
	}
}
