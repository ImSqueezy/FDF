#include "FDF.h"

typedef struct parsing_data
{
	int			x;
	int			y;
	int			z;
	long int	color;
	int 		height;
	size_t 		width;
} p_data;

int	get_length(char **tmp)
{
	int	i;
	int	j;

	// i = 0;
	// while (tmp[i])
	// {
	// 	j = 0;
	// 	while (tmp[i][j])
	// 		printf("%c", tmp[i][j++]);
	// 	i++;
	// }
	i = 0;
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
			printf("%c", tmp[i][j++]);
		i++;
	}
	//printf("\n%d", j);
	return (j);
}

int	**file_read(char	*file)
{
	int		fd;
	int		i;
	char	*p;
	char	**tmp;
	int		**data;
	
	fd = open(file, O_RDONLY);
	p = get_next_line(fd);
	while (p)
	{
		tmp = ft_split(p, ' ');
		// convert each string to each corresponding array
			
		i = get_length(tmp);
		p = get_next_line(fd);
	}
	return (data);
}

int	main(int argc, char **argv)
{
	p_data	*pd_ptr;
	int **data;

	if (argc != 2)
		return (printf("exited from argc check"), 0);
	pd_ptr = (p_data *)malloc(sizeof(p_data));
	data = file_read(argv[1]);
	return (0);
}

// 1) store the file read in a double pointer, each line goes to an index
// 2) store the infos in a 2d array

// READ FILE CHECK IT'S VALIDE CHECK EXTENSION 
	// PARSE DATA INT INT[X][Y]
	// DAA + BRES 
	// ISOMETRI 
	// DRAW INTO MLX 
	// WHILE MOVING SHAPE SETROY IMAGE AND RE WRITE 
	// KEY
	// MENU

