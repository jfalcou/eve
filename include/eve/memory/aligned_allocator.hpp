//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/memory/align.hpp>
#include <eve/detail/spy.hpp>
#include <cstddef>
#include <bit>

#if defined(SPY_COMPILER_IS_MSVC)
#include <malloc.h>
#endif

namespace eve
{
  //================================================================================================
  //! @addtogroup memory
  //! @{
  //================================================================================================
  //! @brief  Standard-compliant allocator handling the allocation and deallocation of segment of
  //!         aligned memory.
  //!
  //! **Required header:** `#include <eve/memory/aligned_allocator.hpp>`
  //!
  //! By default, allocation will be aligned on current architecture's SIMD compatible
  //! alignment but can be specified otherwise.
  //!
  //! aligned_allocator is designed ot be used through
  //! [std::allocator_traits](https://en.cppreference.com/w/cpp/memory/allocator_traits), so it
  //! provides the minimal amount of members and members types.
  //!
  //! @tparam T     Type to allocates
  //! @tparam Lanes Alignment constraint to uphold. Default value is computed to be compatible with
  //!               current SIMD ABI requirements.
  //================================================================================================
  template< typename T
          , typename Lanes = expected_cardinal_t<T>
          >
  struct aligned_allocator
  {
    //! type to allocates, i.e `T`
    using value_type = T;

    //! Return the value of the alignment constraint
    static constexpr auto alignment() noexcept { return Lanes::value * sizeof(T); }

    //! Convert an aligned_allocator type to another
    template<typename U> struct rebind
    {
      using other = aligned_allocator<U, Lanes>;
    };

    //! @brief Default constructor
    aligned_allocator() noexcept {}

    //! @brief Copy constructor
    template<typename U>
    aligned_allocator(aligned_allocator<U, Lanes> const &) noexcept
    {
    }

    //! @brief Allocates aligned, uninitialized storage for `n` elements of type `T`.
    value_type *allocate(std::size_t n)
    {
      auto nbelem = align(n * sizeof(value_type), over{alignment()});

      #if defined(SPY_COMPILER_IS_MSVC)
      void *result = _aligned_malloc(nbelem,alignment());
      #else
      void *result = std::aligned_alloc(alignment(), nbelem);
      #endif

      return static_cast<value_type*>(result);
    }

    //! @brief Deallocates aligned storage
    void deallocate(value_type *p, std::size_t) noexcept
    {
      std::free((void *)p);
    }
  };
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @relates eve::aligned_allocator
  //! @brief Compares aligned_allocators for equality of types and alignment constraints.
  //================================================================================================
  template<typename T, typename U, typename A, typename B>
  bool operator==(aligned_allocator<T, A> const &, aligned_allocator<U, B> const &) noexcept
  {
    return std::is_same_v<A, B> && std::is_same_v<T, U>;
  }

  //================================================================================================
  //! @relates eve::aligned_allocator
  //! @brief Compares aligned_allocators for inequality of types or alignment constraints.
  //================================================================================================
  template<typename T, typename U, typename A, typename B>
  bool operator!=(aligned_allocator<T, A> const &, aligned_allocator<U, B> const &) noexcept
  {
    return !std::is_same_v<A, B> || !std::is_same_v<T, U>;
  }
}
