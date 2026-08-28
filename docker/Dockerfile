##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##
##  A ready-to-use EVE: the compilers, cross-toolchains and emulators our CI runs on, plus EVE
##  itself installed and its examples in place. Built from the commit it ships.
##==================================================================================================
FROM ghcr.io/jfalcou/compilers:v10

## LINKS THE GHCR PACKAGE BACK TO THIS REPOSITORY, WHICH IS WHAT LETS GITHUB_TOKEN PUSH IT
LABEL org.opencontainers.image.source="https://github.com/jfalcou/eve"

## INTEL SDE - RUN AVX-512 AND BEYOND WITHOUT OWNING THE HARDWARE
ARG SDE_VERSION=10.8.0-2026-03-15
ARG SDE_SHA256=50b320cd226acef7a491f5b321fc1be3c3c7984f9e27a456e64894b5b0979dd3

## /opt/sde is emptied first: the base image used to ship its own SDE there, and moving into an existing
## directory would nest this one inside it and go on quietly using the other.
RUN   curl -fsSL "https://downloadmirror.intel.com/915934/sde-external-${SDE_VERSION}-lin.tar.xz" -o /tmp/sde.tar.xz &&  \
      echo "${SDE_SHA256}  /tmp/sde.tar.xz" | sha256sum -c -                                                        &&  \
      rm -rf /opt/sde && mkdir -p /opt/sde                                                                          &&  \
      tar xf /tmp/sde.tar.xz -C /opt/sde --strip-components=1                                                       &&  \
      rm -f /tmp/sde.tar.xz

ENV PATH=/opt/sde:$PATH

RUN   useradd --user-group --create-home --no-log-init --shell /bin/bash eve

## EVE COMES FROM THE BUILD CONTEXT, NOT A CLONE: THE IMAGE IS EXACTLY THE COMMIT THAT BUILT IT
COPY . /src

RUN   cmake -S /src -B /tmp/build -G Ninja                                                                               \
            -DEVE_BUILD_TEST=OFF -DEVE_BUILD_DOCUMENTATION=OFF -DEVE_BUILD_BENCHMARKS=OFF                           &&  \
      cmake --install /tmp/build                                                                                    &&  \
      cp -r /src/examples        /home/eve/examples                                                                 &&  \
      cp -r /src/cmake/toolchain /home/eve/toolchain                                                                &&  \
      mkdir -p /home/eve/test                                                                                       &&  \
      cp -r /src/test/test.hpp /src/test/tts /home/eve/test/                                                        &&  \
      cp /src/docker/README.md /home/eve/README.md                                                                  &&  \
      chown -R eve:eve /home/eve                                                                                    &&  \
      rm -rf /tmp/build /src

## SMOKE TEST
## Fails the build rather than shipping an image where the interesting part does not run. Each of
## the three ways to reach another architecture is exercised once: natively, under SDE, under QEMU.
RUN   cd /home/eve/examples/bilateral                                                                               &&  \
      g++-14 -std=c++23 -O2 -march=native main.cpp -o /tmp/native                                                   &&  \
      /tmp/native --size 512 --iterations 2 > /dev/null                                                             &&  \
      g++-14 -std=c++23 -O2 -march=skylake-avx512 main.cpp -o /tmp/avx512                                           &&  \
      sde64 -skx -- /tmp/avx512 --size 512 --iterations 2 > /dev/null                                               &&  \
      aarch64-linux-gnu-g++-14 -std=c++23 -O2 --static -I/usr/local/include main.cpp -o /tmp/a64                    &&  \
      qemu-aarch64 /tmp/a64 --size 512 --iterations 2 > /dev/null                                                   &&  \
      rm -f /tmp/native /tmp/avx512 /tmp/a64

USER eve
WORKDIR /home/eve
