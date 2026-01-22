#include "../../inc/cub3d.h"

void	parse_identifier(char *line, t_map *map)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		map->north = ft_strtrim(line + 3, "\n\t ");
	}

}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if (line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\n')
		{
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	dot_cub(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len > 0 && ft_strncmp(file + len - 4, ".cub", 4) != 0)
		return (FAILURE);
	return (SUCCESS);
}
