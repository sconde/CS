V=
#V=@
CFORMAT=clang-format-6.0

CC=gcc
CFLAGS=-Wall -Werror -Wextra #-DDEBUG

.PHONY: idshow format clean

idshow: idshow.c error_functions.c ugid_functions.c
	@echo + Building $@ utility...
	$(V)$(CC) $(CFLAGS) -o $@ $^

format:
	@echo + Formatting src...
	$(V)find . -name "*.c" -o -name "*.h" | xargs $(CFORMAT) -i

clean:
	@echo - Cleaning up all executables...
	rm -f idshow
