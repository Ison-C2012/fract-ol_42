#!/bin/bash

xcc ()
{
	local mlx_dir="$HOME/path/to/minilibx-linux"
	cc "$@" -I"$mlx_dir" -L"$mlx_dir" -lmlx -lXext -lX11
}
