# EVE, ready to run

EVE is installed. The examples are in `examples/`, the runner scripts our CI uses are in
`toolchain/`, and the compilers, cross-toolchains and emulators are the ones EVE is tested with.

## Run an example on your own machine

```
cd examples/bilateral
g++-14 -std=c++23 -O3 -march=native main.cpp -o bilateral
./bilateral --size 50000 --iterations 2000
```

## Run it on an instruction set you do not have

Intel SDE emulates AVX-512 and later on any x86. It tells you whether your code *runs* and what it
computes - not how fast it is: emulated AVX-512 is far slower than native scalar, so the timings
this benchmark prints under SDE mean nothing.

```
g++-14 -std=c++23 -O3 -march=skylake-avx512 main.cpp -o bilateral
sde64 -skx -- ./bilateral --size 50000 --iterations 200
```

## Run it on another architecture

Cross-compile, then run the result under QEMU. Note the `-I/usr/local/include`: EVE is installed
there, and a cross-compiler does not look in it on its own.

```
aarch64-linux-gnu-g++-14 -std=c++23 -O3 --static -I/usr/local/include main.cpp -o bilateral
qemu-aarch64 ./bilateral
```

`toolchain/` holds the exact invocations our CI uses - `run_arm.sh`, `run_sve128.sh`,
`run_rvv128.sh` and friends. They take the binary as their argument:

```
sh ../../toolchain/run_sve128.sh ./bilateral
```

## Build an example that carries a test

Some examples end in a `TTS_CASE` and need the test harness on the include path:

```
g++-14 -std=c++23 -O2 -march=native -I ~/test test.cpp -o test && ./test
```
