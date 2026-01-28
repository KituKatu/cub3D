/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:39:22 by adecheri          #+#    #+#             */
/*   Updated: 2026/01/28 12:24:03 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*If any misconfiguration of any kind is encountered in the file, the program
    must exit properly and return "Error\n" followed by an explicit error message
    of your choice.
*/

int	ft_exit_errc(const char *msg, void **ptr, char id)
{
	if (msg)
		printf("%s\n", msg);
	if (*ptr)
		ft_clean_cubed(ptr, id);
	exit(EXIT_FAILURE);
}
