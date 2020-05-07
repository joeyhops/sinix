GPPPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = obj/loader.o \
					obj/gdt.o \
				 	obj/drivers/driver.o \
				 	obj/hwcom/port.o \
				 	obj/hwcom/interruptstubs.o \
				 	obj/hwcom/interrupts.o \
				 	obj/hwcom/pci.o \
					obj/drivers/keyboard.o \
				 	obj/drivers/mouse.o \
				 	obj/drivers/vga.o \
					obj/kernel.o

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	gcc $(GPPPARAMS) -o $@ -c $<

obj/%.o: src/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

sinix.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

install: sinix.bin
	sudo cp $< ./sin/boot/sinix.bin

sinix.iso: sinix.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "Sinix 0.0.0.1" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/sinix.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=./$@ ./iso
	rm -rf iso

run: sinix.iso
	qemu-system-i386 -cdrom sinix.iso -vga std

.PHONY: clean
clean:
	rm -rf obj sinix.bin sinix.iso
