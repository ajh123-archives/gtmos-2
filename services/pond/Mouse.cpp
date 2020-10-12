/*
    This file is part of duckOS.

    duckOS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    duckOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with duckOS.  If not, see <https://www.gnu.org/licenses/>.

    Copyright (c) Byteduck 2016-2020. All rights reserved.
*/

#include <unistd.h>
#include "Mouse.h"

Mouse::Mouse(Window* parent): Window(parent, {0, 0, 3, 3}) {
	mouse_fd = open("/dev/input/mouse", O_RDONLY);
	if(mouse_fd < 0) {
		perror("Failed to open mouse");
		return;
	}
	inited = true;

	framebuffer().fill({{0,0}, 3, 3}, {255, 255, 255});
}

int Mouse::fd() {
	return mouse_fd;
}

bool Mouse::update() {
	MouseEvent events[32];
	ssize_t nread = read(mouse_fd, &events, sizeof(MouseEvent) * 32);
	if(!nread) return false;
	int num_events = (int) nread / sizeof(MouseEvent);

	Rect dims = rect();

	for(int i = 0; i < num_events; i++) {
		dims.position.x += events[i].x;
		dims.position.y -= events[i].y;
	}

	set_rect(dims);

	return true;
}
