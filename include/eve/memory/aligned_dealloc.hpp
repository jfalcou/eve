//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MEMORY_ALIGNED_DEALLOC_HPP_INCLUDED
#define EVE_MEMORY_ALIGNED_DEALLOC_HPP_INCLUDED

#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/power_of_2.hpp>
#include <eve/detail/spy.hpp>
#include <cstdint>

namespace eve
{
  template<typename T, std::size_t Alignment>
  void aligned_dealloc(aligned_ptr<T, Alignment> const &ptr)
  {
#if defined(SPY_SUPPORTS_POSIX) || defined(SPY_OS_IS_MACOS)
    ::free((void *)ptr.get());
#elif defined(SPY_COMPILER_IS_MSVC)
    ::_aligned_free(ptr.get());
#else
    if(ptr) ::free(*((void **)(ptr.get()) - 1));
#endif
  }
}

#endif
