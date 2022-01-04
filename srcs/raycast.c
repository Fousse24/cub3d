/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:50:06 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/03 20:22:10 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
*	Draw a column of pixel based on a tile/wall.
*/
int	draw3d(float dist, double cast_angle, t_coll coll, int x)
{
	float	height;
	int		color;
	int		y;
	float	offset = 0;

	dist = dist * cos((deg_to_rad((int)cast_angle)));
	height = (g_game.map.size * WIN_H) / dist;
	if (height > WIN_H)
	{
		offset = (height - WIN_H) / 2;
		height = WIN_H;
	}
	y = (WIN_H - height) / 2;
	if (coll.dir & NORTH)
		fill_with_texture(&get_mlx()->img, &g_game.texture[0], x, y, height, coll, offset, 1);
	else if (coll.dir & SOUTH)
		fill_with_texture(&get_mlx()->img, &g_game.texture[1], x, y, height, coll, offset, 1);
	else if (coll.dir & WEST)
		fill_with_texture(&get_mlx()->img, &g_game.texture[2], x, y, height, coll, offset, 0);
	else if (coll.dir & EAST)
		fill_with_texture(&get_mlx()->img, &g_game.texture[3], x, y, height, coll, offset, 0);
	return (0);
}

/*
*	Check collisions and draw pixel columns based on collisions.
*	Can also visually represent raycast in a 2d image.
*/
int	raycast_draw_all(t_pos pos, double rot, double view)
{
	int		win_x;
	float	dist;
	double	base_rot;
	t_coll	coll;

	coll = new_collider(new_pos(0, 0, 0), 0, 0);
	win_x = 0;
	base_rot = rot;
	rot -= view / 2;
	while (win_x < WIN_W)
	{
		if (rot >= 360)
			rot = fmod(rot, 360);
		if (rot < 0)
			rot = 360.0 + rot;
		coll = check_intersections(pos.x, pos.y, rot);
		dist = get_draw_distance(pos, rot, coll.pos);
		//dist = sqrt(pow((coll.pos.x - pos.x), 2) + pow((coll.pos.y - pos.y), 2));
		draw3d(dist, base_rot - rot, coll, WIN_W - win_x);
		win_x++;
		rot += (view / WIN_W);
	}
	return (1);
}

// Literally draw a raycast on the mlx image
int	raycast_draw(t_pos pos, double rot, double dist)
{
	t_pos	r_pos;
	int		i;

	i = 0;
	r_pos = new_pos(pos.x, pos.y, pos.z);
	while (i++ < dist && i < 800)
	{
		my_mlx_pixel_put(get_mlx()->img, r_pos.x, r_pos.y, 0x00FF00);
		r_pos = move_pos(r_pos, rot, 1, 0);
	}
	return (1);
}
