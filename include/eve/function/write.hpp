//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/memory/soa_ptr.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup memory
  //! @{
  //! @var write
  //!
  //! @brief Callable object writing single value from memory
  //!
  //! **Required header:** `#include <eve/function/write.hpp>`
  //!
  //! `operator*` based interface used in the standard has notorious issues with proxy references.
  //! To prevent those issues when dealing with complex, potentially SIMD-aware iterators, `eve::write`
  //! is to be used.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Performs a single write to memory                          |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template<typename Ptr, scalar_value V> auto operator()(Ptr p, V v) const noexcept
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //! `ptr`: Memory to write to.
  //! `v`  : [scalar value](@ref eve::scalar_value) to write.
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(write_, write);

  namespace detail
  {
    template<typename Ptr, scalar_value V>
    EVE_FORCEINLINE void write_(EVE_SUPPORTS(cpu_), Ptr ptr, V v) noexcept
    requires requires(Ptr p, V v) { *p = v; }
    {
      *ptr = v;
    }

    template <scalar_value V, typename ... Ptrs>
    EVE_FORCEINLINE void write_(EVE_SUPPORTS(cpu_), soa_ptr<Ptrs...> ptr, V v) noexcept
    {
      kumi::for_each(write, ptr, v);
    }
  }
}
