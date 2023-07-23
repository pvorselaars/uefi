run: all
	qemu-system-x86_64 -bios /usr/share/ovmf/bios.bin -drive file=disk.img,format=raw -net none -nographic

all: disk.img examples
	sudo losetup -Pf disk.img
	sudo mkdir -p /mnt/disk
	sudo mount /dev/loop0p1 /mnt/disk
	make -C examples
	sudo mv examples/*.efi /mnt/disk
	sudo umount /mnt/disk
	sudo losetup -d /dev/loop0p1

disk.img:
	dd if=/dev/zero of=disk.img bs=1M count=48
	(echo g; echo n; echo ""; echo ""; echo ""; echo ""; echo t; echo 1; echo w) | fdisk disk.img
	sudo losetup -Pf disk.img
	sudo mkdosfs -F32 /dev/loop0p1
	sudo losetup -d /dev/loop0p1