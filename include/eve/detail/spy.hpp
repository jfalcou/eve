//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#ifndef SPY_SPY_HPP_INCLUDED
#define SPY_SPY_HPP_INCLUDED
#include <ostream>
namespace spy::detail
{
  enum class archs  { undefined_  = -1
                    , x86_ = 10, amd64_ = 11
                    , ppc_ = 20, arm_ = 30
                    };
  template<archs Arch> struct arch_info
  {
    static constexpr archs  vendor  = Arch;
    inline constexpr operator bool() const noexcept;
    template<archs A2>
    constexpr bool operator==(arch_info<A2> const&) const noexcept
    {
      return A2 == vendor;
    }
  };
  template<archs Arch>
  std::ostream& operator<<(std::ostream& os, arch_info<Arch> const&)
  {
    if(Arch == archs::x86_  ) return os << "X86";
    if(Arch == archs::amd64_) return os << "AMD64";
    if(Arch == archs::ppc_  ) return os << "PowerPC";
    if(Arch == archs::arm_  ) return os << "ARM";
    return os << "Undefined Architecture";
  }
}
namespace spy
{
#if defined(i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) ||                \
    defined(__i686__) || defined(__i386) || defined(_M_IX86) || defined(_X86_) ||                  \
    defined(__THW_INTEL__) || defined(__I86__) || defined(__INTEL__)
  using arch_type = detail::arch_info<detail::archs::x86_>;
  #define SPY_ARCH_IS_X86
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64__) || defined(__amd64) || defined(_M_X64)
  #define SPY_ARCH_IS_AMD64
  using arch_type = detail::arch_info<detail::archs::amd64_>;
#elif defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) || defined(__ppc__) ||     \
      defined(_M_PPC) || defined(_ARCH_PPC) || defined(__PPCGECKO__) || defined(__PPCBROADWAY__) || \
      defined(_XENON)
  using arch_type = detail::arch_info<detail::archs::ppc_>;
  #define SPY_ARCH_IS_PPC
#elif defined(__arm__) || defined(__arm64) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) ||   \
      defined(__TARGET_ARCH_THUMB) || defined(_M_ARM)
  using arch_type = detail::arch_info<detail::archs::arm_>;
  #define SPY_ARCH_IS_ARM
#else
  #define SPY_ARCH_IS_UNKNOWN
  using arch_type = detail::arch_info<detail::archs::undefined_>;
