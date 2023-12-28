#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <gelf.h>
#include <libelf.h>

#define elf_err(fmt, ...) \
        fprintf(stderr, "elf: " fmt ": %s\n", ##__VA_ARGS__, elf_errmsg(-1))

int main(int argc, char **argv)
{
	Elf *elf = NULL;
	int fd = -1;
	int err = 1;

	if (argc != 2) {
		fprintf(stderr, "Usage: ./elfwriter infile\n");
		goto out;
	}

	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		perror("open");
		goto out;
	}

	if (elf_version(EV_CURRENT) == EV_NONE) {
		elf_err("elf_version");
		goto out;
	}

	elf = elf_begin(fd, ELF_C_RDWR, NULL);
	if (!elf) {
		elf_err("elf_begin");
		goto out;
	}

	if (elf_update(elf, ELF_C_WRITE) < 0) {
		elf_err("elf_update");
		goto out;
	}

	err = 0;
out:
	if (elf)
		elf_end(elf);
	if (fd >= 0)
		close(fd);
	return err;
}
