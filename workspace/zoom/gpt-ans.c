// zoom_sample.c (MiniLibX想定：Linuxのボタン4/5ホイール例)
// 重要なのは「scale/centerで複素平面↔ピクセルを対応させる」部分と
// 「ズーム時にmouse位置が指す複素座標(wx,wy)が変わらないようcenterを更新する」部分。

#include <math.h>
#include <stdlib.h>
#include <mlx.h>

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

	// ---- fractal view params ----
	double  center_x; // 複素平面の中心(実部)
	double  center_y; // 複素平面の中心(虚部)
	double  scale;    // 1ピクセルが複素平面で何単位か (小さいほどズームイン)
	int     max_iter;
}	t_app;

static void put_px(t_app *a, int x, int y, unsigned int c)
{
	char *p = a->addr + y * a->line_len + x * (a->bpp / 8);
	*(unsigned int *)p = c;
}

// Mandelbrot: c = (cx, cy), z0=0, z_{n+1}=z_n^2 + c
static unsigned int shade(int it, int max)
{
	// 超簡易：収束(=maxまで行った)は黒、それ以外は灰色
	if (it >= max) return 0x000000;
	int v = (it * 255) / max;
	return (v << 16) | (v << 8) | v;
}

static void render(t_app *a)
{
	for (int py = 0; py < H; py++)
	{
		for (int px = 0; px < W; px++)
		{
			// ピクセル(px,py) -> 複素平面(wx,wy)
			double wx = a->center_x + (px - W * 0.5) * a->scale;
			double wy = a->center_y + (py - H * 0.5) * a->scale;

			double zx = 0.0, zy = 0.0;
			int it = 0;
			while (it < a->max_iter)
			{
				// z^2: (zx + i zy)^2 = (zx^2 - zy^2) + i(2*zx*zy)
				double nx = zx*zx - zy*zy + wx;
				double ny = 2.0*zx*zy + wy;
				zx = nx; zy = ny;
				if (zx*zx + zy*zy > 4.0) break;
				it++;
			}
			put_px(a, px, py, shade(it, a->max_iter));
		}
	}
}

// Linux版minilibxだとホイール上=4, 下=5 が多い
static int on_mouse(int button, int mx, int my, void *param)
{
	t_app *a = (t_app *)param;

	if (button != 4 && button != 5)
		return 0;

	// ズーム倍率：上でズームイン(=scaleを小さく)、下でズームアウト
	double factor = (button == 4) ? 0.90 : (1.0 / 0.90);

	// まず「ズーム前」に、マウス位置が指している複素座標を取る
	double wx = a->center_x + (mx - W * 0.5) * a->scale;
	double wy = a->center_y + (my - H * 0.5) * a->scale;

	// scale更新
	a->scale *= factor;

	// マウスが指していた(wx,wy)が、ズーム後も同じピクセル(mx,my)に来るようcenterを補正
	a->center_x = wx - (mx - W * 0.5) * a->scale;
	a->center_y = wy - (my - H * 0.5) * a->scale;

	render(a);
	mlx_put_image_to_window(a->mlx, a->win, a->img, 0, 0);
	return 0;
}

static int on_key(int key, void *param)
{
	t_app *a = (t_app *)param;
	if (key == 65307) // ESC (X11)
		exit(0);
	return 0;
}

int main(void)
{
	t_app a;

	a.mlx = mlx_init();
	a.win = mlx_new_window(a.mlx, W, H, "zoom sample");
	a.img = mlx_new_image(a.mlx, W, H);
	a.addr = mlx_get_data_addr(a.img, &a.bpp, &a.line_len, &a.endian);

	// 初期ビュー（だいたい見やすい位置）
	a.center_x = -0.5;
	a.center_y = 0.0;
	a.scale = 3.0 / (double)W; // 画面横幅Wピクセルで複素平面の幅を約3.0にする
	a.max_iter = 80;

	render(&a);
	mlx_put_image_to_window(a.mlx, a.win, a.img, 0, 0);

	mlx_mouse_hook(a.win, on_mouse, &a);
	mlx_key_hook(a.win, on_key, &a);

	mlx_loop(a.mlx);
	return 0;
}

