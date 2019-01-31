//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MEMORY_ALIGNED_ALLOC_HPP_INCLUDED
#define EVE_MEMORY_ALIGNED_ALLOC_HPP_INCLUDED

#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/power_of_2.hpp>
#include <eve/memory/align.hpp>
#include <eve/detail/compiler.hpp>
#include <eve/detail/os.hpp>
#include <algorithm>
#include <cstdint>

namespace eve
{
  template<std::size_t Alignment>
  aligned_ptr<void, Alignment> aligned_alloc(std::size_t nbelem)
  {
    static_assert(is_power_of_2(Alignment), "[eve] Alignment must be a power of 2");

    void *result = nullptr;

#if defined(EVE_OS_USE_POSIX) || defined(EVE_OS_IS_MACOS)
    if(::posix_memalign((void **)&result, std::max(Alignment, sizeof(void *)), nbelem))
      result = nullptr;
#elif defined(EVE_COMP_IS_MSVC)
    result = ::_aligned_malloc(nbelem, Alignment);
#else
    constexpr auto alignment = std::max(Alignment, sizeof(void *));
    std::size_t    n         = nbelem + alignment - sizeof(void *);

    void *p = std::malloc(sizeof(void *) + n);

    if(p)
    {
      void *r                        = static_cast<char *>(p) + sizeof(void *);
      r                              = align(r, over{alignment});
      *(static_cast<void **>(r) - 1) = p;
      result                         = r;
    }
#endif

    return {result};
  }
}

#endif
