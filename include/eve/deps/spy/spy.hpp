//======================================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#ifndef SPY_SPY_HPP_INCLUDED
#define SPY_SPY_HPP_INCLUDED
//======================================================================================================================
//! @namespace spy
//! @brief Main SPY namespace
//======================================================================================================================
//======================================================================================================================
//! @defgroup api Main API
//! @brief Everything spy reports about the target, the toolchain and the flags it was given
//!
//! Every axis spy detects is a `constexpr` object living in namespace `spy`, so a question the
//! preprocessor used to answer becomes a value any `constexpr` context can read. The six groups
//! below sort those values by the question they answer.
//!
//! A value is read in three ways, shown here on the compiler:
//!
//! @code{.cpp}
//! // compared to a named value
//! if constexpr(spy::compiler == spy::gcc_) { }
//!
//! // or the named value itself, which converts to bool
//! if constexpr(spy::gcc_) { }
//!
//! // and any of them prints
//! std::cout << spy::compiler;
//! @endcode
//!
//! Versions are named by a user-defined literal per vendor, gathered in `spy::literal`, and the
//! ordering operators compare against them:
//!
//! @code{.cpp}
//! using namespace spy::literal;
//! if constexpr(spy::compiler >= 15'0_clang) { } // clang 15 or later
//! @endcode
//!
//! Two different vendors compare as `std::partial_ordering::unordered` rather than as `false`, so
//! `spy::gcc_ < spy::clang_` has no answer instead of a wrong one.
//!
//! Capabilities that are not an axis of their own live in `spy::supports`, each a plain
//! `constexpr inline bool`.
//!
//! @{
//!   @defgroup spy_platform Target Platforms
//!   @brief The system, the processor and the data model the code is compiled for
//!
//!   Where the code will run. `spy::operating_system` names the system and
//!   `spy::supports::posix_` says whether it offers a POSIX interface, `spy::architecture` names
//!   the processor family, and `spy::data_model` gives the sizes the ABI hands the fundamental
//!   types, which the system and the architecture decide together.
//!
//!   @defgroup spy_compiler Compilers
//!   @brief The compiler processing the code, and the literals naming its versions
//!
//!   `spy::compiler` reports the toolchain as itself: a compiler that imitates another still
//!   answers with its own name. The literals gathered here name a version to compare it against.
//!
//!   @defgroup spy_standards Language Standards
//!   @brief The C++ standard in force, and the C and C++ standard library implementations
//!
//!   What the code is allowed to say and what it can call: the standard the compiler was told to
//!   follow, and the two library implementations behind the headers it includes.
//!
//!   @defgroup spy_isa Instruction Sets
//!   @brief The SIMD extensions the flags turn on, and what they can compute
//!
//!   `spy::simd_instruction_set` names the extension the flags enabled and the width of its
//!   registers, and the `spy::supports::fp16` indicators say what that unit does with
//!   half-precision, which the same architecture macros decide.
//!   @{
//!     @defgroup spy_isa_supplemental Supplemental Instruction Sets
//!     @brief The instructions some extensions add on top of an existing set
//!
//!     One indicator per supplemental set, `true` when the flags turned it on. The AVX family
//!     adds FMA3, FMA4, XOP and F16C, and the AVX-512 subsets live in their own namespace.
//!   @}
//!
//!   @defgroup spy_accelerator Accelerators
//!   @brief The accelerator programming models the code is compiled with
//!
//!   These report how the current translation unit is being compiled, not what the machine
//!   holds: they are true when the compiler was asked for CUDA or for SYCL, whatever device is
//!   present.
//!
//!   @defgroup spy_sanitizers Sanitizers
//!   @brief The sanitizers the code is compiled with
//!
//!   Whether the current translation unit carries the instrumentation of the address or the
//!   thread sanitizer, so that code which the instrumentation would slow down or trip can step
//!   aside at compile time.
//! @}
//======================================================================================================================
//======================================================================================================================
//! @namespace spy::supports
//! @brief Support detection SPY namespace
//======================================================================================================================
//======================================================================================================================
//! @namespace spy::literal
//! @brief SPY User-defined literal namespace
//======================================================================================================================
#if defined(_MSC_VER)
#if _MSVC_LANG < 202002L
#error "SPY C++ version error"
#include "SPY requires C++20 or higher. Use /std:c++20 or higher to enable C++20 features."
#endif
#else
#if __cplusplus < 202002L
#error "SPY C++ version error"
#include "SPY requires C++20 or higher. Use -std=c++20 or higher to enable C++20 features."
#endif
#endif
#include <compare>
namespace spy::_
{
  template<typename T>
  concept stream = requires(T& os, char c) {
    { os.copyfmt(os) };
    { os.flush() };
    { os.put(c) };
  };
  template<char... c> constexpr int find(int i0)
  {
    int  sz    = sizeof...(c);
    char arr[] = {c...};
    while(i0 < sz && arr[ i0 ] != '\'') ++i0;
    return i0;
  }
  template<char... c> constexpr int parse(int i0, int i1)
  {
    char arr[] = {c...};
    int  value = 0;
    while(i0 < i1 && arr[ i0 ] != '\'') value = value * 10 + (arr[ i0++ ] - 48);
    return value;
  }
  template<template<int, int, int> class Wrapper, char... c> constexpr auto literal_wrap()
  {
    constexpr int b0 = 0;
    constexpr int e0 = find<c...>(0);
    constexpr int b1 = e0 + 1;
    constexpr int e1 = find<c...>(b1);
    constexpr int b2 = e1 + 1;
    constexpr int e2 = sizeof...(c);
    return Wrapper<parse<c...>(b0, e0), parse<c...>(b1, e1), parse<c...>(b2, e2)> {};
  }
  template<int M, int N, int P> struct version_id
  {
    static constexpr int major = M;
    static constexpr int minor = N;
    static constexpr int patch = P;
    template<int M2, int N2, int P2>
    friend constexpr bool operator==(version_id, version_id<M2, N2, P2>) noexcept
    {
      return (M == M2) && (N == N2) && (P == P2);
    }
    template<int M2, int N2, int P2>
    friend constexpr std::strong_ordering operator<=>(version_id, version_id<M2, N2, P2>) noexcept
    {
      if constexpr(constexpr auto cmp0 = M <=> M2; cmp0 != 0) return cmp0;
      else if constexpr(constexpr auto cmp1 = N <=> N2; cmp1 != 0) return cmp1;
      else return P <=> P2;
    }
    template<_::stream OS> friend auto& operator<<(OS& os, version_id const&)
    {
      if constexpr(M == -1 && N == 0 && P == 0) return os << "(unspecified)";
      else return os << "v" << M << "." << N << "." << P;
    }
  };
  using unspecified_version_t                                = version_id<-1, 0, 0>;
  constexpr inline unspecified_version_t unspecified_version = {};
}
namespace spy::supports
{
  template<int M, int N, int P> struct sycl_t
  {
    explicit constexpr                  operator bool() const noexcept { return M > 0 && N > 0; }
    template<_::stream OS> friend auto& operator<<(OS& os, sycl_t)
    {
      os << "SYCL v" << M << '.' << N;
      if(P > 0) os << '.' << P;
      return os;
    }
    template<int M1, int N1, int P1>
    constexpr bool operator==(sycl_t<M1, N1, P1> const&) const noexcept
    {
      return M == M1 && N == N1 && P == P1;
    }
  };
  template<int M, int N, int P> struct cuda_t
  {
    explicit constexpr operator bool() const noexcept { return M > 0 && N > 0; }
    template<int M1, int N1, int P1>
    constexpr bool operator==(cuda_t<M1, N1, P1> const&) const noexcept
    {
      return M == M1 && N == N1 && P == P1;
    }
    template<_::stream OS> friend auto& operator<<(OS& os, cuda_t)
    {
#if defined(__NVCC__)
      os << "NVCC ";
#elif defined(__clang__)
      os << "Clang ";
#endif
      os << "CUDA v" << M << '.' << N;
      if(P > 0) os << '.' << P;
      return os;
    }
  };
#if defined(SYCL_LANGUAGE_VERSION) && defined(__INTEL_LLVM_COMPILER)
#define SPY_ACCELERATOR_SUPPORTS_SYCL
  constexpr inline auto sycl =
      sycl_t<SYCL_LANGUAGE_VERSION / 100, SYCL_LANGUAGE_VERSION % 100, 0> {};
#elif defined(SPY_DOXYGEN_INVOKED)
  constexpr inline auto sycl = _::implementation_defined {};
#else
  constexpr inline auto sycl = sycl_t<-1, -1, -1> {};
#endif
#if defined(__CUDACC__)
#if defined(__CUDACC_VER_MAJOR__)
#define SPY_ACCELERATOR_SUPPORTS_CUDA
  constexpr inline auto cuda = cuda_t<__CUDACC_VER_MAJOR__, __CUDACC_VER_MINOR__, 0> {};
#elif defined(CUDA_VERSION)
#define SPY_ACCELERATOR_SUPPORTS_CUDA
  constexpr inline auto cuda =
      cuda_t<CUDA_VERSION / 1000, (CUDA_VERSION % 1000) / 10, CUDA_VERSION % 10> {};
#endif
#elif defined(SPY_DOXYGEN_INVOKED)
  constexpr inline auto cuda = _::implementation_defined {};
#else
  constexpr inline auto cuda = cuda_t<-1, -1, -1> {};
#endif
}
namespace spy::_
{
  enum class archs
  {
    undefined_ = -1,
    x86_       = 10,
    amd64_     = 11,
    ppc_       = 20,
    arm_       = 30,
    wasm_      = 40,
    riscv_     = 50
  };
  template<archs Arch> struct arch_info
  {
    static constexpr archs            vendor = Arch;
    constexpr explicit                operator bool() const noexcept;
    template<archs A2> constexpr bool operator==(arch_info<A2> const&) const noexcept
    {
      return A2 == vendor;
    }
    template<_::stream OS> friend auto& operator<<(OS& os, arch_info const&)
    {
      using enum archs;
      if(Arch == x86_) return os << "X86";
      if(Arch == amd64_) return os << "AMD64";
      if(Arch == ppc_) return os << "PowerPC";
      if(Arch == arm_) return os << "ARM";
      if(Arch == wasm_) return os << "WebAssembly";
      if(Arch == riscv_) return os << "RISC-V";
      return os << "Undefined Architecture";
    }
  };
}
namespace spy
{
#if defined(i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) ||                \
    defined(__i686__) || defined(__i386) || defined(_M_IX86) || defined(_X86_) ||                  \
    defined(__THW_INTEL__) || defined(__I86__) || defined(__INTEL__)
  using arch_type = _::arch_info<_::archs::x86_>;
#define SPY_ARCH_IS_X86
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64__) || defined(__amd64) ||        \
    defined(_M_X64)
