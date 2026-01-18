/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:13:00 by adecheri          #+#    #+#             */
/*   Updated: 2026/01/16 16:54:55 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	dot_cub(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len > 0 && ft_strncmp(file + len - 4, ".cub", 4) != 0)
	{
		return (SUCCES);
	}
	return (FAILURE);
}

int	main(int ac, char **av)
{
	int	fd;

	if(ac != 2)
	{
		//error_function
		return (FAILURE);
	}
	if(!dot_cub(av[1]))
	{
		//error_function
		printf("Wrong file extention\n");
		return (FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if(fd < 0)
	{
		//error_funtion
		return (FAILURE);
	}
	close(fd);
	return (SUCCES);
}
