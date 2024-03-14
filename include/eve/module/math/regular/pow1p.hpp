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
#include <eve/module/core.hpp>
#include <eve/module/math/regular/pow.hpp>

namespace eve
{

  template<typename Options>
  struct pow1p_t : elementwise_callable<pow1p_t, Options, raw_option>
  {
    template<eve::floating_scalar_value T, eve::integral_scalar_value U>
    EVE_FORCEINLINE constexpr T operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    template<eve::value T, eve::value U>
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    EVE_CALLABLE_OBJECT(pow1p_t, pow1p_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var pow1p
//!
//! @brief Callable object computing pow1p: \f$(1+x)^y\f$.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto pow1p(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) \f$(1+x)^y\f$, with good accuracy,
//! even when `x` is  small.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/pow1p.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::pow1p[mask](x, y)` provides a masked version of `eve::pow1p` which is
//!     equivalent to `if_else (mask, pow1p(x, y), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/pow1p.cpp}
//!  @}
//================================================================================================
  inline constexpr auto pow1p = functor<pow1p_t>;

  namespace detail
  {

    template<floating_scalar_value T,  integral_scalar_value U, callable_options O>
    EVE_FORCEINLINE constexpr T
    pow1p_(EVE_REQUIRES(cpu_), O const & o, T a0, U a1) noexcept
    {
      return pow1p[o](a0, T(a1));
    }

    template<typename T,  typename U, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T, U>
    pow1p_(EVE_REQUIRES(cpu_), O const & o, T a, U b) noexcept
    {
      if constexpr(O::contains(raw2) || integral_value<U>)
         return pow[o](inc(a), b);
       else
       {
         using r_t =  common_value_t<T, U>;
         if constexpr(has_native_abi_v<r_t>)
         {
           auto x =  r_t(a);
           auto y =  r_t(b);
           auto incx = inc(x);
           return if_else(abs(x) > half(as(x)), pow[o](incx, y), exp(y*log1p(x)));
         }
         else
           return arithmetic_call(pow1p[o], a, b);
       }
    }
  }
}
