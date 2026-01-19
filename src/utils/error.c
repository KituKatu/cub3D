/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   error.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/16 16:39:22 by adecheri       #+#    #+#                */
/*   Updated: 2026/01/16 16:39:25 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*If any misconfiguration of any kind is encountered in the file, the program
    must exit properly and return "Error\n" followed by an explicit error message
    of your choice.
*/




int ft_exit_errc(const char *msg, void **ptr)
{
    if (msg)
        printf("%s\n", msg);
    if (*ptr)
        ft_clean_cubed(ptr);
    exit(EXIT_FAILURE);
}