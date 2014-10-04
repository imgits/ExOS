SOURCES = $(shell find src -name "*.cpp" -o -name "*.s")

OBJECTS1 = $(SOURCES:.cpp=.o)
OBJECTS = $(OBJECTS1:.s=.o)

CXXFLAGS = -Weverything -Werror \
	   -Wno-c++98-compat -Wno-c++98-c++11-compat-pedantic \
	   -Wno-c++98-compat-pedantic -Wno-c99-extensions \
	   -Wno-gnu-designator -Wno-gnu-string-literal-operator-template \
	   -ffreestanding -flto \
	   -fno-exceptions -fno-rtti \
	   -std=c++1y \
	   -iquote src/ \
	   -O \
	   -target x86_64--macho

LDFLAGS = -static \
	  -e _kmain \
	  -pie \
	  -pagezero_size 0x0 \
	  -image_base 0x1000 \
	  -macosx_version_min `sw_vers -productVersion` \
	  -u _memset -u ___bzero \
	  -arch x86_64

HDIUTIL_FLAGS = create -srcfolder image -fs MS-DOS -fsargs "-F 32" \
		-format UDRW -layout GPTSPUD -size 40m -volname LUMINOS -ov

QEMU_FLAGS = -pflash OVMF.fd

QEMU_DEBUG_FLAGS = $(QEMU_FLAGS) -debugcon file:ovmf_debug.log \
		   -global isa-debugcon.iobase=0x402 \
		   -d guest_errors,cpu_reset,in_asm \
		   -S -s -no-reboot

all: exos.efi

disk: exos.efi
	cp exos.efi image/EFI/BOOT/BOOTx64.EFI
	hdiutil $(HDIUTIL_FLAGS) -o disk
	mv disk.dmg disk

run: disk OVMF.fd
	qemu-system-x86_64 $(QEMU_FLAGS) disk

run-debug: disk OVMF.fd
	qemu-system-x86_64 $(QEMU_DEBUG_FLAGS) disk

exos.macho: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o exos.macho

exos.efi: exos.macho mtoc
	./mtoc exos.macho exos.efi
