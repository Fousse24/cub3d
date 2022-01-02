/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 15:53:43 by fousse            #+#    #+#             */
/*   Updated: 2022/01/01 20:15:58 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

/*t_map	new_map(int width, int height, )
{
	
	return (t);
}*/

/*
* Function to be removed; used for initial testing when we didn't have parsing
*/
int	*copy_map(int *src, int size)
{
	int	*tiles;
	int	i;

	tiles = malloc(sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		tiles[i] = src[i];
		i++;
	}
	return (tiles);
}