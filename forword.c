// minilibx is a way to create graphical softwar
// provides simple window creation, drawing tool, image and basic events management


#include "FDF.h"

typedef struct s_data
{
    void    *mlx_ptr; // a pointer that will be used
                    // initializing the connection
    void    *win_ptr;
} t_data;

int on_keypress(int keysym, t_data *data)
{
    (void)data;
    printf("Pressed key: %d\\n", keysym);
    return (0);
}

int handle_input(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
        mlx_destroy_window((*data).mlx_ptr, (*data).win_ptr);
    return (0);
}


int main()
{
    t_data  data;

    // we need to initialize the connection between our program and the display
    // once done we can draw pixels on the window and manage events
    data.mlx_ptr = mlx_init(); // mlx init creates a struct which contains
            // all the required data for mlx to function currectly.
            // it returns a void pointer which will be used for further calls
            // or null in failure.
    if (data.mlx_ptr == NULL)
        return (0);
    data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 300, "DISPLAY");
            // it returns a window identifier that can be used for other minilibX calls
            // or null in failure
    if (data.win_ptr == NULL)
        return (free(data.mlx_ptr), 0);

    mlx_key_hook(data.win_ptr, &handle_input, &data);

    mlx_loop(data.mlx_ptr);
    mlx_destroy_display(data.mlx_ptr);
    // mlx_loop is used in order to receive events, it is an infinit loop and never returns
    // 
    return (0);
}