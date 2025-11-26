#include <mlx.h>

int	main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1980, 1080, "test window");
	mlx_loop(mlx);
	return (0);
}
