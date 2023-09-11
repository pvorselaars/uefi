CC = clang
LD = lld-link

CFLAGS = -I. -Wall -fshort-wchar -mno-red-zone -fno-stack-protector -target x86_64-pc-win32-coff
LFLAGS = -subsystem:efi_application -nodefaultlib -entry:efi_main

BIN = $(patsubst %.c, %.efi, $(wildcard examples/*.c))

run: all
	qemu-system-x86_64 -bios /usr/share/ovmf/bios.bin -drive file=disk.img,format=raw -net none -nographic

all: disk.img $(BIN)
	mcopy -oi disk.img examples/*.efi ::

disk.img:
	dd if=/dev/zero of=disk.img bs=1K count=1440
	mformat -i disk.img -f 1440

%.efi: %.o
	$(LD) $(LFLAGS) $< -out:$@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm examples/*.efi
	rm disk.img
