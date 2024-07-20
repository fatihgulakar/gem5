build:
	riscv64-unknown-elf-g++ src/sieve.cpp -Iinclude/ -o bin/sieve.elf -static -Os -std=c++17

asm: build
	riscv64-unknown-elf-objdump -d bin/sieve.elf > src/sieve.asm

.PHONY = build
