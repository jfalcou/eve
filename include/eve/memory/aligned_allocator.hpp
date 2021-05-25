//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/memory/aligned_alloc.hpp>
#include <eve/memory/aligned_dealloc.hpp>
#include <eve/memory/power_of_2.hpp>
#include <eve/memory/align.hpp>
#include <cstddef>

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
  //! @tparam T         Type to allocates
  //! @tparam Alignment Alignment constraint to uphold. Default value is computed to be compatible
  //!                   with current SIMD ABI requirements. If `Alignment` is not a power of two,
  //!                   the instantiation is ill-formed.
  //================================================================================================
  template< typename T
          , std::size_t Alignment = sizeof(T) * expected_cardinal_v<T>
          >
#if !defined(EVE_DOXYGEN_INVOKED)
  requires(is_power_of_2(Alignment))
#endif
  struct aligned_allocator
  {
    //! type to allocates, i.e `T`
    using value_type = T;

    //! Convert an aligned_allocator type to another
    template<typename U> struct rebind
    {
      using other = aligned_allocator<U, Alignment>;
    };

    //! @brief Default constructor
    aligned_allocator() noexcept {}

    //! @brief Copy constructor
    template<typename U>
    aligned_allocator(aligned_allocator<U, Alignment> const &) noexcept
    {
    }

    //! @brief Allocates aligned, uninitialized storage for `n` elements of type `T`.
    value_type *allocate(std::size_t n)
    {
      auto ptr = aligned_alloc<Alignment>( align(n * sizeof(value_type), over{Alignment}) );
      return static_cast<value_type *>(ptr.get());
    }

    //! @brief Deallocates aligned storage
    void deallocate(value_type *p, std::size_t) noexcept
    {
      aligned_dealloc(eve::as_aligned<Alignment>(p));
    }
  };
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @relates eve::aligned_allocator
  //! @brief Compares aligned_allocators for equality of types and alignment constraints.
  //================================================================================================
  template<typename T, typename U, std::size_t A, std::size_t B>
  bool operator==(aligned_allocator<T, A> const &, aligned_allocator<U, B> const &) noexcept
  {
    return (A == B) && std::is_same_v<T, U>;
  }

  //================================================================================================
  //! @relates eve::aligned_allocator
  //! @brief Compares aligned_allocators for inequality of types or alignment constraints.
  //================================================================================================
  template<typename T, typename U, std::size_t A, std::size_t B>
  bool operator!=(aligned_allocator<T, A> const &, aligned_allocator<U, B> const &) noexcept
  {
    return A != B || !std::is_same_v<T, U>;
  }
}
