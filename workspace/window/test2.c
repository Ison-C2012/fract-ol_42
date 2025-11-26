#include <mlx.h>
#include <X11/X.h>
#include <stdlib.h>

//#include "mlx.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
} t_vars;

int	win_close(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1980, 1080, "test window");
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, win_close, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
