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
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/constant/mone.hpp>

namespace eve
{
  template<typename Options>
  struct rem_t : tuple_callable<rem_t, Options, saturated_option, downward_option, upward_option,
                                to_nearest_option, toward_zero_option>
  {
    template<eve::integral_value T0, integral_value T1>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1> operator()(T0 t0, T1 t1) const noexcept
    {
      EVE_ASSERT(eve::all(is_nez(t1)), "[eve::rem] elements of the second parameter must be non zero");
      return EVE_DISPATCH_CALL(t0, t1);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(rem_t, rem_);
  };


//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var rem
//!   @brief Computes the  remainder after division.
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
//!      template< eve::integral_value T,  eve::integral_value U>
//!      eve::common_value_t<T, U> rem(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:   [real](@ref eve::value) arguments.
//!
//!   **Return value**
//!
//!      Return the remainder after division division of `x` by `y` and is
//!      semantically equivalent to  `x- eve::trunc ( eve:div(x, y) )*y`.
//!
//!      The call `rem(x, y)` is equivalent to `x % y` if `x` or  `y` is an
//!      [simd value](@ref eve::simd_value).
//!
//!    @note
//!       * Although the infix notation with `%` is supported, the `%` operator on
//!         standard integral scalar type is the original one and so can lead to automatic
//!         promotion. Moreover due to C++ limitations `%` is not available for scalar floating
//!         point values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/rem.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::rem[mask](x, ...)` provides a masked
//!     version of `rem` which is
//!     equivalent to `if_else(mask, rem(x, ...), x)`
//!
//!   * eve::toward_zero
//!
//!       The call `rem[toward_zero](x, y)`  computes  `x-div[towardzero](x, y)*y`.
//!       (this is also the default).
//!
//!   * eve::downward
//!
//!       The call `rem[downward](x, y)`  computes  `x-div[downward](x, y)*y`.
//!
//!   * eve::upward
//!
//!       The call `rem[upward](x, y)`  computes  `x-div[upward](x, y)*y`.
//!        It is not defined for unsigned values as the result can be negative.
//!
//!   * eve::to_nearest
//!
//!       The call `rem[to_nearest](x, y)`  computes  `x-div[to_nearest(](x,y)*y`.
//!        It is not defined for unsigned values as the result can be negative.
//!
//! @}
//================================================================================================
  inline constexpr auto rem = functor<rem_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T rem_(EVE_REQUIRES(cpu_), O const& o, T a, T b) noexcept
    {
      return fanm(a, div[o](a, b), b);
    }

    //masked call must treat specifically masked 0 denominateur
    template<conditional_expr C, integral_value T, callable_options O>
    EVE_FORCEINLINE auto
    rem_(EVE_REQUIRES(cpu_), C const& cond, O const& o, T const& t, T const& f) noexcept
    {
      auto g = if_else(cond, f, mone);
      return if_else(cond, rem[o.drop(condition_key)](t, g), t);
    }

  }
}
