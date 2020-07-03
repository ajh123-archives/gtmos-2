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

//A simple program that forks and then prints "Hello!"

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char** argv) {
	if(argc > 1) {
		int f = open(argv[1], O_RDONLY);
		if(f != -1) {
			char buf[512];
			int nread;
			while((nread = read(f, buf, 512)) > 0) {
				write(STDOUT_FILENO, buf, nread);
			}
			if(errno) {
				printf("cat: Error %d\n", errno);
			}
		} else {
			switch(errno) {
				case ENOENT:
					printf("cat: No such file\n");
					break;
				default:
					printf("cat: Error %d\n", errno);
			}
			return errno;
		}
	} else {
		printf("cat: Please specify a file\n");
		return 1;
	}
	return 0;
}