#define SPY_ARCH_IS_AMD64
  using arch_type = _::arch_info<_::archs::amd64_>;
#elif defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) || defined(__ppc__) ||    \
    defined(_M_PPC) || defined(_ARCH_PPC) || defined(__PPCGECKO__) || defined(__PPCBROADWAY__) ||  \
    defined(_XENON)
  using arch_type = _::arch_info<_::archs::ppc_>;
#define SPY_ARCH_IS_PPC
#elif defined(__arm__) || defined(__arm64) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) ||  \
    defined(__TARGET_ARCH_THUMB) || defined(_M_ARM) || defined(__ARM_ARCH_ISA_A64)
  using arch_type = _::arch_info<_::archs::arm_>;
#define SPY_ARCH_IS_ARM
#elif defined(__wasm__)
  using arch_type = _::arch_info<_::archs::wasm_>;
#define SPY_ARCH_IS_WASM
#elif defined(__riscv)
  using arch_type = _::arch_info<_::archs::riscv_>;
#define SPY_ARCH_IS_RISCV
#else
#define SPY_ARCH_IS_UNKNOWN
  using arch_type = _::arch_info<_::archs::undefined_>;
#endif
  constexpr inline arch_type architecture;
}
namespace spy::_
{
  template<archs Arch> constexpr arch_info<Arch>::operator bool() const noexcept
  {
    return spy::architecture == *this;
  }
}
namespace spy
{
  constexpr inline auto x86_   = _::arch_info<_::archs::x86_> {};
  constexpr inline auto amd64_ = _::arch_info<_::archs::amd64_> {};
  constexpr inline auto ppc_   = _::arch_info<_::archs::ppc_> {};
  constexpr inline auto arm_   = _::arch_info<_::archs::arm_> {};
  constexpr inline auto wasm_  = _::arch_info<_::archs::wasm_> {};
  constexpr inline auto riscv_ = _::arch_info<_::archs::riscv_> {};
}
#include <compare>
#if defined __has_include
#if __has_include(<emscripten/version.h>)
#include <emscripten/version.h>
#endif
#endif
namespace spy::_
{
  enum class compilers
  {
    undefined_ = -1,
    msvc_,
    intel_,
    clang_,
    gcc_,
    emscripten_,
    dpcpp_,
    nvcc_,
    clangcl_,
    mingw32_,
    mingw64_
  };
  template<compilers Compiler, int M, int N, int P> struct compilers_info
  {
    static constexpr compilers           vendor  = Compiler;
    static constexpr version_id<M, N, P> version = {};
    constexpr explicit                   operator bool() const noexcept;
    template<compilers C2>
    constexpr bool operator==(compilers_info<C2, -1, 0, 0> const&) const noexcept
    {
      return C2 == vendor;
    }
    template<compilers C2, int M2, int N2, int P2>
    constexpr bool operator==(compilers_info<C2, M2, N2, P2> const& c2) const noexcept
    {
      return C2 == vendor && version == c2.version;
    }
    template<compilers C2, int M2, int N2, int P2>
    constexpr std::partial_ordering
    operator<=>(compilers_info<C2, M2, N2, P2> const& c2) const noexcept
    {
      if constexpr(vendor == C2) return version <=> c2.version;
      else return std::partial_ordering::unordered;
    }
    template<_::stream OS> friend auto& operator<<(OS& os, compilers_info const&)
    {
      using enum compilers;
      if(Compiler == nvcc_) return os << "NVIDIA CUDA Compiler " << version;
      if(Compiler == msvc_) return os << "Microsoft Visual Studio " << version;
      if(Compiler == intel_) return os << "Intel(R) C++ Compiler " << version;
      if(Compiler == dpcpp_) return os << "Intel(R) oneAPI DPC++/C++ Compiler " << version;
      if(Compiler == clang_) return os << "clang " << version;
      if(Compiler == gcc_) return os << "g++ " << version;
      if(Compiler == emscripten_) return os << "Emscripten " << version;
      if(Compiler == clangcl_) return os << "Clang with MSVC-like command-line" << version;
      if(Compiler == mingw32_) return os << "MINGW32 g++ " << version;
      if(Compiler == mingw64_) return os << "MINGW64 g++ " << version;
      return os << "Undefined " << version;
    }
  };
  template<int M, int N, int P> using msvc_t    = compilers_info<compilers::msvc_, M, N, P>;
  template<int M, int N, int P> using intel_t   = compilers_info<compilers::intel_, M, N, P>;
  template<int M, int N, int P> using dpcpp_t   = compilers_info<compilers::dpcpp_, M, N, P>;
  template<int M, int N, int P> using nvcc_t    = compilers_info<compilers::nvcc_, M, N, P>;
  template<int M, int N, int P> using clang_t   = compilers_info<compilers::clang_, M, N, P>;
  template<int M, int N, int P> using gcc_t     = compilers_info<compilers::gcc_, M, N, P>;
  template<int M, int N, int P> using clangcl_t = compilers_info<compilers::clangcl_, M, N, P>;
  template<int M, int N, int P> using mingw32_t = compilers_info<compilers::mingw32_, M, N, P>;
  template<int M, int N, int P> using mingw64_t = compilers_info<compilers::mingw64_, M, N, P>;
  template<int M, int N, int P>
  using emscripten_t = compilers_info<compilers::emscripten_, M, N, P>;
}
namespace spy
{
#if defined(__NVCC__)
#define SPY_COMPILER_IS_NVCC
  using compiler_type = _::nvcc_t<__CUDACC_VER_MAJOR__, __CUDACC_VER_MINOR__, 0>;
#elif defined(_MSC_VER) && !defined(__clang__)
#define SPY_COMPILER_IS_MSVC
  using compiler_type = _::msvc_t<_MSC_VER / 100, _MSC_VER % 100, _MSC_FULL_VER % 100000>;
#elif defined(__MINGW32__) && !defined(__MINGW64__)
#define SPY_COMPILER_IS_MINGW32
  using compiler_type = _::mingw32_t<__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__>;
#elif defined(__MINGW32__) && defined(__MINGW64__)
#define SPY_COMPILER_IS_MINGW64
  using compiler_type = _::mingw64_t<__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__>;
#elif defined(_MSC_VER) && defined(__clang__)
#define SPY_COMPILER_IS_CLANGCL
  using compiler_type = _::clangcl_t<__clang_major__, __clang_minor__, __clang_patchlevel__>;
#elif defined(__INTEL_LLVM_COMPILER)
#define SPY_COMPILER_IS_INTEL_DPCPP
#define SPY0 __INTEL_LLVM_COMPILER
  using compiler_type = _::dpcpp_t<SPY0 / 10000, (SPY0 / 100) % 100, SPY0 % 100>;
#undef SPY0
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
#define SPY_COMPILER_IS_INTEL
#define SPY0 __INTEL_COMPILER
  using compiler_type = _::intel_t<(SPY0 / 100) % 100, SPY0 % 100, __INTEL_COMPILER_UPDATE>;
#undef SPY0
#elif defined(__EMSCRIPTEN__)
#define SPY_COMPILER_IS_CLANG
#if defined(__EMSCRIPTEN_MAJOR__)
  using compiler_type =
      _::emscripten_t<__EMSCRIPTEN_MAJOR__, __EMSCRIPTEN_MINOR__, __EMSCRIPTEN_TINY__>;
#else
  using compiler_type =
      _::emscripten_t<__EMSCRIPTEN_major__, __EMSCRIPTEN_minor__, __EMSCRIPTEN_tiny__>;
#endif
#undef SPY0
#elif defined(__clang__)
#define SPY_COMPILER_IS_CLANG
  using compiler_type = _::clang_t<__clang_major__, __clang_minor__, __clang_patchlevel__>;
#elif defined(__GNUC__)
#define SPY_COMPILER_IS_GCC
  using compiler_type = _::gcc_t<__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__>;
#else
#define SPY_COMPILER_IS_UNKNOWN
  using compiler_type = _::compilers_info<compilers::undefined_, -1, 0, 0>;
#endif
  constexpr inline compiler_type compiler;
}
namespace spy::_
{
  template<compilers C, int M, int N, int P>
  constexpr compilers_info<C, M, N, P>::operator bool() const noexcept
  {
    return spy::compiler == *this;
  }
}
namespace spy
{
  constexpr inline auto nvcc_       = _::nvcc_t<-1, 0, 0> {};
  constexpr inline auto msvc_       = _::msvc_t<-1, 0, 0> {};
  constexpr inline auto intel_      = _::intel_t<-1, 0, 0> {};
  constexpr inline auto dpcpp_      = _::dpcpp_t<-1, 0, 0> {};
  constexpr inline auto clang_      = _::clang_t<-1, 0, 0> {};
  constexpr inline auto gcc_        = _::gcc_t<-1, 0, 0> {};
  constexpr inline auto emscripten_ = _::emscripten_t<-1, 0, 0> {};
  constexpr inline auto clangcl_    = _::clangcl_t<-1, 0, 0> {};
  constexpr inline auto mingw32_    = _::mingw32_t<-1, 0, 0> {};
  constexpr inline auto mingw64_    = _::mingw64_t<-1, 0, 0> {};
}
namespace spy::literal
{
  template<char... c> consteval auto operator""_nvcc()
  {
    return _::literal_wrap<_::nvcc_t, c...>();
  }
  template<char... c> consteval auto operator""_msvc()
  {
    return _::literal_wrap<_::msvc_t, c...>();
  }
  template<char... c> consteval auto operator""_mingw32()
  {
    return _::literal_wrap<_::mingw32_t, c...>();
  }
  template<char... c> consteval auto operator""_mingw64()
  {
    return _::literal_wrap<_::mingw64_t, c...>();
  }
  template<char... c> consteval auto operator""_intel()
  {
    return _::literal_wrap<_::intel_t, c...>();
  }
  template<char... c> consteval auto operator""_dpcpp()
  {
    return _::literal_wrap<_::dpcpp_t, c...>();
  }
  template<char... c> consteval auto operator""_clang()
  {
    return _::literal_wrap<_::clang_t, c...>();
  }
  template<char... c> consteval auto operator""_gcc() { return _::literal_wrap<_::gcc_t, c...>(); }
  template<char... c> consteval auto operator""_em()
  {
    return _::literal_wrap<_::emscripten_t, c...>();
  }
  template<char... c> consteval auto operator""_clangcl()
  {
    return _::literal_wrap<_::clangcl_t, c...>();
  }
}
namespace spy::_
{
  template<int Short, int Integer, int Long, int Pointer> struct data_model_info
  {
    constexpr explicit operator bool() const noexcept;
    template<int Short2, int Integer2, int Long2, int Pointer2>
    constexpr bool
    operator==(data_model_info<Short2, Integer2, Long2, Pointer2> const&) const noexcept
    {
      return (Short == Short2) && (Integer == Integer2) && (Long == Long2) && (Pointer == Pointer2);
    }
    template<_::stream OS> friend auto& operator<<(OS& os, data_model_info const&)
    {
      if constexpr(Pointer == 4 && Integer == 4) return os << "ILP32";
      else if constexpr(Pointer == 4 && Integer == 2) return os << "LP32";
      else if constexpr(Pointer == 8 && Long == 8 && Integer == 8 && Short == 8)
        return os << "IntegerLP64";
      else if constexpr(Pointer == 8 && Short == 8 && Integer == 8 && Short == 2)
        return os << "ILP64";
      else if constexpr(Pointer == 8 && Long == 4 && Integer == 8 && Short == 2)
        return os << "LLP64";
      else if constexpr(Pointer == 8 && Long == 8 && Integer == 4 && Short == 2)
        return os << "LP64";
      else return os << "Unknown data model";
    }
  };
}
namespace spy
{
  using data_model_type =
      _::data_model_info<sizeof(short), sizeof(int), sizeof(long), sizeof(void*)>;
  constexpr inline auto data_model = data_model_type {};
}
namespace spy::_
{
  template<int Short, int Integer, int Long, int Pointer>
  constexpr data_model_info<Short, Integer, Long, Pointer>::operator bool() const noexcept
  {
    return spy::data_model == *this;
  }
}
namespace spy
{
  constexpr inline auto ilp32_  = _::data_model_info<2, 4, sizeof(long), 4> {};
  constexpr inline auto lp32_   = _::data_model_info<2, 2, sizeof(long), 4> {};
  constexpr inline auto silp64_ = _::data_model_info<8, 8, 8, 8> {};
  constexpr inline auto ilp64_  = _::data_model_info<2, 8, 8, 8> {};
  constexpr inline auto llp64_  = _::data_model_info<2, 8, 4, 8> {};
  constexpr inline auto lp64_   = _::data_model_info<2, 4, 8, 8> {};
}
#include <compare>
#include <cstddef>
namespace spy::_
{
  enum class libC
  {
    undefined_ = -1,
    cloudabi_,
    uc_,
    vms_,
    zos_,
    gnu_
  };
  template<libC Lib, int M, int N, int P> struct libc_info
  {
    static constexpr libC                vendor  = Lib;
    static constexpr version_id<M, N, P> version = {};
    constexpr explicit                   operator bool() const noexcept;
    template<libC C2> constexpr bool     operator==(libc_info<C2, -1, 0, 0> const&) const noexcept
    {
      return C2 == vendor;
    }
    template<libC C2, int M2, int N2, int P2>
    constexpr bool operator==(libc_info<C2, M2, N2, P2> const& c2) const noexcept
    {
      return C2 == vendor && version == c2.version;
    }
    template<libC C2, int M2, int N2, int P2>
    constexpr auto operator<=>(libc_info<C2, M2, N2, P2> const& c2) const noexcept
    {
      if constexpr(vendor == C2) return version <=> c2.version;
      else return vendor <=> C2;
    }
    template<_::stream OS> friend auto& operator<<(OS& os, libc_info const&)
    {
      using enum libC;
      if(vendor == cloudabi_) return os << "CloudABI Standard C Library " << version;
      if(vendor == uc_) return os << "uClibc Standard C Library " << version;
      if(vendor == vms_) return os << "VMS Standard C Library " << version;
      if(vendor == zos_) return os << "z/OS Standard C Library " << version;
      if(vendor == gnu_) return os << "GNU Standard C Library " << version;
      return os << "Undefined Standard C Library";
    }
  };
  template<int M, int N, int P> using cloudabi_t = libc_info<libC::cloudabi_, M, N, P>;
  template<int M, int N, int P> using uc_t       = libc_info<libC::uc_, M, N, P>;
  template<int M, int N, int P> using vms_t      = libc_info<libC::vms_, M, N, P>;
  template<int M, int N, int P> using zos_t      = libc_info<libC::zos_, M, N, P>;
  template<int M, int N, int P> using gnu_t      = libc_info<libC::gnu_, M, N, P>;
}
namespace spy
{
#if defined(__cloudlibc__)
#define SPY_LIBC_IS_CLOUDABI
  using libc_type = _::cloudabi_t<__cloudlibc_major__, __cloudlibc_minor__, 0>;
#elif defined(__GLIBC__)
#define SPY_LIBC_IS_GNU
  using libc_type = _::gnu_t<__GLIBC__, __GLIBC_MINOR__, 0>;
#elif defined(__GNU_LIBRARY__)
#define SPY_LIBC_IS_GNU
  using libc_type = _::gnu_t<__GNU_LIBRARY__, __GNU_LIBRARY_MINOR__, 0>;
#elif defined(__UCLIBC__)
#define SPY_LIBC_IS_UCLIBC
  using libc_type = _::uc_t<__UCLIBC_MAJOR__, __UCLIBC_MINOR__, __UCLIBC_SUBLEVEL__>;
#elif defined(__CRTL_VER)
#define SPY_LIBC_IS_VMS
#define SPY0 (__CRTL_VER / 100)
  using libc_type = _::vms_t<(SPY0 / 100000) % 100, (SPY0 / 1000) % 100, (SPY0) % 100>;
#undef SPY0
#elif defined(__LIBREL__)
#define SPY_LIBC_IS_ZOS
  using libc_type = _::zos_t < (__LIBREL__ & 0xF000000) >> 24, (__LIBREL__ & 0xFF0000) >> 16,
        (__LIBREL__ & 0xFFFF) > ;
#else
#define SPY_LIBC_IS_UNKNOWN
  using libc_type = _::libc_info<_::libC::undefined_, -1, 0, 0>;
#endif
  constexpr inline auto libc = libc_type {};
}
namespace spy::_
{
  template<libC C, int M, int N, int P>
  constexpr libc_info<C, M, N, P>::operator bool() const noexcept
  {
    return spy::libc == *this;
  }
}
namespace spy
{
  constexpr inline auto cloudabi_ = _::cloudabi_t<-1, 0, 0> {};
  constexpr inline auto uc_       = _::uc_t<-1, 0, 0> {};
  constexpr inline auto vms_      = _::vms_t<-1, 0, 0> {};
  constexpr inline auto zos_      = _::zos_t<-1, 0, 0> {};
  constexpr inline auto gnu_      = _::gnu_t<-1, 0, 0> {};
}
namespace spy::literal
{
  template<char... c> consteval auto operator""_cloud()
  {
    return _::literal_wrap<_::cloudabi_t, c...>();
  }
  template<char... c> consteval auto operator""_uc() { return _::literal_wrap<_::uc_t, c...>(); }
  template<char... c> consteval auto operator""_vms() { return _::literal_wrap<_::vms_t, c...>(); }
  template<char... c> consteval auto operator""_zos() { return _::literal_wrap<_::zos_t, c...>(); }
  template<char... c> consteval auto operator""_gnu() { return _::literal_wrap<_::gnu_t, c...>(); }
}
#if defined(__APPLE__) || defined(__APPLE_CC__) || defined(macintosh)
#include <AvailabilityMacros.h>
#endif
namespace spy::_
{
  enum class systems
  {
    undefined_ = -1,
    android_,
    bsd_,
    cygwin_,
    ios_,
    linux_,
    macos_,
    unix_,
    windows_
  };
  template<systems OpSys> struct os_info
  {
    static constexpr systems            vendor = OpSys;
    constexpr explicit                  operator bool() const noexcept;
    template<systems C2> constexpr bool operator==(os_info<C2> const&) const noexcept
    {
      return C2 == vendor;
    }
    template<_::stream OS> friend auto& operator<<(OS& os, os_info const&)
    {
      using enum systems;
      if(OpSys == android_) return os << "Android";
      if(OpSys == bsd_) return os << "BSD";
      if(OpSys == cygwin_) return os << "Cygwin";
      if(OpSys == ios_) return os << "iOs";
      if(OpSys == linux_) return os << "Linux";
      if(OpSys == macos_) return os << "MacOs";
      if(OpSys == unix_) return os << "UNIX";
      if(OpSys == windows_) return os << "Windows";
      return os << "Undefined Operating System";
    }
  };
}
namespace spy
{
#if defined(__ANDROID__)
#define SPY_OS_IS_ANDROID
  using os_type = _::os_info<_::systems::android_>;
#elif defined(BSD) || defined(_SYSTYPE_BSD)
#define SPY_OS_IS_BSD
  using os_type = _::os_info<_::systems::bsd_>;
#elif defined(__CYGWIN__)
#define SPY_OS_IS_CYGWIN
  using os_type = _::os_info<_::systems::cygwin_>;
#elif defined(__APPLE__) && defined(__MACH__) &&                                                   \
    defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
#define SPY_OS_IS_IOS
  using os_type = _::os_info<_::systems::ios_>;
#elif defined(linux) || defined(__linux)
#define SPY_OS_IS_LINUX
  using os_type = _::os_info<_::systems::linux_>;
#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
#define SPY_OS_IS_MACOS
  using os_type = _::os_info<_::systems::macos_>;
#elif defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
#define SPY_OS_IS_UNIX
  using os_type = _::os_info<_::systems::unix_>;
#elif defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) ||          \
    defined(__WINDOWS__)
#define SPY_OS_IS_WINDOWS
  using os_type = _::os_info<_::systems::windows_>;
#else
#define SPY_OS_IS_UNKNOWN
  using os_type = _::os_info<_::systems::undefined_>;
#endif
  constexpr inline os_type operating_system;
}
namespace spy::_
{
  template<systems OS> constexpr os_info<OS>::operator bool() const noexcept
  {
    return spy::operating_system == *this;
  }
}
namespace spy
{
  constexpr inline auto android_ = _::os_info<_::systems::android_> {};
  constexpr inline auto bsd_     = _::os_info<_::systems::bsd_> {};
  constexpr inline auto cygwin_  = _::os_info<_::systems::cygwin_> {};
  constexpr inline auto ios_     = _::os_info<_::systems::ios_> {};
  constexpr inline auto linux_   = _::os_info<_::systems::linux_> {};
  constexpr inline auto macos_   = _::os_info<_::systems::macos_> {};
  constexpr inline auto unix_    = _::os_info<_::systems::unix_> {};
  constexpr inline auto windows_ = _::os_info<_::systems::windows_> {};
}
namespace spy::supports
{
#if defined(SPY_DOXYGEN_INVOKED)
  constexpr inline auto posix_ = _::implementation_defined {};
#else
#if (MAC_OS_X_VERSION_MIN_REQUIRED >= 1090) || (_POSIX_C_SOURCE >= 200112L) ||                     \
    (_XOPEN_SOURCE >= 600)
#define SPY_SUPPORTS_POSIX
  constexpr inline auto posix_ = true;
#else
  constexpr inline auto posix_ = false;
#endif
#endif
}
#if defined(__has_feature)
#if __has_feature(address_sanitizer)
#define SPY_ADDRESS_SANITIZERS_ENABLED
#endif
#if __has_feature(thread_sanitizer)
#define SPY_THREAD_SANITIZERS_ENABLED
#endif
#endif
#if !defined(SPY_ADDRESS_SANITIZERS_ENABLED)
#if defined(__SANITIZE_ADDRESS__)
#define SPY_ADDRESS_SANITIZERS_ENABLED
#endif
#endif
#if !defined(SPY_THREAD_SANITIZERS_ENABLED)
#if defined(__SANITIZE_THREAD__)
#define SPY_THREAD_SANITIZERS_ENABLED
#endif
#endif
namespace spy::supports
{
#if defined(SPY_ADDRESS_SANITIZERS_ENABLED)
  constexpr inline bool address_sanitizers_status = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  constexpr inline bool address_sanitizers_status = _::implementation_defined {};
#else
  constexpr inline bool address_sanitizers_status = false;
#endif
#if defined(SPY_THREAD_SANITIZERS_ENABLED)
  constexpr inline bool thread_sanitizers_status = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  constexpr inline bool thread_sanitizers_status = _::implementation_defined {};
#else
  constexpr inline bool thread_sanitizers_status = false;
#endif
  constexpr inline bool sanitizers_status = address_sanitizers_status || thread_sanitizers_status;
}
#if defined(SPY_COMPILER_IS_MSVC)
#define SPY_DISABLE_ADDRESS_SANITIZERS __declspec(no_sanitize_address)
#define SPY_DISABLE_THREAD_SANITIZERS
#define SPY_DISABLE_SANITIZERS __declspec(no_sanitize_address)
#elif defined(SPY_DOXYGEN_INVOKED)
#define SPY_DISABLE_ADDRESS_SANITIZERS _::implementation_defined
#define SPY_DISABLE_THREAD_SANITIZERS  _::implementation_defined
#define SPY_DISABLE_SANITIZERS         _::implementation_defined
#else
#if defined(__has_attribute)
#if __has_attribute(no_sanitize_address)
#define SPY_DISABLE_ADDRESS_SANITIZERS __attribute__((no_sanitize_address))
#endif
#if __has_attribute(no_sanitize_thread)
#define SPY_DISABLE_THREAD_SANITIZERS __attribute__((no_sanitize_thread))
#endif
#if __has_attribute(no_sanitize)
#define SPY_DISABLE_SANITIZERS __attribute__((no_sanitize("address", "thread")))
#endif
#endif
#if !defined(SPY_DISABLE_ADDRESS_SANITIZERS)
#define SPY_DISABLE_ADDRESS_SANITIZERS
#endif
#if !defined(SPY_DISABLE_THREAD_SANITIZERS)
#define SPY_DISABLE_THREAD_SANITIZERS
#endif
#if !defined(SPY_DISABLE_SANITIZERS)
#define SPY_DISABLE_SANITIZERS SPY_DISABLE_ADDRESS_SANITIZERS SPY_DISABLE_THREAD_SANITIZERS
#endif
#endif
#if defined(__ARM_FEATURE_SVE2)
#if !defined(__ARM_FEATURE_SVE_BITS) || (__ARM_FEATURE_SVE_BITS == 0)
#define SPY_SIMD_IS_ARM_FLEXIBLE_SVE2
#define SPY_SIMD_DETECTED ::spy::_::simd_version::sve2_
#elif defined(__ARM_FEATURE_SVE_BITS)
#if (__ARM_FEATURE_SVE_BITS == 128)
#define SPY_SIMD_IS_ARM_FIXED_SVE2
#define SPY_SIMD_DETECTED ::spy::_::simd_version::fixed_sve2_
#elif (__ARM_FEATURE_SVE_BITS == 256)
#define SPY_SIMD_IS_ARM_FIXED_SVE2
#define SPY_SIMD_DETECTED ::spy::_::simd_version::fixed_sve2_
#elif (__ARM_FEATURE_SVE_BITS == 512)
#define SPY_SIMD_IS_ARM_FIXED_SVE2
#define SPY_SIMD_DETECTED ::spy::_::simd_version::fixed_sve2_
#elif (__ARM_FEATURE_SVE_BITS == 1024)
#define SPY_SIMD_IS_ARM_FIXED_SVE2
#define SPY_SIMD_DETECTED ::spy::_::simd_version::fixed_sve2_
#else
#error "[SPY] - No support for non-power of 2 SVE-2 cardinals"
#endif
#endif
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__ARM_FEATURE_SVE)
#if !defined(__ARM_FEATURE_SVE_BITS) || (__ARM_FEATURE_SVE_BITS == 0)
#define SPY_SIMD_IS_ARM_FLEXIBLE_SVE
#define SPY_SIMD_DETECTED ::spy::_::simd_version::sve_
#elif defined(__ARM_FEATURE_SVE_BITS)
#if (__ARM_FEATURE_SVE_BITS == 128)
#define SPY_SIMD_IS_ARM_FIXED_SVE
#define SPY_SIMD_DETECTED ::spy::_::simd_version::fixed_sve_
#elif (__ARM_FEATURE_SVE_BITS == 256)
#define SPY_SIMD_IS_ARM_FIXED_SVE
#define SPY_SIMD_DETECTED ::spy::_::simd_version::fixed_sve_
#elif (__ARM_FEATURE_SVE_BITS == 512)
#define SPY_SIMD_IS_ARM_FIXED_SVE
#define SPY_SIMD_DETECTED ::spy::_::simd_version::fixed_sve_
#elif (__ARM_FEATURE_SVE_BITS == 1024)
#define SPY_SIMD_IS_ARM_FIXED_SVE
#define SPY_SIMD_DETECTED ::spy::_::simd_version::fixed_sve_
#else
#error "[SPY] - No support for non-power of 2 SVE cardinals"
#endif
#endif
#endif
#if defined(__ARM_FEATURE_SVE2)
#define SPY_SIMD_IS_ARM_SVE2
#define SPY_SIMD_VENDOR ::spy::_::simd_isa::arm_sve_
#elif defined(__ARM_FEATURE_SVE)
#define SPY_SIMD_IS_ARM_SVE
#define SPY_SIMD_VENDOR ::spy::_::simd_isa::arm_sve_
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__aarch64__)
#define SPY_SIMD_IS_ARM_ASIMD
#define SPY_SIMD_DETECTED ::spy::_::simd_version::asimd_
#endif
#if !defined(SPY_SIMD_DETECTED) && ((defined(__ARM_NEON__) || defined(_M_ARM)) && (__ARM_ARCH == 7))
#define SPY_SIMD_IS_ARM_NEON
#define SPY_SIMD_DETECTED ::spy::_::simd_version::neon_
#endif
#if defined(SPY_SIMD_DETECTED) && !defined(SPY_SIMD_VENDOR)
#define SPY_SIMD_IS_ARM
#define SPY_SIMD_VENDOR ::spy::_::simd_isa::arm_
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__VSX__)
#define SPY_SIMD_IS_PPC_VSX
#if defined(_ARCH_PWR10)
#define SPY_SIMD_IS_PPC_VSX_3_01
#define SPY_SIMD_DETECTED ::spy::_::simd_version::vsx_3_01_
#elif defined(_ARCH_PWR9)
#define SPY_SIMD_IS_PPC_VSX_3_00
#define SPY_SIMD_DETECTED ::spy::_::simd_version::vsx_3_00_
#elif defined(_ARCH_PWR8)
#define SPY_SIMD_IS_PPC_VSX_2_07
#define SPY_SIMD_DETECTED ::spy::_::simd_version::vsx_2_07_
#elif defined(_ARCH_PWR7)
#define SPY_SIMD_IS_PPC_VSX_2_06
#define SPY_SIMD_DETECTED ::spy::_::simd_version::vsx_2_06_
#endif
#endif
#if !defined(SPY_SIMD_DETECTED) && (defined(__ALTIVEC__) || defined(__VEC__))
#define SPY_SIMD_IS_PPC_VMX
#if defined(_ARCH_PWR10)
#define SPY_SIMD_IS_PPC_VMX_3_01
#define SPY_SIMD_DETECTED ::spy::_::simd_version::vmx_3_01_
#elif defined(_ARCH_PWR9)
#define SPY_SIMD_IS_PPC_VMX_3_00
#define SPY_SIMD_DETECTED ::spy::_::simd_version::vmx_3_00_
#elif defined(_ARCH_PWR8)
#define SPY_SIMD_IS_PPC_VMX_2_07
#define SPY_SIMD_DETECTED ::spy::_::simd_version::vmx_2_07_
#elif defined(_ARCH_PWR7)
#define SPY_SIMD_IS_PPC_VMX_2_06
#define SPY_SIMD_DETECTED ::spy::_::simd_version::vmx_2_06_
#elif defined(_ARCH_PWR6)
#define SPY_SIMD_IS_PPC_VMX_2_05
#define SPY_SIMD_DETECTED ::spy::_::simd_version::vmx_2_05_
#elif defined(_ARCH_PWR5)
#define SPY_SIMD_IS_PPC_VMX_2_03
#define SPY_SIMD_DETECTED ::spy::_::simd_version::vmx_2_03_
#endif
#define SPY_SIMD_DETECTED ::spy::_::simd_version::vmx_
#endif
#if defined(SPY_SIMD_DETECTED) && !defined(SPY_SIMD_VENDOR)
#define SPY_SIMD_IS_PPC
#define SPY_SIMD_VENDOR ::spy::_::simd_isa::ppc_
#endif
#if defined(__riscv_vector)
#if !defined(__riscv_v_fixed_vlen)
#define SPY_SIMD_IS_RISCV_FLEXIBLE_RVV
#define SPY_SIMD_DETECTED ::spy::_::simd_version::rvv_
#else
#define SPY_SIMD_IS_RISCV_FIXED_RVV
#define SPY_SIMD_DETECTED ::spy::_::simd_version::fixed_rvv_
#endif
#endif
#if defined(__riscv_vector)
#define SPY_SIMD_IS_RISCV_RVV
#define SPY_SIMD_VENDOR ::spy::_::simd_isa::riscv_
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__wasm_simd128__)
#define SPY_SIMD_DETECTED ::spy::_::simd_version::simd128_
#endif
#if defined(SPY_SIMD_DETECTED) && !defined(SPY_SIMD_VENDOR)
#define SPY_SIMD_IS_WASM
#define SPY_SIMD_VENDOR ::spy::_::simd_isa::wasm_
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__AVX512F__)
#define SPY_SIMD_IS_X86_AVX512
#define SPY_SIMD_DETECTED ::spy::_::simd_version::avx512_
#if defined(__AVX512BW__)
#define SPY_SIMD_IS_X86_AVX512_BW
#endif
#if defined(__AVX512CD__)
#define SPY_SIMD_IS_X86_AVX512_CD
#endif
#if defined(__AVX512DQ__)
#define SPY_SIMD_IS_X86_AVX512_DQ
#endif
#if defined(__AVX512ER__)
#define SPY_SIMD_IS_X86_AVX512_ER
#endif
#if defined(__AVX512IFMA__)
#define SPY_SIMD_IS_X86_AVX512_IFMA
#endif
#if defined(__AVX512PF__)
#define SPY_SIMD_IS_X86_AVX512_PF
#endif
#if defined(__AVX512VL__)
#define SPY_SIMD_IS_X86_AVX512_VL
#endif
#if defined(__AVX512VPOPCNTDQ__)
#define SPY_SIMD_IS_X86_AVX512_POPCNTDQ
#endif
#if defined(__AVX5124FMAPS__)
#define SPY_SIMD_IS_X86_AVX512_4FMAPS
#endif
#if defined(__AVX5124VNNIW__)
#define SPY_SIMD_IS_X86_AVX512_VNNIW
#endif
#if defined(__AVX512VBMI__)
#define SPY_SIMD_IS_X86_AVX512_VBMI
#endif
#if defined(__AVX512BF16__)
#define SPY_SIMD_IS_X86_AVX512_BF16
#endif
#if defined(__AVX512BITALG__)
#define SPY_SIMD_IS_X86_AVX512_BITALG
#endif
#if defined(__AVX512VBMI2__)
#define SPY_SIMD_IS_X86_AVX512_VBMI2
#endif
#if defined(__AVX512VNNI__)
#define SPY_SIMD_IS_X86_AVX512_VNNI
#endif
#if defined(__AVX512VP2INTERSECT__)
#define SPY_SIMD_IS_X86_AVX512_VP2INTERSECT
#endif
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__AVX2__)
#define SPY_SIMD_IS_X86_AVX2
#define SPY_SIMD_DETECTED ::spy::_::simd_version::avx2_
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__AVX__)
#define SPY_SIMD_IS_X86_AVX
#define SPY_SIMD_DETECTED ::spy::_::simd_version::avx_
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__SSE4_2__)
#define SPY_SIMD_IS_X86_SSE4_2
#define SPY_SIMD_DETECTED ::spy::_::simd_version::sse42_
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__SSE4_1__)
#define SPY_SIMD_IS_X86_SSE4_1
#define SPY_SIMD_DETECTED ::spy::_::simd_version::sse41_
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__SSSE3__)
#define SPY_SIMD_IS_X86_SSSE3
#define SPY_SIMD_DETECTED ::spy::_::simd_version::ssse3_
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__SSE3__)
#define SPY_SIMD_IS_X86_SSE3
#define SPY_SIMD_DETECTED ::spy::_::simd_version::sse3_
#endif
#if !defined(SPY_SIMD_DETECTED) &&                                                                 \
    (defined(__SSE2__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2))
