# elf-segfault

Minimal reproducer for libelf mangled binary crashes.

Reproduce by running:

```
$ make repro
```

You should get:

```
rm -f ./testprog_copy
cp ./testprog ./testprog_copy
./elfwriter ./testprog_copy
./testprog_copy
make: *** [Makefile:14: repro] Segmentation fault
```

## Notes

When I use
https://sourceware.org/git/?p=elfutils.git;a=blob;f=tests/addsections.c;hb=HEAD
I get a similar segmentation fault.
