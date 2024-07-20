TOOLCHAIN = riscv64-unknown-elf

build:
	$(TOOLCHAIN)-gcc src/spectre.c -Iinclude/ -o bin/spectre.elf -static -Os

asm: build
	$(TOOLCHAIN)-objdump -d bin/spectre.elf > src/spectre.asm

.PHONY = build
