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
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/dist.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/next.hpp>
#include <iostream>

namespace eve
{
  template<typename Options>
  struct sufp_t : elementwise_callable<sufp_t, Options, kahan_option, harrisson_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const noexcept
    { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(sufp_t, sufp_);
  };

//================================================================================================
//! @addtogroup core_fma_internal
//! @{
//!   @var sufp
//!   @brief `elementwise_callable` object computing the signed unit value in the first place of the input
//!   i.e. the greatest integer power of 2 less than or equal to |x|, multiplied by the sign of x.
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
//!      constexpr auto sufp(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sufp[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto sufp[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto sufp[kahan](value auto x)                   noexcept; // 1
//!      constexpr auto sufp[harrison](value auto x)                noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [value](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!     1. the signed unit value in the first place of the input. I.e. the greatest integer power
//!        of the base (2) less than or equal to |x| multiplied by the sign of x. (Kahan- definition)
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. The same value up to a factor 2, but with faster computation. (the result is times 2 is the input is not
//!         a power of 2).
//!
//!  @groupheader{External references}
//!   *  [wikipedia](//!https://en.wikipedia.org/wiki/Unit_in_the_last_place)
//!   *  [HAL: On various ways to split a floating-point number]( https://members.loria.fr/PZimmermann/papers/split.pdf)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/sufp.cpp}
//================================================================================================
  inline constexpr auto sufp = functor<sufp_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto sufp_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(integral_value<T>)
        return eve::sign(a0)*eve::bit_floor(eve::abs(a0));
      else
      {
        using e_t = eve::element_type_t<T>;
        constexpr e_t eps = eve::eps(eve::as<e_t>());
        if constexpr(O::contains(harrisson))
        {
          constexpr e_t phi = 2/eps;
          constexpr e_t phim1(phi-1);
          auto a = phim1*a0;
          return fms[pedantic](phi, a0, a);
        }
        else // kahan is the default
        {
          constexpr e_t phi = (1/eps+1);
          constexpr e_t psi = (1-eps/2);
          auto q = phi*a0;
          auto r = psi*q;
          return (q-r);
        }
      }
    }
  }
}
