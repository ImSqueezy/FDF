#include "FDF.h"

int	handle_no_event(void *data)
{
    return (0);
}

int	key_handle(int keysysm, t_gl *gl_ptr)
{

	printf("%d\n", keysysm);
	return (0);
}

int	hooks(t_gl *gl_ptr)
{
	mlx_loop_hook(gl_ptr->mlx_ptr, &handle_no_event, &gl_ptr);
	mlx_hook(gl_ptr->win_ptr, 17, 0, &key_handle, gl_ptr);
	return (0);
}