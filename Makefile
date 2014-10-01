VPATH = src:src/lib/:src/font/:src/framebuffer/:src/uefi/:src/cpuid/

OBJECTS = main.o error.o printf.o compiler_needed.o assert.o font.o \
	  framebuffer.o uefi.o cpuid.o

CXXFLAGS = -Weverything \
	   -Wno-c++98-compat \
	   -Wno-c++98-c++11-compat-pedantic \
	   -Wno-c++98-compat-pedantic \
	   -Wno-c99-extensions \
	   -Wno-gnu-designator \
	   -Wno-gnu-string-literal-operator-template \
	   -ffreestanding \
	   -fno-exceptions \
	   -fno-rtti \
	   -fno-stack-protector \
	   -std=c++1y \
	   -iquote src/ \
	   -g

LDFLAGS = -static -e _kmain -pie -pagezero_size 0x0 -image_base 0x1000 \
	  -macosx_version_min `sw_vers -productVersion` \
	  -u _memset -u ___bzero

HDIUTIL_FLAGS = create -srcfolder image -fs MS-DOS -fsargs "-F 32" \
		-format UDRW -layout GPTSPUD -size 40m -volname LUMINOS -ov

QEMU_FLAGS = -pflash OVMF.fd -no-reboot -cpu Haswell

QEMU_DEBUG_FLAGS = $(QEMU_FLAGS) -debugcon file:ovmf_debug.log \
		   -global isa-debugcon.iobase=0x402 \
		   -d guest_errors,cpu_reset,in_asm -S -s

all: exos.efi

disk: exos.efi
	cp exos.efi image/EFI/BOOT/BOOTx64.EFI
	hdiutil $(HDIUTIL_FLAGS) -o disk
	mv disk.dmg disk

run: disk
	qemu-system-x86_64 $(QEMU_FLAGS) disk

run-debug: disk
	qemu-system-x86_64 $(QEMU_DEBUG_FLAGS) disk

exos.macho: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o exos.macho

exos.efi: exos.macho
	./mtoc exos.macho exos.efi
