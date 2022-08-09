//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/implementation.hpp>
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
//! **Required header:** `#include <eve/module/core.hpp>`
//!
//! `operator*` based interface used in the standard has notorious issues with proxy references.
//! To prevent those issues when dealing with complex, potentially SIMD-aware iterators,
//! `eve::write` is to be used.
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
//!  template<typename Ptr, scalar_value V> auto operator()(V v,Ptr p) const noexcept
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!
//! **Parameters**
//!
//! `v`  : [scalar value](@ref eve::scalar_value) to write.
//! `ptr`: Memory to write to.
//!
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(write_, write);

namespace detail
{
  template<typename Ptr, scalar_value V>
  EVE_FORCEINLINE void write_(EVE_SUPPORTS(cpu_), V v, Ptr ptr) noexcept requires
      requires(Ptr p, V v)
  {
    *p = v;
  }
  {
    *ptr = v;
  }

  template<scalar_value V, typename... Ptrs>
  EVE_FORCEINLINE void write_(EVE_SUPPORTS(cpu_), V v, soa_ptr<Ptrs...> ptr) noexcept
  {
    kumi::for_each(write, v, ptr);
  }
}
}
