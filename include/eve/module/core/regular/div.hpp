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

namespace eve
{
  template<typename Options>
  struct div_t : tuple_callable<div_t, Options, saturated_option, upward_option, downward_option,
                                to_nearest_option, toward_zero_option>
  {
    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(div_t, div_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var div
//!   @brief `elementwise_callable` object computing the  division of multiple values.
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
//!      // Regular overloads
//!      constexpr auto div(value auto x, value auto ... xs)                          noexcept; // 1
//!      constexpr auto div(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto div[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto div[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
//!
//!      // Semantic options
//!      constexpr auto div[upward](/*any of the above overloads*/)                   noexcept; // 4
//!      constexpr auto div[downward](/*any of the above overloads*/)                 noexcept; // 5
//!      constexpr auto div[toward_zero](/*any of the above overloads*/)              noexcept; // 6
//!      constexpr auto div[to_nearest](/*any of the above overloads*/)               noexcept; // 7
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `...xs`: [real](@ref value) arguments.
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      If the arguments are \f$(x_i)_{0\le i\le n}\f$ The value of \f$x/\prod_1^n x_i\f$
//!      is returned.
//!
//!    @note
//!      * With two parameters, the call `div(x, y)` is equivalent to `x / y`
//!        if `x` or  `y` is an  [simd value](@ref eve::simd_value).
//!
//!      * Although the infix notation with `/` is supported for
//!        two parameters, the `/` operator on
//!        standard scalar types is the original one and so can lead to automatic promotion.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/div.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::div[mask](x, ...)` provides a masked
//!     version of `div` which is
//!     equivalent to `if_else(mask, div(x, ...), x)`
//!
//!   * eve::saturated
//!
//!       The expression `eve::saturated(eve::div)(x, xs...)` computes the saturated
//!       division of `x` by  all `xs`. The result is semantically equivalent to
//!       `saturated(div)(x, saturated(mul)(xs...))` but is always defined even if
//!       the denominator is 0.
//!
//!       The relevant cases are just in fact  the division by 0 for integral types
//!       in which case the result is [`eve::valmin(as(x))`](@ref eve::valmin) or
//!       [`eve::valmax(as(x))`](ref eve::valmax) according to the dividend sign, and
//!       the division of [`eve::valmin(as(x))`](@ref eve::valmin)
//!       by -1 that produces [`eve::valmax(as(x))`](@ref eve::valmax).
//!
//!   * eve::toward_zero, eve::downward, eve::upward, eve::to_nearest
//!
//!       The calls `d(div)(x, y)` where d is one of these 4 decorators produce respectively
//!
//!           * `eve::trunc (div(x, y))` for eve::toward_zero.
//!           * `eve::floor (div(x, y))` for deve::downward.
//!           * `eve::ceil (div(x, y))`  for eve::upward.
//!           * `eve::nearest (div(x,y))`for eve::to_nearest.
//!
//! @}
//================================================================================================
  inline constexpr auto div = functor<div_t>;
}

#include <eve/module/core/regular/impl/div.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/div.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/div.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/div.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/div.hpp>
#endif
