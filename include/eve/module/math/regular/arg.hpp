//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/constant/pi.hpp>


namespace eve
{

  template<typename Options>
  struct arg_t : elementwise_callable<arg_t, Options, pedantic_option,
                                      rad_option, radpi_option, deg_option>
  {
    template<eve::value T>
    EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(arg_t, arg_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//!   @var arg
//!   @brief `elementwise_callable` object computing the phase angle (in radians).
//!
//!   @groupheader{Callable Signatures}
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
//!      // Regular overload
//!      constexpr auto arg(floating_value auto x)                  noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto arg[conditional_expr auto c](value auto x)  noexcept; // 2
//!      constexpr auto arg[logical_value auto m](value auto x)     noexcept; // 2
//!
//!      // Semantic option
//!      constexpr auto arg[pedantic](floating_value auto x)        noexcept; // 3
//!      constexpr auto arg[rad](floating_value auto x)             noexcept; // 1
//!      constexpr auto arg[deg](floating_value auto x)             noexcept; // 4
//!      constexpr auto arg[pirad](floating_value auto x)           noexcept; // 5
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!    * `x`: [floating value](@ref eve::floating_value) argument.
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns [elementwise](@ref glossary_elementwise) the phase angle (in radians) of the
//!       input (0 or\f$\pi\f$) depending of the bit of sign of the input
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!    3. If the entry is `NaN` the result is `NaN`.
//!    4. Result in degrees
//!    5. Result in \f$\pi\f$ multiples
///!
//!  @note phase can be used as an alias
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/complex/arg)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/arg.cpp}
//================================================================================================
  inline constexpr auto arg = functor<arg_t>;
  inline constexpr auto phase = functor<arg_t>;
//================================================================================================
//!  @}
//================================================================================================
}


namespace eve::detail
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr T
  arg_(EVE_REQUIRES(cpu_), O const &, T a) noexcept
  {
    auto valneg = [](auto x){
      if constexpr(O::contains(deg))          return T(180);
        else if constexpr(O::contains(radpi)) return one(eve::as(x));
        else                                  return pi(eve::as(x));

    };
    auto z = if_else(is_negative(a), valneg(a), eve::zero);
    if constexpr( platform::supports_nans && O::contains(pedantic))
      return if_else(is_nan(a), eve::allbits, z);
    else
      return z;
  }

  constexpr auto argd = eve::arg[eve::deg];
  constexpr auto argpi= eve::arg[eve::radpi];

}
