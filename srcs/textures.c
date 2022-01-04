/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:38:28 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/04 17:03:38 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_pos	textures_index(t_coll coll, float offset, float height, int side)
{
	double	i_x;
	double	i_y;

	if (side)
		i_x = (fmod(fmod(coll.pos.x, TILE_SIZE), TEXTURES_SIZE));
	else
		i_x = (fmod(fmod(coll.pos.y, TILE_SIZE), TEXTURES_SIZE));
	i_y = (TEXTURES_SIZE * offset) / (height + (offset * 2));
	return (new_pos(i_x, i_y, 0));
}

void	fill_with_texture(t_img *text, t_pos pos, float height, t_pos index)
{
	t_img	*win;
	double	y_step;
	int		bytes;
	int		color;

	win = &get_mlx()->img;
	y_step = (((float)text->height - (index.y * 2))
			/ (height + (win->height - height) / TILE_SIZE));
	bytes = (text->bpp / 8);
	while (pos.y < height + (win->height - height) / 2)
	{
		color = *((unsigned int *)(text->addr
					+ ((int)index.y * text->width + (int)index.x * bytes)));
		color = color_shift_int(color, BLACK, ((WIN_H - height) / WIN_H) / 1.5);
		if (pos.x >= 0 && pos.x < win->width)
			my_mlx_pixel_put(*win, pos.x, pos.y, color);
		index.y += y_step;
		pos.y++;
	}
}