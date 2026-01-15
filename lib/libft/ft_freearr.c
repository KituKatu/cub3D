/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_freearr.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/07 12:45:09 by adecheri       #+#    #+#                */
/*   Updated: 2025/06/07 12:45:10 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freearr(void **array)
{
	int	i;

	if (array)
	{
		i = -1;
		while (array[++i])
			ft_safefree(&array[i]);
		ft_safefree(array);
	}
}