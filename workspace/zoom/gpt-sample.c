// zoom_circle.c — 円(アウトライン)を「scale(拡大率)」でズームする最小例
// scale = 1.0 のとき「ワールド座標 1.0」が「画面 1px」になる、という定義。
// scale が大きいほどズームイン（大きく表示）、小さいほどズームアウト。
// マウス位置を基準にズームするため、ズーム前後で「マウス下のワールド座標」が同じになるよう view を補正する。

#include <math.h>
#include <stdlib.h>
#include "mlx.h"

#define W 800
#define H 600

typedef struct s_app {
	void   *mlx;
	void   *win;
	void   *img;
	char   *addr;
	int     bpp;
	int     line_len;
	int     endian;

	// view（ワールド座標系 -> 画面への変換用）
	double  view_x;   // 画面中心(W/2,H/2)が指すワールドX
	double  view_y;   // 画面中心(W/2,H/2)が指すワールドY
	double  scale;    // pixel_per_world_unit（大きいほどズームイン）

	// 図形（ワールド座標で定義）
	double  c_x;
	double  c_y;
	double  r;
}	t_app;

static void put_px(t_app *a, int x, int y, unsigned int c)
{
	if (x < 0 || x >= W || y < 0 || y >= H) return;
	char *p = a->addr + y * a->line_len + x * (a->bpp / 8);
	*(unsigned int *)p = c;
}

static void clear_img(t_app *a, unsigned int c)
{
	for (int y = 0; y < H; y++)
		for (int x = 0; x < W; x++)
			put_px(a, x, y, c);
}

// ピクセル(px,py) -> ワールド(wx,wy)
static void screen_to_world(t_app *a, int px, int py, double *wx, double *wy)
{
	*wx = a->view_x + (px - W * 0.5) / a->scale;
	*wy = a->view_y + (py - H * 0.5) / a->scale;
}

// 円のアウトライン：|dist - r| < thickness を満たすピクセルを塗る
static void render_circle(t_app *a)
{
	clear_img(a, 0x101010);

	// 線の太さを「2px固定」にしたいので、ワールド厚みに変換
	double thickness_world = 2.0 / a->scale;

	for (int y = 0; y < H; y++)
	{
		for (int x = 0; x < W; x++)
		{
			double wx, wy;
			screen_to_world(a, x, y, &wx, &wy);

			double dx = wx - a->c_x;
			double dy = wy - a->c_y;
			double dist = sqrt(dx*dx + dy*dy);

			if (fabs(dist - a->r) <= thickness_world)
				put_px(a, x, y, 0xFFFFFF);
		}
	}
}

static void redraw(t_app *a)
{
	render_circle(a);
	mlx_put_image_to_window(a->mlx, a->win, a->img, 0, 0);
}

// Linux版minilibxだとホイール上=4, 下=5 が多い
static int on_mouse(int button, int mx, int my, void *param)
{
	t_app *a = (t_app *)param;
	if (button != 4 && button != 5) return 0;

	// ズーム係数（上でズームイン＝scale増加）
	double factor = (button == 4) ? 1.10 : (1.0 / 1.10);

	// ズーム前：マウス下のワールド座標を取得
	double wx, wy;
	screen_to_world(a, mx, my, &wx, &wy);

	// scale 更新
	a->scale *= factor;

	// ズーム後も「wx,wy」が同じ(mx,my)に来るよう view を補正
	a->view_x = wx - (mx - W * 0.5) / a->scale;
	a->view_y = wy - (my - H * 0.5) / a->scale;

	redraw(a);
	return 0;
}

static int on_key(int key, void *param)
{
	(void)param;
	if (key == 65307) exit(0); // ESC (X11)
	return 0;
}

static int on_close(void *param)
{
	(void)param;
	exit(0);
	return 0;
}

int main(void)
{
	t_app a;

	a.mlx = mlx_init();
	a.win = mlx_new_window(a.mlx, W, H, "Circle Zoom (scale demo)");
	a.img = mlx_new_image(a.mlx, W, H);
	a.addr = mlx_get_data_addr(a.img, &a.bpp, &a.line_len, &a.endian);

	// 初期 view：中心を(0,0)に、scale=1px/1world_unit
	a.view_x = 0.0;
	a.view_y = 0.0;
	a.scale  = 1.0;

	// 円をワールド座標で定義（中心(0,0)、半径100）
	a.c_x = 0.0;
	a.c_y = 0.0;
	a.r   = 100.0;

	redraw(&a);

	mlx_mouse_hook(a.win, on_mouse, &a);
	mlx_key_hook(a.win, on_key, &a);
	mlx_hook(a.win, 17, 0, on_close, &a); // DestroyNotify

	mlx_loop(a.mlx);
	return 0;
}
