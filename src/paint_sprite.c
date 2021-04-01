/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atweek <atweek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:09:30 by atweek            #+#    #+#             */
/*   Updated: 2021/04/01 08:58:06 by atweek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void paint_sprites(t_all *all_st,int a)
{
	int i;
	int j;

	i = 0;
	while (i < all_st->sprites[a].screen_size)
	{
		if (all_st->sprites[a].h_offset + i >= WIGHT || all_st->sprites[a].h_offset + i < 0)
		{
			i++;
			continue;
		}
		j = 0;
		while (j < all_st->sprites[a].screen_size)
		{
			if (all_st->sprites[a].v_offset + j >= HEIGHT || all_st->sprites[a].v_offset + j < 0)
			{
				j++;
				continue;
			}
			my_mlx_pixel_put(all_st->win, all_st->sprites[a].h_offset + i,all_st->sprites[a].v_offset  + j,0xFF0000);
			j++;
		}
		i++;
	}
		printf("222\n");

	
}

int count_sprite(t_all *all_st)
{
	int	i;
	int	j;
	int	count;
	
	count = 0;
	i = 0;
	j = 0;
	while (all_st->map[j])
	{
		while (all_st->map[j][i])
		{
			if (all_st->map[j][i]  == '2') 
			{
				count++;
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (count);
}

void fill_sprite(t_all *all_st)
{
	int	j;
	int i;
	int a;
	

	i = 0;
	j = 0;
	a = 0;
	while (all_st->map[j])
	{
		while (all_st->map[j][i])
		{
			if (all_st->map[j][i]  == '2') 
			{
				all_st->sprites[a].x = (float)i * SCALE;
				all_st->sprites[a].y =  (float)j * SCALE;
				all_st->sprites[a].dir =  0;
				math_sprite(all_st,all_st->count_sprite);
				a++;
			}
			i++;
		}
		i = 0;
		j++;
	}
} 


void math_sprite(t_all *all_st,int count)
{
	int a;
	// int count;
	// int screen_size;
	(void)count;
	a = -1;//-1
	// count = count_sprite(all_st);
	while (++a < count)
	{
		all_st->sprites[a].dist = sqrt(pow(all_st->plr->x - all_st->sprites[a].x,2) + pow(all_st->plr->y - all_st->sprites[a].y,2));
		all_st->sprites[a].screen_size = (HEIGHT / all_st->sprites[a].dist) * 32;
		all_st->sprites[a].dir = atan2(all_st->sprites[a].y - all_st->plr->y, all_st->sprites[a].x - all_st->plr->x);
		while (all_st->sprites[a].dir - all_st->plr->dir>  M_PI)
			all_st->sprites[a].dir -= 2*M_PI; 
    	while (all_st->sprites[a].dir - all_st->plr->dir < -M_PI)
			all_st->sprites[a].dir += 2*M_PI;
		all_st->sprites[a].h_offset = (all_st->sprites[a].dir - all_st->plr->dir)*(WIGHT)/(M_PI / 3) + (WIGHT)/2 - all_st->sprites[a].screen_size;
    	all_st->sprites[a].v_offset = HEIGHT / 2- all_st->sprites[a].screen_size;
		printf("111\n");
		paint_sprites(all_st,a);

	}
	// paint_sprites(all_st);
}