#define SPY_SIMD_IS_X86_SSE2
#define SPY_SIMD_DETECTED ::spy::_::simd_version::sse2_
#endif
#if !defined(SPY_SIMD_DETECTED) && (defined(__SSE__) || defined(_M_IX86_FP))
#define SPY_SIMD_IS_X86_SSE
#define SPY_SIMD_DETECTED ::spy::_::simd_version::sse1_
#endif
#if defined(SPY_SIMD_DETECTED) && !defined(SPY_SIMD_VENDOR)
#define SPY_SIMD_IS_X86
#define SPY_SIMD_VENDOR ::spy::_::simd_isa::x86_
#endif
namespace spy::supports
{
#if defined(__FMA__)
#define SPY_SIMD_SUPPORTS_FMA
  constexpr inline bool fma_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  constexpr inline bool fma_ = _::implementation_defined {};
#else
  constexpr inline bool fma_ = false;
#endif
#if defined(__FMA4__)
#define SPY_SIMD_SUPPORTS_FMA4
  constexpr inline bool fma4_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  constexpr inline bool fma4_ = _::implementation_defined {};
#else
  constexpr inline bool fma4_ = false;
#endif
#if defined(__XOP__)
#define SPY_SIMD_SUPPORTS_XOP
  constexpr inline bool xop_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  constexpr inline bool xop_ = _::implementation_defined {};
#else
  constexpr inline bool xop_ = false;
#endif
#if defined(__F16C__)
#define SPY_SIMD_SUPPORTS_F16C
  constexpr inline bool f16c_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  constexpr inline bool f16c_ = _::implementation_defined {};
#else
  constexpr inline bool f16c_ = false;
#endif
  namespace avx512
  {
#if defined(__AVX512BW__)
#define SPY_SIMD_IS_X86_AVX512_BW
    constexpr inline bool bw_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    constexpr inline bool bw_ = _::implementation_defined {};
#else
    constexpr inline bool bw_ = false;
#endif
#if defined(__AVX512CD__)
#define SPY_SIMD_IS_X86_AVX512_CD
    constexpr inline bool cd_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    constexpr inline bool cd_ = _::implementation_defined {};
#else
    constexpr inline bool cd_ = false;
#endif
#if defined(__AVX512DQ__)
#define SPY_SIMD_IS_X86_AVX512_DQ
    constexpr inline bool dq_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    constexpr inline bool dq_ = _::implementation_defined {};
#else
    constexpr inline bool dq_ = false;
#endif
#if defined(__AVX512ER__)
#define SPY_SIMD_IS_X86_AVX512_ER
    constexpr inline bool er_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    constexpr inline bool er_ = _::implementation_defined {};
#else
    constexpr inline bool er_ = false;
#endif
#if defined(__AVX512IFMA__)
#define SPY_SIMD_IS_X86_AVX512_IFMA
    constexpr inline bool ifma_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    constexpr inline bool ifma_ = _::implementation_defined {};
#else
    constexpr inline bool ifma_ = false;
#endif
#if defined(__AVX512PF__)
#define SPY_SIMD_IS_X86_AVX512_PF
    constexpr inline bool pf_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    constexpr inline bool pf_ = _::implementation_defined {};
#else
    constexpr inline bool pf_ = false;
#endif
#if defined(__AVX512VL__)
#define SPY_SIMD_IS_X86_AVX512_VL
    constexpr inline bool vl_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    constexpr inline bool vl_ = _::implementation_defined {};
#else
    constexpr inline bool vl_ = false;
#endif
#if defined(__AVX512VPOPCNTDQ__)
#define SPY_SIMD_IS_X86_AVX512_POPCNTDQ
    constexpr inline bool popcntdq_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    constexpr inline bool popcntdq_ = _::implementation_defined {};
#else
    constexpr inline bool popcntdq_ = false;
#endif
#if defined(__AVX5124FMAPS__)
#define SPY_SIMD_IS_X86_AVX512_4FMAPS
    constexpr inline bool _4fmaps_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    constexpr inline bool _4fmaps_ = _::implementation_defined {};
#else
    constexpr inline bool _4fmaps_ = false;
#endif
#if defined(__AVX5124VNNIW__)
#define SPY_SIMD_IS_X86_AVX512_VNNIW
    constexpr inline bool vnniw_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    constexpr inline bool vnniw_ = _::implementation_defined {};
#else
    constexpr inline bool vnniw_ = false;
#endif
#if defined(__AVX512VBMI__)
#define SPY_SIMD_IS_X86_AVX512_VBMI
    constexpr inline bool vbmi_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    constexpr inline bool vbmi_ = _::implementation_defined {};
#else
    constexpr inline bool vbmi_ = false;
#endif
#if defined(__AVX512BF16__)
#define SPY_SIMD_IS_X86_AVX512_BF16
    constexpr inline bool bf16_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    constexpr inline bool bf16_ = _::implementation_defined {};
#else
    constexpr inline bool bf16_ = false;
#endif
#if defined(__AVX512BITALG__)
#define SPY_SIMD_IS_X86_AVX512_BITALG
    constexpr inline bool bitalg_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    constexpr inline bool bitalg_ = _::implementation_defined {};
#else
    constexpr inline bool bitalg_ = false;
#endif
#if defined(__AVX512VBMI2__)
#define SPY_SIMD_IS_X86_AVX512_VBMI2
    constexpr inline bool vbmi2_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    constexpr inline bool vbmi2_ = _::implementation_defined {};
#else
    constexpr inline bool vbmi2_ = false;
#endif
#if defined(__AVX512VNNI__)
#define SPY_SIMD_IS_X86_AVX512_VNNI
    constexpr inline bool vnni_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    constexpr inline bool vnni_ = _::implementation_defined {};
#else
    constexpr inline bool vnni_ = false;
#endif
#if defined(__AVX512VP2INTERSECT__)
#define SPY_SIMD_IS_X86_AVX512_VP2INTERSECT
    constexpr inline bool vpintersect_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    constexpr inline bool vpintersect_ = _::implementation_defined {};
#else
    constexpr inline bool vpintersect_ = false;
#endif
  }
}
namespace spy::_
{
  enum class simd_isa
  {
    undefined_ = -1,
    x86_       = 1000,
    ppc_       = 2000,
    arm_       = 3000,
    arm_sve_   = 3500,
    wasm_      = 4000,
    riscv_     = 5000
  };
  enum class simd_version
  {
    undefined_  = -1,
    sse1_       = 1110,
    sse2_       = 1120,
    sse3_       = 1130,
    ssse3_      = 1131,
    sse41_      = 1141,
    sse42_      = 1142,
    avx_        = 1201,
    avx2_       = 1202,
    avx512_     = 1300,
    vmx_        = 2000,
    vmx_2_03_   = 2203,
    vmx_2_05_   = 2205,
    vmx_2_06_   = 2206,
    vmx_2_07_   = 2207,
    vmx_3_00_   = 2300,
    vmx_3_01_   = 2301,
    vsx_        = 3000,
    vsx_2_06_   = 3206,
    vsx_2_07_   = 3207,
    vsx_3_00_   = 3300,
    vsx_3_01_   = 3301,
    neon_       = 4001,
    asimd_      = 4002,
    sve_        = 5000,
    fixed_sve_  = 5100,
    sve2_       = 5500,
    fixed_sve2_ = 5600,
    simd128_    = 6000,
    rvv_        = 7000,
    fixed_rvv_  = 7500
  };
  template<simd_version Version> constexpr int simd_width()
  {
    using enum simd_version;
    if constexpr(Version == simd128_ || (Version >= sse1_ && Version <= sse42_) ||
                 Version == neon_ || Version == asimd_ ||
                 (Version >= vmx_2_03_ && Version <= vsx_3_01_))
      return 128;
    else if constexpr(Version == avx_ || Version == avx2_) return 256;
    else if constexpr(Version == avx512_) return 512;
    else if constexpr(Version == rvv_) return -1;
    else if constexpr(Version == fixed_rvv_)
    {
#if defined(__riscv_v_fixed_vlen)
      return __riscv_v_fixed_vlen;
#else
      return -1;
#endif
    }
    else if constexpr(Version == sve_ || Version == sve2_)
    {
      return -1;
    }
    else if constexpr(Version == fixed_sve_ || Version == fixed_sve2_)
    {
#if defined(__ARM_FEATURE_SVE_BITS)
      return __ARM_FEATURE_SVE_BITS;
#else
      return -1;
#endif
    }
    else return -1;
  }
  template<_::stream OS> void print_supplemental_sets(OS& os)
  {
    if constexpr(spy::supports::fma_) os << " (with FMA3 support)";
    if constexpr(spy::supports::fma4_) os << " (with FMA4 support)";
    if constexpr(spy::supports::xop_) os << " (with XOP support)";
  }
  template<simd_isa     InsSetArch = simd_isa::undefined_,
           simd_version Version    = simd_version::undefined_>
  struct simd_info
  {
    static constexpr auto isa     = InsSetArch;
    static constexpr auto version = Version;
    static constexpr int  width   = simd_width<Version>();
    static constexpr bool has_fixed_cardinal() { return width != -1; }
    template<simd_isa I2, simd_version V2>
    friend constexpr bool operator==(simd_info, simd_info<I2, V2>) noexcept
    {
      if constexpr(Version != simd_version::undefined_ && V2 != simd_version::undefined_)
        return (InsSetArch == I2) && (Version == V2);
      else return InsSetArch == I2;
    }
    template<simd_isa I2, simd_version V2>
    friend constexpr std::partial_ordering operator<=>(simd_info, simd_info<I2, V2>) noexcept
    {
      if constexpr(InsSetArch != I2) return std::partial_ordering::unordered;
      else return Version <=> V2;
    }
    template<_::stream OS> friend auto& operator<<(OS& os, simd_info const&)
    {
      using enum simd_version;
      if constexpr(Version == simd128_) os << "WASM SIMD128";
      else if constexpr(Version == sse1_) os << "X86 SSE";
      else if constexpr(Version == sse2_) os << "X86 SSE2";
      else if constexpr(Version == sse3_) os << "X86 SSE3";
      else if constexpr(Version == ssse3_) os << "X86 SSSE3";
      else if constexpr(Version == sse41_) os << "X86 SSE4.1";
      else if constexpr(Version == sse42_) os << "X86 SSE4.2";
      else if constexpr(Version == avx_) os << "X86 AVX";
      else if constexpr(Version == avx2_) os << "X86 AVX2";
      else if constexpr(Version == avx512_) os << "X86 AVX512";
      else if constexpr(Version >= vmx_2_03_ && Version <= vmx_3_01_)
      {
        constexpr auto v = static_cast<int>(Version);
        os << "PPC VMX with ISA v" << ((v - 2000) / 100.);
      }
      else if constexpr(Version >= vsx_2_06_ && Version <= vsx_3_01_)
      {
        constexpr auto v = static_cast<int>(Version);
        os << "PPC VSX with ISA v" << ((v - 3000) / 100.);
      }
      else if constexpr(Version == neon_) os << "ARM NEON";
      else if constexpr(Version == asimd_) os << "ARM ASIMD";
      else if constexpr(Version == sve_) os << "ARM SVE (dyn.)";
      else if constexpr(Version == fixed_sve_) os << "ARM SVE (" << simd_info::width << " bits)";
      else if constexpr(Version == sve2_) os << "ARM SVE2 (dyn.)";
      else if constexpr(Version == fixed_sve2_) os << "ARM SVE2 (" << simd_info::width << " bits)";
      else if constexpr(Version == rvv_) os << "RISC-V RVV (dyn.)";
      else if constexpr(Version == fixed_rvv_) os << "RISC-V RVV (" << simd_info::width << " bits)";
      else return os << "Undefined SIMD instructions set";
      _::print_supplemental_sets(os);
      return os;
    }
  };
}
namespace spy
{
#if defined(SPY_SIMD_DETECTED)
  constexpr inline auto simd_instruction_set = _::simd_info<SPY_SIMD_VENDOR, SPY_SIMD_DETECTED> {};
  #else
  constexpr inline auto simd_instruction_set = _::simd_info<> {};
#endif
  constexpr inline auto undefined_simd_ = _::simd_info<> {};
  template<_::simd_version V = _::simd_version::undefined_>
  using wasm_simd_info             = _::simd_info<_::simd_isa::wasm_, V>;
  constexpr inline auto wasm_simd_ = wasm_simd_info<> {};
  constexpr inline auto simd128_   = wasm_simd_info<_::simd_version::simd128_> {};
  template<_::simd_version V = _::simd_version::undefined_>
  using x86_simd_info             = _::simd_info<_::simd_isa::x86_, V>;
  constexpr inline auto x86_simd_ = x86_simd_info<> {};
  constexpr inline auto sse1_     = x86_simd_info<_::simd_version::sse1_> {};
  constexpr inline auto sse2_     = x86_simd_info<_::simd_version::sse2_> {};
  constexpr inline auto sse3_     = x86_simd_info<_::simd_version::sse3_> {};
  constexpr inline auto ssse3_    = x86_simd_info<_::simd_version::ssse3_> {};
  constexpr inline auto sse41_    = x86_simd_info<_::simd_version::sse41_> {};
  constexpr inline auto sse42_    = x86_simd_info<_::simd_version::sse42_> {};
  constexpr inline auto avx_      = x86_simd_info<_::simd_version::avx_> {};
  constexpr inline auto avx2_     = x86_simd_info<_::simd_version::avx2_> {};
  constexpr inline auto avx512_   = x86_simd_info<_::simd_version::avx512_> {};
  template<_::simd_version V = _::simd_version::undefined_>
  using ppc_simd_info             = _::simd_info<_::simd_isa::ppc_, V>;
  constexpr inline auto ppc_simd_ = ppc_simd_info<> {};
  constexpr inline auto vmx_      = ppc_simd_info<_::simd_version::vmx_> {};
  constexpr inline auto vmx_2_03_ = ppc_simd_info<_::simd_version::vmx_2_03_> {};
  constexpr inline auto vmx_2_05_ = ppc_simd_info<_::simd_version::vmx_2_05_> {};
  constexpr inline auto vmx_2_06_ = ppc_simd_info<_::simd_version::vmx_2_06_> {};
  constexpr inline auto vmx_2_07_ = ppc_simd_info<_::simd_version::vmx_2_07_> {};
  constexpr inline auto vmx_3_00_ = ppc_simd_info<_::simd_version::vmx_3_00_> {};
  constexpr inline auto vmx_3_01_ = ppc_simd_info<_::simd_version::vmx_3_01_> {};
  constexpr inline auto vsx_      = ppc_simd_info<_::simd_version::vsx_> {};
  constexpr inline auto vsx_2_06_ = ppc_simd_info<_::simd_version::vsx_2_06_> {};
  constexpr inline auto vsx_2_07_ = ppc_simd_info<_::simd_version::vsx_2_07_> {};
  constexpr inline auto vsx_3_00_ = ppc_simd_info<_::simd_version::vsx_3_00_> {};
  constexpr inline auto vsx_3_01_ = ppc_simd_info<_::simd_version::vsx_3_01_> {};
  template<_::simd_version V = _::simd_version::undefined_>
  using arm_simd_info = _::simd_info<_::simd_isa::arm_, V>;
  template<_::simd_version V = _::simd_version::undefined_>
  using sve_simd_info               = _::simd_info<_::simd_isa::arm_sve_, V>;
  constexpr inline auto arm_simd_   = arm_simd_info<> {};
  constexpr inline auto neon_       = arm_simd_info<_::simd_version::neon_> {};
  constexpr inline auto asimd_      = arm_simd_info<_::simd_version::asimd_> {};
  constexpr inline auto sve_        = sve_simd_info<_::simd_version::sve_> {};
  constexpr inline auto fixed_sve_  = sve_simd_info<_::simd_version::fixed_sve_> {};
  constexpr inline auto sve2_       = sve_simd_info<_::simd_version::sve2_> {};
  constexpr inline auto fixed_sve2_ = sve_simd_info<_::simd_version::fixed_sve2_> {};
  template<_::simd_version V = _::simd_version::undefined_>
  using riscv_simd_info             = _::simd_info<_::simd_isa::riscv_, V>;
  constexpr inline auto riscv_simd_ = riscv_simd_info<> {};
  constexpr inline auto rvv_        = riscv_simd_info<_::simd_version::rvv_> {};
  constexpr inline auto fixed_rvv_  = riscv_simd_info<_::simd_version::fixed_rvv_> {};
}
#include <compare>
#include <cstddef>
namespace spy::_
{
  template<int Year> struct cpp_standard_t
  {
    static constexpr int                   year = Year;
    template<int OtherYear> constexpr auto operator<=>(cpp_standard_t<OtherYear>) const
    {
      return year <=> OtherYear;
    }
    template<int OtherYear> constexpr bool operator==(cpp_standard_t<OtherYear>) const
    {
      return year == OtherYear;
    }
    constexpr auto operator<=>(int other_year) const { return year <=> other_year; }
    constexpr bool operator==(int other_year) const { return year == other_year; }
    template<_::stream OS> friend auto& operator<<(OS& os, cpp_standard_t const&)
    {
      if constexpr(Year != 0) return os << "C++" << Year;
      else return os << "Unknown C++ standard version";
    }
  };
}
namespace spy
{
#if defined(_MSVC_LANG)
#define SPY_RAW_CXX_STANDARD _MSVC_LANG
#else
#define SPY_RAW_CXX_STANDARD __cplusplus
#endif
#if SPY_RAW_CXX_STANDARD > 202302L
#define SPY_CXX_VERSION 26
#elif SPY_RAW_CXX_STANDARD >= 202302L
#define SPY_CXX_VERSION 23
#elif SPY_RAW_CXX_STANDARD >= 202002L
#define SPY_CXX_VERSION 20
#else
#define SPY_CXX_VERSION 0
#endif
  inline constexpr _::cpp_standard_t<SPY_CXX_VERSION> cpp_standard {};
}
namespace spy::literal
{
  template<char... c>
    requires(sizeof...(c) == 2)
  consteval auto operator""_cpp()
  {
    return _::cpp_standard_t<_::parse<c...>(0, 2)> {};
  }
}
#include <cstddef>
namespace spy::_
{
  enum class stdlib
  {
    undefined_ = -1,
    libcpp_,
    gnucpp_
  };
  template<stdlib Lib, int M, int N, int P> struct stdlib_info
  {
    static constexpr stdlib              vendor  = Lib;
    static constexpr version_id<M, N, P> version = {};
    constexpr explicit                   operator bool() const noexcept;
    template<stdlib C2> constexpr bool   operator==(stdlib_info<C2, -1, 0, 0> const&) const noexcept
    {
      return C2 == vendor;
    }
    template<stdlib C2, int M2, int N2, int P2>
    constexpr bool operator==(stdlib_info<C2, M2, N2, P2> const& c2) const noexcept
    {
      return C2 == vendor && version == c2.version;
    }
    template<stdlib C2, int M2, int N2, int P2>
    constexpr std::partial_ordering
    operator<=>(stdlib_info<C2, M2, N2, P2> const& c2) const noexcept
    {
      if constexpr(vendor == C2) return version <=> c2.version;
      else return std::partial_ordering::unordered;
    }
    template<_::stream OS> friend auto& operator<<(OS& os, stdlib_info const&)
    {
      if(Lib == stdlib::libcpp_) return os << "libc++ Standard C++ Library " << version;
      if(Lib == stdlib::gnucpp_) return os << "GNU Standard C++ Library " << version;
      return os << "Undefined Standard C++ Library";
    }
  };
  template<int M, int N, int P> using libcpp_t = stdlib_info<stdlib::libcpp_, M, N, P>;
  template<int M, int N, int P> using gnucpp_t = stdlib_info<stdlib::gnucpp_, M, N, P>;
}
namespace spy
{
#if defined(_LIBCPP_VERSION)
#define SPY_STDLIB_IS_LIBCPP
  using stdlib_type = _::libcpp_t<(_LIBCPP_VERSION / 1000) % 10, 0, _LIBCPP_VERSION % 1000>;
#elif defined(__GLIBCXX__)
#define SPY_STDLIB_IS_GLIBCXX
#define SPY0 (__GLIBCXX__ / 100)
  using stdlib_type = _::gnucpp_t<(SPY0 / 100) % 10000, SPY0 % 100, __GLIBCXX__ % 100>;
#undef SPY0
#else
#define SPY_STDLIB_IS_UNKNOWN
  using stdlib_type = _::stdlib_info<_::stdlib::undefined_, -1, 0, 0>;
#endif
  constexpr inline auto stdlib = stdlib_type {};
}
namespace spy::_
{
  template<stdlib SLib, int M, int N, int P>
  constexpr stdlib_info<SLib, M, N, P>::operator bool() const noexcept
  {
    return spy::stdlib == *this;
  }
}
namespace spy
{
  constexpr inline auto libcpp_ = _::libcpp_t<-1, 0, 0> {};
  constexpr inline auto gnucpp_ = _::gnucpp_t<-1, 0, 0> {};
}
namespace spy::literal
{
  template<char... c> consteval auto operator""_libcpp()
  {
    return _::literal_wrap<_::libcpp_t, c...>();
  }
  template<char... c> consteval auto operator""_gnucpp()
  {
    return _::literal_wrap<_::gnucpp_t, c...>();
  }
}
#if defined(SPY_ARCH_IS_ARM)
#if defined(__ARM_FP16_FORMAT_IEEE) && __ARM_FP16_FORMAT_IEEE == 1 &&                              \
    (!defined(__ARM_FP16_FORMAT_ALTERNATIVE) || __ARM_FP16_FORMAT_ALTERNATIVE == 0)
