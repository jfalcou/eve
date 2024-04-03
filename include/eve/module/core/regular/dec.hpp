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
#include <eve/module/core/constant/one.hpp>

namespace eve
{
  template<typename Options>
  struct dec_t : elementwise_callable<dec_t, Options, saturated_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(dec_t, dec_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var dec
//!   @brief return the input decremented by 1.
//!
//!   **Defined in Header**
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
//!      template< eve::value T >
//!      T dec(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) argument.
//!
//!    **Return value**
//!
//!    The value of `x - 1` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/dec.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::dec[mask](x, ...)` provides a masked
//!     version of `dec` which is
//!     equivalent to `if_else(mask, dec(x, ...), x)`
//!
//!   * eve::saturated
//!
//!       The call `saturated(dec)(x)` computes the saturated decrement of `x`.
//!       The only interest of this behaviour is that
//!       for integral type T  the call `saturated(dec)(Valmin<T>())` returns `Valmin<T>()`.
//!
//! @}
//================================================================================================
  inline constexpr auto dec = functor<dec_t>;

  namespace detail
  {
    template<value T, callable_options O>
    EVE_FORCEINLINE constexpr T dec_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      if constexpr(integral_value<T> && O::contains(saturated2))
        return if_else(a != valmin(eve::as(a)), dec(a),  a);
      else
        return a - one(eve::as(a));
    }
  }
}
