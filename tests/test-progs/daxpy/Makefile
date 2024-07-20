build:
	riscv64-unknown-elf-g++ src/daxpy.cpp -Iinclude/ -o bin/daxpy.elf -static -O2 -std=c++17

asm: build
	riscv64-unknown-elf-objdump -d bin/daxpy.elf > src/daxpy.asm

.PHONY = build
