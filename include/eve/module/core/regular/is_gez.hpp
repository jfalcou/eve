//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/constant/true.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_gez_t : elementwise_callable<is_gez_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_gez_t, is_gez_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_gez
//!   @brief `elementwise callable` returning a logical true  if and only if the element value is greater or equal to 0.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto is_gez(value auto x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    Returns [elementwise](@ref glossary_elementwise) `x >= 0`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_gez.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_gez[mask](x)` provides a masked version of `eve::is_gez` which is
//!     equivalent to `if_else (mask, is_gez(x), eve::false( eve::as(x)))`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_gez = functor<is_gez_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_gez_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( unsigned_value<T> )
        return true_(eve::as(a));
      else
        return a >= zero(eve::as(a));
    }
  }
}
