// zoom_axes_min.c
// Minimal “world coords + zoom” demo for MiniLibX (Linux, X11).
// Draws axes (x=0,y=0), a 1.0-unit grid, and a fixed point at world (1,1).
// Mouse wheel: zoom in/out around mouse cursor.

#include <stdlib.h>
#include <math.h>
#include <X11/X.h>
#include <mlx.h>

#define W 720
#define H 480

#define ESC 0xff1b
#define ZOOM_IN 4
#define ZOOM_OUT 5

#define COL_BG   0x00FFFFFF
#define COL_GRID 0x00E6E6E6
#define COL_AXIS 0x00000000
#define COL_DOT  0x00FF0000

typedef struct s_img {
	void *img;
	char *addr;
	int   bpp;
	int   line_len;
	int   endian;
} t_img;

typedef struct s_view {
	double cx;     // screen center in world coords
	double cy;
	double scale;  // world units per pixel
} t_view;

typedef struct s_app {
	void  *mlx;
	void  *win;
	t_img  im;
	t_view v;
} t_app;

static void	put_pixel(t_app *a, int x, int y, unsigned int color)
{
	char *p;

	if (x < 0 || x >= W || y < 0 || y >= H)
		return;
	p = a->im.addr + y * a->im.line_len + x * (a->im.bpp / 8);
	*(unsigned int *)p = color;
}

static void	clear_img(t_app *a, unsigned int color)
{
	int x, y;

	y = 0;
	while (y < H)
	{
		x = 0;
		while (x < W)
			put_pixel(a, x++, y, color);
		y++;
	}
}

static int	world_to_sx(t_view *v, double wx)
{
	return (int)llround((wx - v->cx) / v->scale + (double)W / 2.0);
}

static int	world_to_sy(t_view *v, double wy)
{
	return (int)llround((wy - v->cy) / v->scale + (double)H / 2.0);
}

static void	screen_to_world(t_view *v, int sx, int sy, double *wx, double *wy)
{
	*wx = v->cx + ((double)sx - (double)W / 2.0) * v->scale;
	*wy = v->cy + ((double)sy - (double)H / 2.0) * v->scale;
}

static void	draw_vline(t_app *a, int x, unsigned int color)
{
	int y = 0;
	while (y < H)
		put_pixel(a, x, y++, color);
}

static void	draw_hline(t_app *a, int y, unsigned int color)
{
	int x = 0;
	while (x < W)
		put_pixel(a, x++, y, color);
}

static void	draw_dot(t_app *a, int sx, int sy, unsigned int color)
{
	int dx, dy;

	dy = -2;
	while (dy <= 2)
	{
		dx = -2;
		while (dx <= 2)
		{
			if (dx*dx + dy*dy <= 4) // small disk
				put_pixel(a, sx + dx, sy + dy, color);
			dx++;
		}
		dy++;
	}
}

static void	render(t_app *a)
{
	// visible world range
	double wx_min = a->v.cx - (double)W / 2.0 * a->v.scale;
	double wx_max = a->v.cx + (double)W / 2.0 * a->v.scale;
	double wy_min = a->v.cy - (double)H / 2.0 * a->v.scale;
	double wy_max = a->v.cy + (double)H / 2.0 * a->v.scale;

	clear_img(a, COL_BG);

	// grid lines at integer world coords
	// (this is what makes zoom visually obvious)
	int ix0 = (int)floor(wx_min);
	int ix1 = (int)ceil (wx_max);
	int iy0 = (int)floor(wy_min);
	int iy1 = (int)ceil (wy_max);

	for (int ix = ix0; ix <= ix1; ix++)
		draw_vline(a, world_to_sx(&a->v, (double)ix), COL_GRID);
	for (int iy = iy0; iy <= iy1; iy++)
		draw_hline(a, world_to_sy(&a->v, (double)iy), COL_GRID);

	// axes (world x=0 and y=0)
	draw_vline(a, world_to_sx(&a->v, 0.0), COL_AXIS);
	draw_hline(a, world_to_sy(&a->v, 0.0), COL_AXIS);

	// fixed world point at (1,1)
	draw_dot(a, world_to_sx(&a->v, 1.0), world_to_sy(&a->v, 1.0), COL_DOT);

	mlx_put_image_to_window(a->mlx, a->win, a->im.img, 0, 0);
}

static int	close_win(t_app *a)
{
	if (a->win) mlx_destroy_window(a->mlx, a->win);
	exit(0);
	return (0);
}

static int	key_hook(int keycode, t_app *a)
{
	if (keycode == ESC)
		return (close_win(a));
	return (0);
}

static int	mouse_hook(int button, int x, int y, t_app *a)
{
	double wx0, wy0;
	double zoom;

	if (button != ZOOM_IN && button != ZOOM_OUT)
		return (0);

	// 1) world position under the mouse BEFORE zoom
	screen_to_world(&a->v, x, y, &wx0, &wy0);

	// 2) update scale
	zoom = 0.9; // smaller => slower zoom
	if (button == ZOOM_IN)
		a->v.scale *= zoom;
	else
		a->v.scale /= zoom;

	// 3) adjust center so that (wx0,wy0) stays under the cursor
	a->v.cx = wx0 - ((double)x - (double)W / 2.0) * a->v.scale;
	a->v.cy = wy0 - ((double)y - (double)H / 2.0) * a->v.scale;

	render(a);
	return (0);
}

int	main(void)
{
	t_app a;

	a.mlx = mlx_init();
	a.win = mlx_new_window(a.mlx, W, H, "world coords zoom demo");
	a.im.img = mlx_new_image(a.mlx, W, H);
	a.im.addr = mlx_get_data_addr(a.im.img, &a.im.bpp, &a.im.line_len, &a.im.endian);

	// camera / view init
	a.v.cx = 0.0;
	a.v.cy = 0.0;
	a.v.scale = 0.02; // world units per pixel

	render(&a);

	mlx_mouse_hook(a.win, mouse_hook, &a);
	mlx_key_hook(a.win, key_hook, &a);
	mlx_hook(a.win, DestroyNotify, StructureNotifyMask, close_win, &a);

	mlx_loop(a.mlx);
	return (0);
}
