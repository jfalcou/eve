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

namespace eve
{
  template<typename Options>
  struct sulp_t : elementwise_callable<sulp_t, Options, kahan_option, harrisson_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const noexcept
    { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(sulp_t, sulp_);
  };

//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var sulp
//!   @brief `elementwise_callable` object computing the classical unit in the last place (Kahan)
//!      or the harrisson version multiplied by the sign of the input.
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
//!      constexpr auto sulp(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sulp[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto sulp[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto sulp[kahan](value auto x)                    noexcept; // 1
//!      constexpr auto sulp[harrison](value auto x)                 noexcept; // 3
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
//!
//!      1. The distance of x to the next representable element in the type of `x` in the x direction. (Kahan definition)
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. The distance of x to the nearest representable element in the type of `x`,  not equal to x. (Harrisson definition).
//!
//!   @note invalid entries return NaN
//!
//!  @groupheader{External references}
//!   *  [wikipedia](//!https://en.wikipedia.org/wiki/Unit_in_the_last_place)
//!   *  [HAL: On the definition of ulp(x)](https://hal.science/inria-00070503)
//!   *  [HAL: On various ways to split a floating-point number]( https://members.loria.fr/PZimmermann/papers/split.pdf)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/sulp.cpp}
//================================================================================================
  inline constexpr auto sulp = functor<sulp_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto sulp_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(integral_value<T>)
        return T(1);
      else
      {
        using e_t = eve::element_type_t<T>;
        constexpr e_t eps = eve::eps(eve::as<e_t>());
        if constexpr(O::contains(harrisson))
        {
          constexpr e_t psi = 1-eps/2;
          auto a = psi*a0;
          return a0-a;
        }
        else //kahan is the default
        {
          constexpr e_t psi = eps*e_t(3)/4;
          auto a = eve::fma(psi, a0, a0);
          return a-a0;
        }
      }
    }
  }
}
