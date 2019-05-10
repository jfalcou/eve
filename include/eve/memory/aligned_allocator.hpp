//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MEMORY_ALIGNED_ALLOCATOR_HPP_INCLUDED
#define EVE_MEMORY_ALIGNED_ALLOCATOR_HPP_INCLUDED

#include <eve/memory/aligned_alloc.hpp>
#include <eve/memory/aligned_dealloc.hpp>
#include <eve/memory/power_of_2.hpp>
#include <cstddef>

namespace eve
{
  template<typename T, std::size_t Alignment>
  struct aligned_allocator
  {
    static_assert(is_power_of_2(Alignment), "[eve] Alignment must be a power of 2");

    using value_type = T;

    template<typename U>
    struct rebind
    {
      using other = aligned_allocator<U, Alignment>;
    };

    aligned_allocator() noexcept {}
    template<typename U>
    aligned_allocator(aligned_allocator<U, Alignment> const &) noexcept
    {
    }

    value_type *allocate(std::size_t n)
    {
      auto ptr = aligned_alloc<Alignment>(n * sizeof(value_type));
      return static_cast<value_type *>(ptr.get());
    }

    void deallocate(value_type *p, std::size_t) noexcept
    {
      aligned_dealloc(as_aligned<Alignment>(p));
    }
  };

  template<typename T, typename U, std::size_t A, std::size_t B>
  bool operator==(aligned_allocator<T, A> const &, aligned_allocator<U, B> const &) noexcept
  {
    return (A == B) && std::is_same_v<T, U>;
  }

  template<typename T, typename U, std::size_t A, std::size_t B>
  bool operator!=(aligned_allocator<T, A> const &, aligned_allocator<U, B> const &) noexcept
  {
    return A != B || !std::is_same_v<T, U>;
  }
}

#endif
