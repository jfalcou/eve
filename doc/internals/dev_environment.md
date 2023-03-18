Development Environment {#dev_environment}
=======================

When adding feature or fixing bugs within **EVE**, you may want to locally test your code for a
non-trivial amount of architecture and instructions sets. As you may not have access to all the
compilers or hardware necessary, **EVE** continuous integration and testing environment can be
recreated locally.

**EVE** use a [pre-configured Docker image](https://github.com/jfalcou/compilers) based on Ubuntu
that comes with preinstalled latest versions of g++ and clang  compilers for x86, ARM, AARCH64 and
PowerPC. It is setup so that CI triggers works out of the box but also support manual usage.

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

Running **EVE** CI docker can be done by moving to **EVE** source folder than run the following
command:

@verbatim
docker run -i -t -v${PWD}:${PWD} ghcr.io/jfalcou/compilers:v6
@endverbatim

This will give you access to an interactive shell running inside the Docker Image. We strongly
advice to make a small Bash function that you can add to your bash profile to easily spin up
an instance of Docker.

@verbatim
# .bashrc
dockhere()
{
  docker run -i -t -v${PWD}:${PWD} ghcr.io/jfalcou/compilers:v6
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

Next step is [configuring CMake and compiling some tests](@ref dev_cmake)
