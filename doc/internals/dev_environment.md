Development Environment {#dev_environment}
=======================

When adding a feature or fixing a bug within **EVE**, you may want to test your code locally over a
non-trivial number of architectures and instruction sets. As you are unlikely to own all the
hardware - or to have every compiler installed - two Docker images are published for that.

| Image                            | What it is                                                                     |
|----------------------------------|--------------------------------------------------------------------------------|
| `ghcr.io/jfalcou/compilers:v10`  | The image our CI runs in: g++ and clang for x86, ARM, AArch64, PowerPC64 and RISC-V, QEMU to execute what you cross-compile, and the Emscripten SDK for WebAssembly. Use it to reproduce a CI job exactly. |
| `ghcr.io/jfalcou/eve:latest`     | The above, plus **EVE** already installed, its examples in place, and Intel SDE. Rebuilt on every push to `main`. Use it to try **EVE** out without building anything. |

Both are built from [their own repository](https://github.com/jfalcou/compilers) and from
`docker/Dockerfile` in this one respectively.

@section dev_docker_setup Docker setup

First step is to install docker on your system. On most Linux, you can find docker in your
usual package manager.

* On Ubuntu using snap:
  @verbatim
  sudo snap install docker
  @endverbatim

* on Arch Linux using pacman
  @verbatim
  sudo pacman -S docker
  @endverbatim

Depending on your system and privilege, you'll need to start the Docker service using the appropriate
command for your operating system.

To check that your docker installation and setup are correct, run:

@verbatim
docker run hello-world
@endverbatim

This command will download a small docker image, run it and display some message that confirms the
proper installation.

@section dev_docker_helper Running EVE docker

Running the CI image over your own **EVE** checkout is done by moving to the **EVE** source folder
then running:

@verbatim
docker run -i -t -v${PWD}:${PWD} ghcr.io/jfalcou/compilers:v10
@endverbatim

This will give you access to an interactive shell running inside the Docker Image. We strongly
advice to make a small Bash function that you can add to your bash profile to easily spin up
an instance of Docker.

@verbatim
# .bashrc
dockhere()
{
  docker run -i -t -v${PWD}:${PWD} ghcr.io/jfalcou/compilers:v10
}
@endverbatim

From there, you can navigate to the source folder by `cd` into your folder:

@verbatim
@:~/space/eve$ pwd                              # From eve directory
/home/dyarosh/space/eve
@:dockhere                                      # Get docker with compilers
root@302ed6f6f4fa:                              # We are in docker in root
root@302ed6f6f4fa:/# cd /home/dyarosh/space/eve # Go back to eve directory
root@302ed6f6f4fa:/home/dyarosh/space/eve#      # Done
@endverbatim

From now on, we make the assumption your Docker instance is running and that you're logged into
its interactive shell.

@section dev_docker_eve Trying EVE without building it

If all you want is to *use* **EVE** - run the examples, see what a kernel compiles to on another
instruction set - the second image needs no checkout at all:

@verbatim
docker run -i -t ghcr.io/jfalcou/eve:latest
@endverbatim

**EVE** is installed, `examples/` holds every example, `toolchain/` holds the very scripts our CI
uses to run a binary under emulation, and its `README.md` lists the commands. Intel SDE is on the
path, so an AVX-512 build runs on any x86:

@verbatim
cd examples/bilateral
g++-14 -std=c++23 -O3 -march=skylake-avx512 main.cpp -o bilateral
sde64 -skx -- ./bilateral
@endverbatim

Next step is [configuring CMake and compiling some tests](@ref dev_cmake)
