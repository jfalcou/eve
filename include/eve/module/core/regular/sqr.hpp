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
#include <eve/module/core/constant/sqrtvalmax.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/regular/mul.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/if_else.hpp>


namespace eve
{
template<typename Options>
struct sqr_t : elementwise_callable<sqr_t, Options, saturated_option>
{
  template<eve::value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(sqr_t, sqr_);
};

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var sqr
//!   @brief Computes the square of the parameter.
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
//!      template< eve::value T >
//!      T sqr(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) argument.
//!
//!    **Return value**
//!
//!    value containing the [elementwise](@ref glossary_elementwise)
//!    square of `x` if it is representable in this type.
//!
//!  @note
//!      For  [integral signed values](@ref eve::value)   if `eve::abs[eve::saturated](x)`
//!      is greater than `eve::Sqrtvalmax(as(x))` the corresponding element result
//!      is undefined.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/sqr.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::sqr[mask](x)` provides a masked version of `eve::sqr` which is
//!     equivalent to `if_else (mask, sqr(x), x)`.
//!
//!   * eve::saturated
//!
//!     The call `eve::saturated(eve::sqr)(x)` computes a saturated version of eve::sqr.
//!
//!     Contrary to the  non-decorated case, it guarantees
//!      that the result is [elementwise](@ref glossary_elementwise) greater or equal than 0. More
//!      specifically, for any signed integer value `x`, the expression:
//!
//!      `saturated(sqr)(x)`
//!
//!      evaluates to:
//!
//!      [`eve::valmax(as(x))`](@ref eve::valmax) as soon as `eve::abs[eve::saturated](x)`
//!      is greater than `eve::sqrtvalmax(as(x))`.
//!
//! @}
//================================================================================================
  inline constexpr auto sqr = functor<sqr_t>;

  namespace detail
  {

    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    sqr_(EVE_REQUIRES(cpu_), O const &, T const &a0) noexcept
    {
      if constexpr(O::contains(saturated2))
      {
        if constexpr( scalar_value<T> )
        {
          return (eve::abs[saturated2](a0) > sqrtvalmax(eve::as(a0))) ? valmax(eve::as(a0)) : sqr(a0);
        }
        else
        {
          return if_else(eve::abs[saturated2](a0) > sqrtvalmax(eve::as(a0)), valmax(eve::as(a0)), sqr(a0));
        }
      }
      else
        return mul(a0, a0);
    }
  }
}
