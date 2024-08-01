//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/concept/value.hpp>
#include <eve/traits/overload.hpp>
#include <eve/memory/soa_ptr.hpp>

namespace eve
{
  template<typename Options>
  struct read_t : callable<read_t, Options>
  {
    template<typename Ptr>
    EVE_FORCEINLINE auto operator()(Ptr ptr) const noexcept -> std::remove_cvref_t<decltype(*ptr)>
    {
      return EVE_DISPATCH_CALL(ptr);
    }

    template<typename Readable>
    EVE_FORCEINLINE auto operator()(Readable ptr) const noexcept -> decltype(ptr.read())
    {
      return EVE_DISPATCH_CALL(ptr);
    }

    template<typename... Ptrs>
    EVE_FORCEINLINE auto operator()(soa_ptr<Ptrs...> ptr) const noexcept { return EVE_DISPATCH_CALL(ptr); }

    EVE_CALLABLE_OBJECT(read_t, read_);
  };
// TODO DOC 
//================================================================================================
//! @addtogroup memory
//! @{
//! @var read
//!
//! @brief Callable object reading single value from memory
//!
//! **Required header:** `#include <eve/module/core.hpp>`
//!
//! `operator*` based interface used in the standard has notorious issues with proxy references.
//! To prevent those issues when dealing with complex, potentially SIMD-aware iterators, `eve::read`
//! is to be used.
//!
//! #### Members Functions
//!
//! | Member       | Effect                                                     |
//! |:-------------|:-----------------------------------------------------------|
//! | `operator()` | Performs a single read from memory                         |
//!
//! ---
//!
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//!  template<typename Ptr> auto operator()(Ptr p) const noexcept
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!
//! **Parameters**
//!
//! `ptr`: Memory to read from.
//!
//! **Return value**
//!
//! Returns a signle value read at the memory location specified by `ptr`. If `ptr` is
//! equivalent to `nullptr`, the behavior is undefined.
//!
//================================================================================================
  inline constexpr auto read = functor<read_t>;
//================================================================================================
//!  @}
//================================================================================================
}
namespace eve::detail
{
  template<typename Ptr, callable_options O>
  EVE_FORCEINLINE auto read_(EVE_REQUIRES(cpu_), O const&, Ptr ptr) noexcept
  {
    if constexpr(requires { ptr.read(); })  return ptr.read();
    else                                    return *ptr;
  }

  template<typename... Ptrs, callable_options O>
  EVE_FORCEINLINE auto read_(EVE_REQUIRES(cpu_), O const&, soa_ptr<Ptrs...> ptr) noexcept
  {
    return kumi::map(read, ptr);
  }
}
