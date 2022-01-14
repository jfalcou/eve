//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/soa_ptr.hpp>

#include <concepts>
#include <iterator>

namespace eve
{
  //================================================================================================
  //! @addtogroup memory
  //! @{
  //! @var unalign
  //!
  //! @brief Callable object for computing an unaligned version of a relaxed iterator.
  //!
  //! **Required header:** `#include <eve/function/unalign.hpp>`
  //!
  //!   For a std::iterator returns itself.
  //!   For an aligned_ptr returns raw pointer.
  //!   algo uses this as a customization point for relaxed iterator/iterator.
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(unalign_, unalign);

  //================================================================================================
  //! @addtogroup memory
  //! @{
  //!  @typedef unaligned_t
  //!
  //!  @tparam T Type to process
  //!
  //!  @brief
  //!
  //! **Required header:** `#include <eve/function/unalign.hpp>`
  //!
  //!   @code{.cpp}
  //!   template <typename T>
  //!   using unaligned_t = decltype(unalign(std::declval<T>()));
  //!   @endcode
  //! @}
  //================================================================================================

  template <typename T>
  using unaligned_t = decltype(unalign(std::declval<T>()));

  namespace detail
  {

    template <std::contiguous_iterator I>
    EVE_FORCEINLINE I unalign_(EVE_SUPPORTS(cpu_), I i) noexcept { return i; }

    template <typename T, typename N>
    EVE_FORCEINLINE T* unalign_(EVE_SUPPORTS(cpu_), aligned_ptr<T, N> p) noexcept
    {
      return p.get();
    }

    template <typename ...Ptrs>
    EVE_FORCEINLINE auto unalign_(EVE_SUPPORTS(cpu_), soa_ptr<Ptrs...> p) noexcept
    {
      return soa_ptr<unaligned_t<Ptrs>...>{ kumi::map(unalign, p) };
    }
  }
}
