includePath = R:/s/c/i
includePathNix = ~/s/cBao

.PHONY: baofiles
baofiles:
	gcc -ansi -g0 -Wall -Wextra -Wshadow -Wvla -pedantic-errors -o baofiles.exe baofiles.c -I $(includePath)

baofiles-d:
	gcc -ansi -g -static-libasan -fsanitize=address -Wall -Wextra -Wshadow -Wvla -pedantic-errors -o baofiles baofiles.c -I $(includePathNix)
	./baofiles
