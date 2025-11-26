#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <mlx.h>


typedef struct s_vars
{
	void	*mlx;
	void	*win;

//	t_pxl	*pxl;
} t_vars;

/*SD*/
#define WIDTH 720
#define HEIGHT 480

/*HD
#define WIDTH 1280
#define HEIGHT 720
*/

/*Full HD
#define WIDTH 1920
#define HEIGHT 1080
*/

#define ESC 0xff1b

int	window_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESC)
		window_close(vars);
	printf("%d\n", keycode);
	return (0);
}

void *mlx_new_image ( void *mlx_ptr, int width, int height );
char *mlx_get_data_addr ( void *img_ptr, int *bits_per_pixel, int *size_line, int *endian );
int mlx_put_image_to_window ( void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y );
unsigned int mlx_get_color_value ( void *mlx_ptr, int color );
void *mlx_xpm_to_image ( void *mlx_ptr, char **xpm_data, int *width, int *height );
void *mlx_xpm_file_to_image ( void *mlx_ptr, char *filename, int *width, int *height );
int mlx_destroy_image ( void *mlx_ptr, void *img_ptr );

int	main(void)
{
	t_vars	vars;
	void	*img;
	char	*data_adr;
	int		*bpp;
	int		*size_len;
	int		*endian;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "keitotak's screen");
	img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	data_adr = mlx_get_data_addr(img, bpp, size_len, endian);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, window_close, &vars);
	mlx_loop(vars.mlx);
	return 0;
}
