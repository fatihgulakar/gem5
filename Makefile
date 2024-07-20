GEM5=./build/RISCV/gem5.opt
CFG_PATH=learning_gem5/part1/two_level.py
KONATA_PATH=./Konata

GEM5_OPTS = --verbose
GEM5_OPTS += --debug-flags=O3PipeView
GEM5_OPTS += --debug-start=1
GEM5_OPTS += --debug-file=trace.out

CFG_OPTS =  --l2_size='2MB'
CFG_OPTS += --l1d_size='512kB'
CFG_OPTS += --l1i_size='512kB'

tests:
	make -C tests/test-progs/spectre build
	make -C tests/test-progs/riscv-coremark build
	make -C tests/test-progs/sieve build
	make -C tests/test-progs/daxpy build

run:
	$(GEM5) $(GEM5_OPTS) configs/$(CFG_PATH) $(CFG_OPTS)

konata:
	$(KONATA_PATH)/konata.sh &

.PHONY: tests run konata