#endif
  constexpr inline arch_type architecture;
}
namespace spy::detail
{
  template<archs Arch>
  inline constexpr arch_info<Arch>::operator bool() const noexcept
  {
    return *this == spy::architecture;
  }
}
namespace spy
{
  constexpr inline auto x86_    = detail::arch_info<detail::archs::x86_>{};
  constexpr inline auto amd64_  = detail::arch_info<detail::archs::amd64_>{};
  constexpr inline auto ppc_    = detail::arch_info<detail::archs::ppc_>{};
  constexpr inline auto arm_    = detail::arch_info<detail::archs::arm_>{};
}
#include <iosfwd>
#include <ostream>
namespace spy::detail
{
  template<char... c> constexpr int find(int i0)
  {
    int sz = sizeof...(c);
    char arr[] = {c...};
    while( i0<sz && arr[i0] != '\'' ) ++i0;
    return i0;
  }
  template<char... c> constexpr int parse(int i0, int i1)
  {
    char arr[] = {c...};
    int value = 0;
    while( i0<i1 && arr[i0] != '\'' ) value = value*10 + (arr[i0++] - 48);
    return value;
  }
  template<template<int,int,int> class Wrapper, char ...c> constexpr auto literal_wrap()
  {
    constexpr int b0 = 0     , e0 = find<c...>(0);
    constexpr int b1 = e0 + 1, e1 = find<c...>(b1);
    constexpr int b2 = e1+1  , e2 = sizeof...(c);
    return Wrapper<parse<c...>(b0,e0),parse<c...>(b1,e1),parse<c...>(b2,e2)>{};
  }
  template<int M, int N, int P> struct version_id
  {
    static constexpr int major = M;
    static constexpr int minor = N;
    static constexpr int patch = P;
  };
  template<int M = 1, int N = 0, int P = 0> constexpr inline version_id<M,N,P> version = {};
  using unspecified_version_t = version_id<-1,0,0>;
  constexpr inline unspecified_version_t unspecified_version = {};
  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator==(version_id<M1,N1,P1> const&, version_id<M2,N2,P2> const&) noexcept
  {
    return (M1==M2) && (N1==N2) && (P1==P2);
  }
  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator!=(version_id<M1,N1,P1> const& v1, version_id<M2,N2,P2> const& v2) noexcept
  {
    return !(v1==v2);
  }
  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator<(version_id<M1,N1,P1> const&, version_id<M2,N2,P2> const&) noexcept
  {
    if constexpr(M1 < M2) return true;
    if constexpr(M1 > M2) return false;
    if constexpr(N1 < N2) return true;
    if constexpr(N1 > N2) return false;
    return P1 < P2;
  }
  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator>(version_id<M1,N1,P1> const&, version_id<M2,N2,P2> const&) noexcept
  {
    if constexpr(M1 > M2) return true;
    if constexpr(M1 < M2) return false;
    if constexpr(N1 > N2) return true;
    if constexpr(N1 < N2) return false;
    return P1 > P2;
  }
  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator<=(version_id<M1,N1,P1> const& a, version_id<M2,N2,P2> const& b) noexcept
  {
    return !(a>b);
  }
  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator>=(version_id<M1,N1,P1> const& a, version_id<M2,N2,P2> const& b) noexcept
  {
    return !(a<b);
  }
  template<int M, int N, int P>
  std::ostream& operator<<(std::ostream& os, version_id<M,N,P> const&)
  {
    return os << "v" << M << "." << N << "." << P;
  }
  inline std::ostream& operator<<(std::ostream& os, unspecified_version_t const&)
  {
    return os << "(unspecified)";
  }
}
#define SPY_VERSION_COMPARISONS_OPERATOR(ID,TYPE)                       \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator==( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept \
{                                                                       \
  return C2 == vendor && version == c2.version;                         \
}                                                                       \
                                                                        \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator!=( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept \
{                                                                       \
  return C2 == vendor && version != c2.version;                         \
}                                                                       \
                                                                        \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator<( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept  \
{                                                                       \
  return C2 == vendor && version < c2.version;                          \
}                                                                       \
                                                                        \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator>( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept  \
{                                                                       \
  return C2 == vendor && version > c2.version;                          \
}                                                                       \
                                                                        \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator>=( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept \
{                                                                       \
  return C2 == vendor && version >= c2.version;                         \
}                                                                       \
                                                                        \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator<=( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept \
{                                                                       \
  return C2 == vendor && version <= c2.version;                         \
}                                                                       \

namespace spy::detail
{
  enum class compilers { undefined_  = - 1, msvc_, intel_, clang_, gcc_ };
  template<compilers Compiler, int M, int N, int P> struct compilers_info
  {
    static constexpr compilers          vendor  = Compiler;
    static constexpr version_id<M,N,P>  version = {};
    inline constexpr operator bool() const noexcept;
    template<compilers C2>
    constexpr bool operator==(compilers_info<C2,-1,0,0> const&) const noexcept
    {
      return C2 == vendor;
    }
    SPY_VERSION_COMPARISONS_OPERATOR(compilers,compilers_info)
  };
  template<compilers C, int M, int N, int P>
  std::ostream& operator<<(std::ostream& os, compilers_info<C, M, N, P> const& c)
  {
    if(C == compilers::msvc_ ) return os << "Microsoft Visual Studio "  << c.version;
    if(C == compilers::intel_) return os << "Intel icpc "               << c.version;
    if(C == compilers::clang_) return os << "clang "                    << c.version;
    if(C == compilers::gcc_  ) return os << "g++ "                      << c.version;
    return os << "Undefined " << c.version;
  }
  template<int M, int N, int P> using msvc_t  = compilers_info<compilers::msvc_ ,M,N,P>;
  template<int M, int N, int P> using intel_t = compilers_info<compilers::intel_,M,N,P>;
  template<int M, int N, int P> using clang_t = compilers_info<compilers::clang_,M,N,P>;
  template<int M, int N, int P> using gcc_t   = compilers_info<compilers::gcc_  ,M,N,P>;
}
namespace spy
{
#if defined(_MSC_VER)
  #define SPY_COMPILER_IS_MSVC
  using compiler_type = detail::msvc_t<_MSC_VER / 100, _MSC_VER % 100, _MSC_FULL_VER % 100000>;
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
  #define SPY_COMPILER_IS_INTEL
  #define SPY0 __INTEL_COMPILER
  using compiler_type = detail::intel_t<(SPY0 / 100) % 100,SPY0 % 100, __INTEL_COMPILER_UPDATE>;
  #undef SPY0
#elif defined(__clang__)
  #define SPY_COMPILER_IS_CLANG
  using compiler_type = detail::clang_t<__clang_major__, __clang_minor__, __clang_patchlevel__>;
#elif defined(__GNUC__)
  #define SPY_COMPILER_IS_GCC
  using compiler_type = detail::gcc_t<__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__>;
#else
  #define SPY_COMPILER_IS_UNKNOWN
  using compiler_type = detail::compilers_info<compilers::undefined_,-1,0,0>;
#endif
  constexpr inline compiler_type compiler;
}
namespace spy::detail
{
  template<compilers C, int M, int N, int P>
  inline constexpr compilers_info<C,M,N,P>::operator bool() const noexcept
  {
    return *this == spy::compiler;
  }
}
namespace spy
{
  constexpr inline auto  msvc_   = detail::msvc_t<-1,0,0>{};
  constexpr inline auto  intel_  = detail::intel_t<-1,0,0>{};
  constexpr inline auto  clang_  = detail::clang_t<-1,0,0>{};
  constexpr inline auto  gcc_    = detail::gcc_t<-1,0,0>{};
}
namespace spy::literal
{
  template<char ...c> constexpr auto operator"" _msvc()
  {
    return detail::literal_wrap<detail::msvc_t,c...>();
  }
  template<char ...c> constexpr auto operator"" _intel()
  {
    return detail::literal_wrap<detail::intel_t,c...>();
  }
  template<char ...c> constexpr auto operator"" _clang()
  {
    return detail::literal_wrap<detail::clang_t,c...>();
  }
  template<char ...c> constexpr auto operator"" _gcc()
  {
    return detail::literal_wrap<detail::gcc_t,c...>();
  }
}
#include <iosfwd>
namespace spy::detail
{
  template<int Short, int Integer, int Long, int Pointer>
  struct data_model_info
  {
    inline constexpr operator bool() const noexcept;
    template<int Short2, int Integer2, int Long2, int Pointer2>
    constexpr bool operator==(data_model_info<Short2, Integer2, Long2, Pointer2> const& ) const noexcept
    {
      return (Short==Short2) && (Integer == Integer2) && (Long == Long2) && (Pointer == Pointer2);
    }
  };
  template<int Short, int Integer, int Long, int Pointer>
  std::ostream& operator<<(std::ostream& os, data_model_info<Short, Integer, Long, Pointer> const&)
  {
          if constexpr(Pointer == 4 && Integer == 4) return os << "ILP32";
    else  if constexpr(Pointer == 4 && Integer == 2) return os << "LP32";
    else  if constexpr(Pointer == 8 && Long == 8 && Integer == 8 && Short == 8)  return os << "IntegerLP64";
    else  if constexpr(Pointer == 8 && Short == 8 && Integer == 8 && Short == 2)  return os << "ILP64";
    else  if constexpr(Pointer == 8 && Long == 4 && Integer == 8 && Short == 2)  return os << "LLP64";
    else  if constexpr(Pointer == 8 && Long == 8 && Integer == 4 && Short == 2)  return os << "LP64";
    else  return os << "Unknown data model";
  }
}
namespace spy
{
  using data_model_type = detail::data_model_info < sizeof(short), sizeof(int)
                                                  , sizeof(long), sizeof(void*)
                                                  >;
  constexpr inline data_model_type data_model;
}
namespace spy::detail
{
  template<int Short, int Integer, int Long, int Pointer>
  inline constexpr data_model_info<Short, Integer, Long, Pointer>::operator bool() const noexcept
  {
    return *this == spy::data_model;
  }
}
namespace spy
{
  constexpr inline auto ilp32_  = detail::data_model_info<2,4,sizeof(long),4>{};
  constexpr inline auto lp32_   = detail::data_model_info<2,2,sizeof(long),4>{};
  constexpr inline auto silp64_ = detail::data_model_info<8,8,8,8>{};
  constexpr inline auto ilp64_  = detail::data_model_info<2,8,8,8>{};
  constexpr inline auto llp64_  = detail::data_model_info<2,8,4,8>{};
  constexpr inline auto lp64_   = detail::data_model_info<2,4,8,8>{};
}
#include <cstddef>
#include <iosfwd>
namespace spy::detail
{
  enum class libC  { undefined_  = - 1, cloudabi_, uc_, vms_, zos_, gnu_ };
  template<libC Lib, int M, int N, int P> struct libc_info
  {
    static constexpr libC               vendor  = Lib;
    static constexpr version_id<M,N,P>  version = {};
    inline constexpr operator bool() const noexcept;
    template<libC C2>
    constexpr bool operator==(libc_info<C2,-1,0,0> const&) const noexcept
    {
      return C2 == vendor;
    }
    SPY_VERSION_COMPARISONS_OPERATOR(libC,libc_info)
  };
  template<libC C, int M, int N, int P>
  std::ostream& operator<<(std::ostream& os, libc_info<C, M, N, P> const& c)
  {
    if(c.vendor == libC::cloudabi_) return os << "CloudABI Standard C Library " << c.version;
    if(c.vendor == libC::uc_      ) return os << "uClibc Standard C Library "   << c.version;
    if(c.vendor == libC::vms_     ) return os << "VMS Standard C Library "      << c.version;
    if(c.vendor == libC::zos_     ) return os << "z/OS Standard C Library "    << c.version;
    if(c.vendor == libC::gnu_     ) return os << "GNU Standard C Library "     << c.version;
    return os << "Undefined Standard C Library";
  }
  template<int M, int N, int P> using cloudabi_t  = libc_info<libC::cloudabi_ ,M,N,P>;
  template<int M, int N, int P> using uc_t        = libc_info<libC::uc_ ,M,N,P>;
  template<int M, int N, int P> using vms_t       = libc_info<libC::vms_,M,N,P>;
  template<int M, int N, int P> using zos_t       = libc_info<libC::zos_,M,N,P>;
  template<int M, int N, int P> using gnu_t       = libc_info<libC::gnu_,M,N,P>;
}
namespace spy
{
#if defined(__cloudlibc__)
  #define SPY_LIBC_IS_CLOUDABI
  using libc_type = detail::cloudabi_t<__cloudlibc_major__,__cloudlibc_minor__,0>;
#elif defined(__GLIBC__)
  #define SPY_LIBC_IS_GNU
  using libc_type = detail::gnu_t<__GLIBC__, __GLIBC_MINOR__, 0>;
#elif defined(__GNU_LIBRARY__)
  #define SPY_LIBC_IS_GNU
  using libc_type = detail::gnu_t<__GNU_LIBRARY__, __GNU_LIBRARY_MINOR__, 0>;
#elif defined(__UCLIBC__)
  #define SPY_LIBC_IS_UCLIBC
  using libc_type = detail::uc_t<__UCLIBC_MAJOR__, __UCLIBC_MINOR__, __UCLIBC_SUBLEVEL__>;
#elif defined(__CRTL_VER)
  #define SPY_LIBC_IS_VMS
  #define SPY0  (__CRTL_VER/100)
  using libc_type = detail::vms_t<(SPY0/100000)%100, (SPY0/1000)%100, (SPY0)%100>;
  #undef SPY0
#elif defined(__LIBREL__)
  #define SPY_LIBC_IS_ZOS
  using libc_type = detail::zos_t < (__LIBREL__&0xF000000)>>24
                                  , (__LIBREL__&0xFF0000)>>16
                                  , (__LIBREL__&0xFFFF)
                                  >;
#else
  #define SPY_LIBC_IS_UNKNOWN
  using libc_type = detail::libc_info<detail::libC::undefined_,-1,0,0>;
#endif
  constexpr inline libc_type libc;
}
namespace spy::detail
{
  template<libC C, int M, int N, int P>
  inline constexpr libc_info<C,M,N,P>::operator bool() const noexcept
  {
    return *this == spy::libc;
  }
}
namespace spy
{
  constexpr inline auto  cloudabi_  = detail::cloudabi_t<-1,0,0>{};
  constexpr inline auto  uc_        = detail::uc_t<-1,0,0>{};
  constexpr inline auto  vms_       = detail::vms_t<-1,0,0>{};
  constexpr inline auto  zos_       = detail::zos_t<-1,0,0>{};
  constexpr inline auto  gnu_       = detail::gnu_t<-1,0,0>{};
}
namespace spy::literal
{
  template<char ...c> constexpr auto operator"" _cloud()
  {
    return detail::literal_wrap<detail::cloudabi_t,c...>();
  }
  template<char ...c> constexpr auto operator"" _uc()
  {
    return detail::literal_wrap<detail::uc_t,c...>();
  }
  template<char ...c> constexpr auto operator"" _vms()
  {
    return detail::literal_wrap<detail::vms_t,c...>();
  }
  template<char ...c> constexpr auto operator"" _zos()
  {
    return detail::literal_wrap<detail::zos_t,c...>();
  }
  template<char ...c> constexpr auto operator"" _gnu()
  {
    return detail::literal_wrap<detail::gnu_t,c...>();
  }
}
#include <cstddef>
#include <iosfwd>
namespace spy::detail
{
  enum class stdlib { undefined_  = - 1, libcpp_, gnucpp_ };
  template<stdlib Lib, int M, int N, int P> struct stdlib_info
  {
    static constexpr stdlib             vendor  = Lib;
    static constexpr version_id<M,N,P>  version = {};
    inline constexpr operator bool() const noexcept;
    template<stdlib C2>
    constexpr bool operator==(stdlib_info<C2,-1,0,0> const&) const noexcept
    {
      return C2 == vendor;
    }
    SPY_VERSION_COMPARISONS_OPERATOR(stdlib,stdlib_info)
  };
  template<stdlib SLib, int M, int N, int P>
  std::ostream& operator<<(std::ostream& os, stdlib_info<SLib, M, N, P> const&)
  {
    if(SLib == stdlib::libcpp_) return os << "libc++ Standard C++ Library";
    if(SLib == stdlib::gnucpp_) return os << "GNU Standard C++ Library";
    return os << "Undefined Standard C++ Library";
  }
  template<int M, int N, int P> using libcpp_t = stdlib_info<stdlib::libcpp_,M,N,P>;
  template<int M, int N, int P> using gnucpp_t = stdlib_info<stdlib::gnucpp_,M,N,P>;
}
namespace spy
{
#if defined(_LIBCPP_VERSION)
  #define SPY_STDLIB_IS_LIBCPP
  using stdlib_type = detail::libcpp_t<(_LIBCPP_VERSION/1000)%10,0,_LIBCPP_VERSION%1000>;
#elif defined(__GLIBCXX__)
  #define SPY_STDLIB_IS_GLIBCXX
  #define SPY0 (__GLIBCXX__/100)
  using stdlib_type = detail::gnucpp_t<(SPY0/100)%10000, SPY0%100, __GLIBCXX__%100>;
  #undef SPY0
#else
  #define SPY_STDLIB_IS_UNKNOWN
  using stdlib_type = detail::stdlib_info<detail::stdlib::undefined_,-1,0,0>;
#endif
  constexpr inline stdlib_type stdlib;
}
namespace spy::detail
{
  template<stdlib SLib, int M, int N, int P>
  inline constexpr stdlib_info<SLib,M,N,P>::operator bool() const noexcept
  {
    return *this == spy::stdlib;
  }
}
namespace spy
{
  constexpr inline auto  libcpp_  = detail::libcpp_t<-1,0,0>{};
  constexpr inline auto  gnucpp_  = detail::gnucpp_t<-1,0,0>{};
}
namespace spy::literal
{
  template<char ...c> constexpr auto operator"" _libcpp()
  {
    return detail::literal_wrap<detail::libcpp_t,c...>();
  }
  template<char ...c> constexpr auto operator"" _gnucpp()
  {
    return detail::literal_wrap<detail::gnucpp_t,c...>();
  }
}
#include <ostream>
#if !defined(SPY_SIMD_DETECTED) && defined(__AVX512F__)
#  define SPY_SIMD_IS_X86_AVX512
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::avx512_
#if defined(__AVX512BW__)
#  define SPY_SIMD_IS_X86_AVX512_BW
#endif
#if defined(__AVX512CD__)
#  define SPY_SIMD_IS_X86_AVX512_CD
#endif
#if defined(__AVX512DQ__)
#  define SPY_SIMD_IS_X86_AVX512_DQ
#endif
#if defined(__AVX512ER__)
#  define SPY_SIMD_IS_X86_AVX512_ER
#endif
#if defined(__AVX512IFMA__)
#  define SPY_SIMD_IS_X86_AVX512_IFMA
#endif
#if defined(__AVX512PF__)
#  define SPY_SIMD_IS_X86_AVX512_PF
#endif
#if defined(__AVX512VL__)
#  define SPY_SIMD_IS_X86_AVX512_VL
#endif
#if defined(__AVX512VPOPCNTDQ__)
#  define SPY_SIMD_IS_X86_AVX512_POPCNTDQ
#endif
#if defined(__AVX5124FMAPS__)
#  define SPY_SIMD_IS_X86_AVX512_4FMAPS
#endif
#if defined(__AVX5124VNNIW__)
#  define SPY_SIMD_IS_X86_AVX512_VNNIW
#endif
#if defined(__AVX512VBMI__)
#  define SPY_SIMD_IS_X86_AVX512_VBMI
#endif
#if defined(__AVX512BF16__)
#  define SPY_SIMD_IS_X86_AVX512_BF16
#endif
#if defined(__AVX512BITALG__)
#  define SPY_SIMD_IS_X86_AVX512_BITALG
#endif
#if defined(__AVX512VBMI2__)
#  define SPY_SIMD_IS_X86_AVX512_VBMI2
#endif
#if defined(__AVX512VNNI__)
#  define SPY_SIMD_IS_X86_AVX512_VNNI
#endif
#if defined(__AVX512VP2INTERSECT__)
#  define SPY_SIMD_IS_X86_AVX512_VP2INTERSECT
#endif
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__AVX2__)
#  define SPY_SIMD_IS_X86_AVX2
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::avx2_
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__AVX__)
#  define SPY_SIMD_IS_X86_AVX
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::avx_
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__SSE4_2__)
#  define SPY_SIMD_IS_X86_SSE4_2
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::sse42_
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__SSE4_1__)
#  define SPY_SIMD_IS_X86_SSE4_1
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::sse41_
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__SSSE3__)
#  define SPY_SIMD_IS_X86_SSSE3
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::ssse3_
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__SSE3__)
#  define SPY_SIMD_IS_X86_SSE3
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::sse3_
#endif
#if !defined(SPY_SIMD_DETECTED) && (defined(__SSE2__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2))
#  define SPY_SIMD_IS_X86_SSE2
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::sse2_
#endif
#if !defined(SPY_SIMD_DETECTED) && (defined(__SSE__) || defined(_M_IX86_FP))
#  define SPY_SIMD_IS_X86_SSE
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::sse1_
#endif
#if defined(SPY_SIMD_DETECTED) && !defined(SPY_SIMD_VENDOR)
#  define SPY_SIMD_IS_X86
#  define SPY_SIMD_VENDOR ::spy::detail::simd_isa::x86_
#endif
namespace spy::supports
{
#if defined(__SIZEOF_INT128__)
#  define SPY_SIMD_SUPPORTS_INT128
  constexpr inline auto int128_ = true;
#else
  constexpr inline auto int128_ = false;
#endif
#if defined(__FMA__)
#  define SPY_SIMD_SUPPORTS_FMA
  constexpr inline auto fma_ = true;
#else
  constexpr inline auto fma_ = false;
#endif
#if defined(__FMA4__)
#  define SPY_SIMD_SUPPORTS_FMA4
  constexpr inline auto fma4_ = true;
#else
  constexpr inline auto fma4_ = false;
#endif
#if defined(__XOP__)
#  define SPY_SIMD_SUPPORTS_XOP
  constexpr inline auto xop_ = true;
#else
  constexpr inline auto xop_ = false;
#endif
namespace avx512
{
#if defined(__AVX512BW__)
#  define SPY_SIMD_IS_X86_AVX512_BW
  constexpr inline auto bw_ = true;
#else
  constexpr inline auto bw_ = false;
#endif
#if defined(__AVX512CD__)
#  define SPY_SIMD_IS_X86_AVX512_CD
  constexpr inline auto cd_ = true;
#else
  constexpr inline auto cd_ = false;
#endif
#if defined(__AVX512DQ__)
#  define SPY_SIMD_IS_X86_AVX512_DQ
  constexpr inline auto dq_ = true;
#else
  constexpr inline auto dq_ = false;
#endif
#if defined(__AVX512ER__)
#  define SPY_SIMD_IS_X86_AVX512_ER
  constexpr inline auto er_ = true;
#else
  constexpr inline auto er_ = false;
#endif
#if defined(__AVX512IFMA__)
#  define SPY_SIMD_IS_X86_AVX512_IFMA
  constexpr inline auto ifma_ = true;
#else
  constexpr inline auto ifma_ = false;
#endif
#if defined(__AVX512PF__)
#  define SPY_SIMD_IS_X86_AVX512_PF
  constexpr inline auto pf_ = true;
#else
  constexpr inline auto pf_ = false;
#endif
#if defined(__AVX512VL__)
#  define SPY_SIMD_IS_X86_AVX512_VL
  constexpr inline auto vl_ = true;
#else
  constexpr inline auto vl_ = false;
#endif
#if defined(__AVX512VPOPCNTDQ__)
#  define SPY_SIMD_IS_X86_AVX512_POPCNTDQ
  constexpr inline auto popcntdq_ = true;
#else
  constexpr inline auto popcntdq_ = false;
#endif
#if defined(__AVX5124FMAPS__)
#  define SPY_SIMD_IS_X86_AVX512_4FMAPS
  constexpr inline auto _4fmaps_ = true;
#else
  constexpr inline auto _4fmaps_ = false;
#endif
#if defined(__AVX5124VNNIW__)
#  define SPY_SIMD_IS_X86_AVX512_VNNIW
  constexpr inline auto vnniw_ = true;
#else
  constexpr inline auto vnniw_ = false;
#endif
#if defined(__AVX512VBMI__)
#  define SPY_SIMD_IS_X86_AVX512_VBMI
  constexpr inline auto vbmi_ = true;
#else
  constexpr inline auto vbmi_ = false;
#endif
#if defined(__AVX512BF16__)
#  define SPY_SIMD_IS_X86_AVX512_BF16
  constexpr inline auto bf16_ = true;
#else
  constexpr inline auto bf16_ = false;
#endif
#if defined(__AVX512BITALG__)
#  define SPY_SIMD_IS_X86_AVX512_BITALG
  constexpr inline auto bitalg_ = true;
#else
  constexpr inline auto bitalg_ = false;
#endif
#if defined(__AVX512VBMI2__)
#  define SPY_SIMD_IS_X86_AVX512_VBMI2
  constexpr inline auto vbmi2_ = true;
#else
  constexpr inline auto vbmi2_ = false;
#endif
#if defined(__AVX512VNNI__)
#  define SPY_SIMD_IS_X86_AVX512_VNNI
  constexpr inline auto vnni_ = true;
#else
  constexpr inline auto vnni_ = false;
#endif
#if defined(__AVX512VP2INTERSECT__)
#  define SPY_SIMD_IS_X86_AVX512_VP2INTERSECT
  constexpr inline auto vpintersect_ = true;
#else
  constexpr inline auto vpintersect_ = false;
#endif
}
}
#if !defined(SPY_SIMD_DETECTED) && defined(__aarch64__)
#  define SPY_SIMD_IS_ARM_ASIMD
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::asimd_
#endif
#if !defined(SPY_SIMD_DETECTED) && ((defined(__ARM_NEON__) || defined(_M_ARM)) && (__ARM_ARCH == 7))
#  define SPY_SIMD_IS_ARM_NEON
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::neon_
#endif
#if defined(SPY_SIMD_DETECTED) && !defined(SPY_SIMD_VENDOR)
#  define SPY_SIMD_IS_ARM
#  define SPY_SIMD_VENDOR ::spy::detail::simd_isa::arm_
#endif
#if !defined(SPY_SIMD_DETECTED) && defined(__VSX__)
#  define SPY_SIMD_IS_PPC_VSX
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::vsx_
#endif
#if !defined(SPY_SIMD_DETECTED) && (defined(__ALTIVEC__) || defined(__VEC__))
#  define SPY_SIMD_IS_PPC_VMX
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::vmx_
#endif
#if defined(SPY_SIMD_DETECTED) && !defined(SPY_SIMD_VENDOR)
#  define SPY_SIMD_IS_PPC
#  define SPY_SIMD_VENDOR ::spy::detail::simd_isa::ppc_
#endif
namespace spy::detail
{
  enum class simd_isa { undefined_ = -1, x86_ = 1000, ppc_ = 2000, arm_ = 3000 };
  enum class simd_version { undefined_ = -1
                          , sse1_   = 1110, sse2_  = 1120, sse3_ = 1130, ssse3_ = 1131
                          , sse41_  = 1141, sse42_ = 1142, avx_  = 1201, avx2_  = 1202
                          , avx512_ = 1300
                          , vmx_    = 2001, vsx_   = 2002
                          , neon_   = 3001, asimd_ = 3002
                          };
  template<simd_isa InsSetArch = simd_isa::undefined_, simd_version Version = simd_version::undefined_>
  struct simd_info
  {
    static constexpr auto isa     = InsSetArch;
    static constexpr auto version = Version;
    friend std::ostream& operator<<(std::ostream& os, simd_info const&)
    {
            if constexpr ( Version == simd_version::sse1_   ) os << "X86 SSE";
      else  if constexpr ( Version == simd_version::sse2_   ) os << "X86 SSE2";
      else  if constexpr ( Version == simd_version::sse3_   ) os << "X86 SSE3";
      else  if constexpr ( Version == simd_version::ssse3_  ) os << "X86 SSSE3";
      else  if constexpr ( Version == simd_version::sse41_  ) os << "X86 SSE4.1";
      else  if constexpr ( Version == simd_version::sse42_  ) os << "X86 SSE4.2";
      else  if constexpr ( Version == simd_version::avx_    ) os << "X86 AVX";
      else  if constexpr ( Version == simd_version::avx2_   ) os << "X86 AVX2";
      else  if constexpr ( Version == simd_version::avx512_ ) os << "X86 AVX512";
      else  if constexpr ( Version == simd_version::vmx_    ) os << "PPC VMX";
      else  if constexpr ( Version == simd_version::vsx_    ) os << "PPC VSX";
      else  if constexpr ( Version == simd_version::neon_   ) os << "ARM NEON";
      else  if constexpr ( Version == simd_version::asimd_  ) os << "ARM ASIMD";
      else return os << "Undefined SIMD instructions set";
      if constexpr (spy::supports::fma_)     os << " (with FMA3 support)";
      if constexpr (spy::supports::fma4_)    os << " (with FMA4 support)";
      if constexpr (spy::supports::xop_)     os << " (with XOP support)";
      return os;
    }
    template<simd_isa OInsSetArch>
    constexpr bool operator==(simd_info<OInsSetArch> const&) const noexcept { return OInsSetArch == InsSetArch; }
    template<simd_isa OInsSetArch>
    constexpr bool operator!=(simd_info<OInsSetArch> const&) const noexcept { return OInsSetArch != InsSetArch; }
    template<simd_isa OInsSetArch, simd_version OVersion>
    constexpr bool operator==(simd_info<OInsSetArch,OVersion> const&) const noexcept
    {
      return (Version == OVersion) && (OInsSetArch == InsSetArch);
    }
    template<simd_isa OInsSetArch, simd_version OVersion>
    constexpr bool operator!=(simd_info<OInsSetArch,OVersion> const&) const noexcept
    {
      return (Version != OVersion) || (OInsSetArch != InsSetArch);
    }
    template<simd_isa OInsSetArch, simd_version OVersion>
    constexpr bool operator<(simd_info<OInsSetArch,OVersion> const&) const noexcept
    {
      return (Version < OVersion) && (OInsSetArch == InsSetArch);
    }
    template<simd_isa OInsSetArch, simd_version OVersion>
    constexpr bool operator>(simd_info<OInsSetArch,OVersion> const&) const noexcept
    {
      return (Version > OVersion) && (OInsSetArch == InsSetArch);
    }
    template<simd_isa OInsSetArch, simd_version OVersion>
    constexpr bool operator<=(simd_info<OInsSetArch,OVersion> const&) const noexcept
    {
      return (Version <= OVersion) && (OInsSetArch == InsSetArch);
    }
    template<simd_isa OInsSetArch, simd_version OVersion>
    constexpr bool operator>=(simd_info<OInsSetArch,OVersion> const&) const noexcept
    {
      return (Version >= OVersion) && (OInsSetArch == InsSetArch);
    }
  };
}
namespace spy
{
  #if defined(SPY_SIMD_DETECTED)
  constexpr inline auto simd_instruction_set = detail::simd_info<SPY_SIMD_VENDOR,SPY_SIMD_DETECTED>{};
  #else
  constexpr inline auto simd_instruction_set = detail::simd_info<>{};
  #endif
  constexpr inline auto undefined_simd_ = detail::simd_info<>{};
  template<detail::simd_version V = detail::simd_version::undefined_>
  using x86_simd_info = detail::simd_info<detail::simd_isa::x86_,V>;
  constexpr inline auto x86_simd_ = x86_simd_info<>{};
  constexpr inline auto sse1_     = x86_simd_info<detail::simd_version::sse1_   >{};
  constexpr inline auto sse2_     = x86_simd_info<detail::simd_version::sse2_   >{};
  constexpr inline auto sse3_     = x86_simd_info<detail::simd_version::sse3_   >{};
  constexpr inline auto ssse3_    = x86_simd_info<detail::simd_version::ssse3_  >{};
  constexpr inline auto sse41_    = x86_simd_info<detail::simd_version::sse41_  >{};
  constexpr inline auto sse42_    = x86_simd_info<detail::simd_version::sse42_  >{};
  constexpr inline auto avx_      = x86_simd_info<detail::simd_version::avx_    >{};
  constexpr inline auto avx2_     = x86_simd_info<detail::simd_version::avx2_   >{};
  constexpr inline auto avx512_   = x86_simd_info<detail::simd_version::avx512_ >{};
  template<detail::simd_version V = detail::simd_version::undefined_>
  using ppc_simd_info = detail::simd_info<detail::simd_isa::ppc_,V>;
  constexpr inline auto ppc_simd_ = ppc_simd_info<>{};
  constexpr inline auto vmx_      = ppc_simd_info<detail::simd_version::vmx_>{};
  constexpr inline auto vsx_      = ppc_simd_info<detail::simd_version::vsx_>{};
  template<detail::simd_version V = detail::simd_version::undefined_>
  using arm_simd_info = detail::simd_info<detail::simd_isa::arm_,V>;
  constexpr inline auto arm_simd_ = arm_simd_info<>{};
  constexpr inline auto neon_     = arm_simd_info<detail::simd_version::neon_ >{};
  constexpr inline auto asimd_    = arm_simd_info<detail::simd_version::asimd_>{};
}
#include <iosfwd>
#if defined(__APPLE__) || defined(__APPLE_CC__) || defined(macintosh)
#  include <AvailabilityMacros.h>
#endif
namespace spy::detail
{
  enum class systems  { undefined_  = - 1
                      , android_, bsd_, cygwin_, ios_, linux_, macos_, unix_, windows_
                      };
  template<systems OpSys> struct os_info
  {
    static constexpr systems            vendor  = OpSys;
    inline constexpr operator bool() const noexcept;
    template<systems C2>
    constexpr bool operator==(os_info<C2> const&) const noexcept
    {
      return C2 == vendor;
    }
  };
  template<systems OpSys>
  std::ostream& operator<<(std::ostream& os, os_info<OpSys> const&)
  {
    if(OpSys == systems::android_ ) return os << "Android";
    if(OpSys == systems::bsd_     ) return os << "BSD";
    if(OpSys == systems::cygwin_  ) return os << "Cygwin";
    if(OpSys == systems::ios_     ) return os << "iOs";
    if(OpSys == systems::linux_   ) return os << "Linux";
    if(OpSys == systems::macos_   ) return os << "MacOs";
    if(OpSys == systems::unix_    ) return os << "UNIX";
    if(OpSys == systems::windows_ ) return os << "Windows";
    return os << "Undefined Operating System";
  }
}
namespace spy
{
#if defined(__ANDROID__)
  #define SPY_OS_IS_ANDROID
  using os_type = detail::os_info<detail::systems::android_>;
#elif defined(BSD) || defined(_SYSTYPE_BSD)
  #define SPY_OS_IS_BSD
  using os_type = detail::os_info<detail::systems::bsd_>;
#elif defined(__CYGWIN__)
  #define SPY_OS_IS_CYGWIN
  using os_type = detail::os_info<detail::systems::cygwin_>;
#elif defined(__APPLE__) && defined(__MACH__) && defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
  #define SPY_OS_IS_IOS
  using os_type = detail::os_info<detail::systems::ios_>;
#elif defined(linux) || defined(__linux)
  #define SPY_OS_IS_LINUX
  using os_type = detail::os_info<detail::systems::linux_>;
#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
  #define SPY_OS_IS_MACOS
  using os_type = detail::os_info<detail::systems::macos_>;
#elif defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
  #define SPY_OS_IS_UNIX
  using os_type = detail::os_info<detail::systems::unix_>;
#elif defined(_WIN32) || defined(_WIN64) ||  defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
  #define SPY_OS_IS_WINDOWS
  using os_type = detail::os_info<detail::systems::windows_>;
#else
  #define SPY_OS_IS_UNKNOWN
  using os_type = detail::os_info<detail::systems::undefined_>;
#endif
  constexpr inline os_type operating_system;
}
namespace spy::detail
{
  template<systems OS>
  inline constexpr os_info<OS>::operator bool() const noexcept
  {
    return *this == spy::operating_system;
  }
}
namespace spy
{
  constexpr inline auto android_  = detail::os_info<detail::systems::android_>{};
  constexpr inline auto bsd_      = detail::os_info<detail::systems::bsd_>{};
  constexpr inline auto cygwin_   = detail::os_info<detail::systems::cygwin_>{};
  constexpr inline auto ios_      = detail::os_info<detail::systems::ios_>{};
  constexpr inline auto linux_    = detail::os_info<detail::systems::linux_>{};
  constexpr inline auto macos_    = detail::os_info<detail::systems::macos_>{};
  constexpr inline auto unix_     = detail::os_info<detail::systems::unix_>{};
  constexpr inline auto windows_  = detail::os_info<detail::systems::windows_>{};
}
namespace spy::supports
{
#if(MAC_OS_X_VERSION_MIN_REQUIRED >= 1090) || (_POSIX_C_SOURCE >= 200112L) || (_XOPEN_SOURCE >= 600)
#define SPY_SUPPORTS_POSIX
  constexpr inline auto posix_ = true;
#else
  constexpr inline auto posix_ = false;
#endif
}
#endif
