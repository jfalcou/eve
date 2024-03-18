/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/decorator/trigo_tags.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/rempio2_kernel.hpp>

namespace eve
{
  template<typename Options>
  struct rempio2_t : elementwise_callable<rempio2_t, Options, quarter_circle_option, half_circle_option
                                          , full_circle_option, medium_option, big_option>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE auto
    operator()(T v) const  noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(rempio2_t, rempio2_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var rempio2
//!
//! @brief Callable object computing the remainder of the division by \f$\pi/2\f$.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      kumi::tuple<eve::as_integer<T>, T, T> rempio2(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//!    A tuple consisting of an [flint](@ref eve::is_flint) value designing the quadrant and two
//!    floating values of type `T` giving the remainder of `x` modulo \f$\pi/2\f$ and a corrective
//!    to the rounding error on the first result.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/rempio2.cpp}
//!  @}
//================================================================================================
  inline constexpr auto rempio2 = functor<rempio2_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE auto
    rempio2_(EVE_REQUIRES(cpu_), O const& o, T const& x) noexcept
    {
      if      constexpr( O::contains(quarter_circle2))  return rempio2_half_circle(x);
      else if constexpr( O::contains(half_circle2))     return rempio2_half_circle(x);
      else if constexpr( O::contains(full_circle2))     return rempio2_full_circle(x);
      else if constexpr( O::contains(medium2))          return rempio2_medium(x);
      else if constexpr( O::contains(big2))             return rempio2_big(x);
      else
      {
        if( eve::all(x <= Rempio2_limit[quarter_circle2](as(x))))   return  kumi::make_tuple(T(0), x, T(0));
        else if( eve::all(x <= Rempio2_limit[half_circle2](as(x)))) return rempio2_half_circle(x);
        else if( eve::all(x <= Rempio2_limit[full_circle2](as(x)))) return rempio2_full_circle(x);
        else if( eve::all(x <= Rempio2_limit[medium2](as(x))))      return rempio2_medium(x);
        else                                                        return rempio2_big(x);
      }
    }
  }
}
