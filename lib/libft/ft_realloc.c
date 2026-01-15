/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_realloc.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/03 14:27:06 by adecheri       #+#    #+#                */
/*   Updated: 2025/06/03 14:27:15 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

// check if memory space is not null in space you want to malloc
// if so,
//	move block to addresses that are available and malloc/calloc/populate there
// would be best to set previous space to null after moving

void	**ft_realloc(void *ptr, unsigned int oldsize, unsigned int newsize)
{
	int		i;
	void	*new_ptr;

	if (!ptr)
		return (write(2, "Memory Allocation Failed\n", 25));
	new_ptr = ptr + oldsize;
	i = newsize - oldsize;
	while (i <= newsize)
	{
		if (new_ptr + i != NULL)
		{
			new_ptr += i + 1;
			i = -1;
		}
		i++;
	}
	if (new_ptr == (ptr + oldsize))
	{
		new_ptr = malloc(newsize - oldsize);
		return (free(new_ptr), &ptr);
	}
	new_ptr = malloc(newsize);
	ft_memmove(new_ptr, ptr, oldsize);
	return (free(ptr), &new_ptr);
}
