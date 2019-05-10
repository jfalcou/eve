//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_PLATFORM_HPP_INCLUDED
#define EVE_PLATFORM_HPP_INCLUDED

#include <eve/detail/compiler.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/os.hpp>

namespace eve
{
  enum class compilers  { none_, clang_, gcc_, intel_, msvc_ };
  enum class systems    { none_, linux_, macos_, unix_, windows_ };

  struct platform
  {
#if defined(EVE_COMP_IS_CLANG)
    static constexpr compilers compiler = compilers::clang_;
#elif defined(EVE_COMP_IS_GNUC)
    static constexpr compilers compiler = compilers::gcc_;
#elif defined(EVE_COMP_IS_INTEL)
    static constexpr compilers compiler = compilers::intel_;
#elif defined(EVE_COMP_IS_MSVC)
    static constexpr compilers compiler = compilers::msvc_;
#else
    static constexpr compilers compiler = compilers::none_;
#endif

#if defined(EVE_OS_USE_POSIX)
    static constexpr bool is_posix_compliant = true;
#else
    static constexpr bool is_posix_compliant = false;
#endif

#if defined(EVE_OS_IS_LINUX)
    static constexpr systems os = systems::linux_;
#elif defined(EVE_OS_IS_MACOS)
    static constexpr systems os = systems::macos_;
#elif defined(EVE_OS_IS_UNIX)
    static constexpr systems os = systems::unix_;
#elif defined(EVE_OS_IS_WINDOWS)
    static constexpr systems os = systems::windows_;
#else
    static constexpr systems os = systems::none_;
#endif

    static constexpr bool supports_32bits_addressing = sizeof(void*) == 4;
    static constexpr bool supports_64bits_addressing = sizeof(void*) == 8;

#if defined(EVE_NO_NANS)
    static constexpr bool supports_nans = false;
#else
    static constexpr bool supports_nans = true;
#endif

#if defined(EVE_NO_INFINITIES)
    static constexpr bool supports_infinites = false;
#else
    static constexpr bool supports_infinites = true;
#endif

    static constexpr bool supports_invalids = supports_infinites && supports_nans;

#if defined(EVE_NO_MINUSZERO)
    static constexpr bool supports_negative_zero = false;
#else
    static constexpr bool supports_negative_zero = true;
#endif

#if defined(EVE_NO_DENORMALS)
    static constexpr bool supports_denormals = false;
#else
    static constexpr bool supports_denormals = true;
#endif
  };
}

#endif
