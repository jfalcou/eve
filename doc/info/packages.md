Package Managers Integration {#packages}
============================

@tableofcontents

If you want to automate your usage of **EVE**, here is a list of package managers that
let you access the library.

## OS-dependent Package Manager
### AUR
**EVE** is available on Arch-Linux via an [**AUR package**](https://aur.archlinux.org/packages/eve-git/).

```bash
$ yay -S eve-git
```

## OS-independent Package Manager
### Conan
[**Conan Center**](https://conan.io/center/) hosts **EVE** as the
[`jfalcou-eve` package](https://conan.io/center/jfalcou-eve).

To use **EVE**, just add `jfalcou-eve/v2021.10.0` in the `[requires]` section of
your `conanfile.txt`

```cmake
[requires]
jfalcou-eve/v2021.10.0

[generators]
cmake
```

### CPM

You can install **EVE** directly via [CPM](https://github.com/cpm-cmake/CPM.cmake). After
[adding CPM to your CMake setup](https://github.com/cpm-cmake/CPM.cmake#adding-cpm), just
add the following commands:

```cmake
include(CPM)

CPMAddPackage(
        NAME eve
        URL https://github.com/jfalcou/eve/archive/refs/tags/v2021.10.0.zip
        VERSION 2021.10.0
        OPTIONS
                "EVE_BUILD_TEST OFF"
                "EVE_BUILD_BENCHMARKS OFF"
                "EVE_BUILD_DOCUMENTATION OFF"
)
```

### SPACK

**EVE** is [**available**](https://spack.readthedocs.io/en/latest/package_list.html#eve
) via [**SPACK**](https://spack.readthedocs.io/en/latest/getting_started.html):

```bash
$ spack install eve
```

Once installed, you can use **EVE** headers directly from your
[**SPACK**](https://spack.readthedocs.io/en/latest/getting_started.html) installation.

### VCPKG

**EVE** can be fetch from [VCPKG](https://vcpkgx.com/details.html?package=eve). Note that, as of
now, we still don't support MSVC.


```bash
$ vcpkg install eve
```
