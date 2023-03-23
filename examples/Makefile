CC = clang
LD = lld-link

CFLAGS = -I../ -Wall -fshort-wchar -mno-red-zone -fno-stack-protector -target x86_64-pc-win32-coff 
LFLAGS = -subsystem:efi_application -nodefaultlib -entry:efi_main

TARGET = hello-world.efi

all: $(TARGET)

%.efi: %.o
	$(LD) $(LFLAGS) $< -out:$@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(TARGET)
