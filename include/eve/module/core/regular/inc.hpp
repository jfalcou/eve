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
  struct inc_t : elementwise_callable<inc_t, Options, saturated_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(inc_t, inc_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var inc
//!   @brief return the input incremented by one.
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
//!      T inc(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) argument.
//!
//!    **Return value**
//!
//!    The value of `x + 1` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/inc.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::inc[mask](x, ...)` provides a masked
//!     version of `inc` which is
//!     equivalent to `if_else(mask, inc(x, ...), x)`
//!
//!   * eve::saturated
//!
//!       The call `saturated(inc)(x)` computes the saturated increment of `x`.
//!       The only interest of this behaviour is that
//!       for integral type T the call  `saturated(inc)(Valmax<T>())` returns `Valmax<T>()`.
//!
//! @}
//================================================================================================
  inline constexpr auto inc = functor<inc_t>;

  namespace detail
  {
    template<value T, callable_options O>
    EVE_FORCEINLINE constexpr T inc_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      if constexpr(integral_value<T> && O::contains(saturated2))
        return if_else(a != valmax(eve::as(a)), inc(a),  a);
      else
        return a + one(eve::as(a));
    }
  }
}
