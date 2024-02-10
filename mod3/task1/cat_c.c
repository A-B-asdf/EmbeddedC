#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv) {
	char buf[BUFSIZ];
	int fd = 0;
	if (argc > 1) {
		fd = open(argv[1], O_RDONLY, 0);
	}
	int n;
	while ((n = read(fd, buf, BUFSIZ)) > 0) {
		write(1, buf, n);
	}
	return 0;
}