#define SPY_SUPPORTS_FP16_TYPE
#if defined(__ARM_FEATURE_FP16_SCALAR_ARITHMETIC)
#define SPY_SUPPORTS_FP16_SCALAR_OPS
#endif
#if defined(__ARM_FEATURE_FP16_VECTOR_ARITHMETIC)
#define SPY_SUPPORTS_FP16_VECTOR_OPS
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#elif defined(__aarch64__)
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#endif
#endif
#elif defined(SPY_ARCH_IS_X86)
#define SPY_SUPPORTS_FP16_TYPE
#elif defined(SPY_ARCH_IS_AMD64)
#define SPY_SUPPORTS_FP16_TYPE
#if defined(__AVX512FP16__)
#define SPY_SUPPORTS_FP16_SCALAR_OPS
#define SPY_SUPPORTS_FP16_VECTOR_OPS
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#elif defined(__F16C__)
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#endif
#elif defined(SPY_ARCH_IS_RISCV)
#define SPY_SUPPORTS_FP16_TYPE
#if defined(__riscv_zfh)
#define SPY_SUPPORTS_FP16_SCALAR_OPS
#endif
#if defined(__riscv_zvfh)
#define SPY_SUPPORTS_FP16_VECTOR_OPS
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#elif defined(__riscv_zvfhmin)
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#endif
#endif
namespace spy::supports::fp16
{
#if defined(SPY_SUPPORTS_FP16_TYPE)
  constexpr inline bool type = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  constexpr inline bool type = _::implementation_defined {};
#else
  constexpr inline bool type = false;
#endif
#if defined(SPY_SUPPORTS_FP16_SCALAR_OPS)
  constexpr inline bool scalar_ops = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  constexpr inline bool scalar_ops = _::implementation_defined {};
#else
  constexpr inline bool scalar_ops = false;
#endif
#if defined(SPY_SUPPORTS_FP16_VECTOR_CONVERSION)
  constexpr inline bool vector_conversion = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  constexpr inline bool vector_conversion = _::implementation_defined {};
#else
  constexpr inline bool vector_conversion = false;
#endif
#if defined(SPY_SUPPORTS_FP16_VECTOR_OPS)
  constexpr inline bool vector_ops = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  constexpr inline bool vector_ops = _::implementation_defined {};
#else
  constexpr inline bool vector_ops = false;
#endif
}
#endif
