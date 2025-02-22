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
#include <eve/module/math.hpp>

namespace eve
{
  template<typename Options>
  struct abel_t : strict_elementwise_callable< abel_t, Options>
  {
    template<value N, eve::floating_value T0,  eve::floating_value T1>
    constexpr EVE_FORCEINLINE
    as_wide_as_t<eve::common_value_t<T0, T1>, N> operator()(N n, T0 x,  T1 a) const noexcept
    {
      return EVE_DISPATCH_CALL(n, x, a);
    }

    EVE_CALLABLE_OBJECT(abel_t, abel_);
  };

//================================================================================================
//! @addtogroup polynomial
//! @{
//!   @var abel
//!   @brief Computes the value of the Abel function of order `n` at `x`: \f$x(x-an)^{n-1}\f$.
//!          for positive integer `n` it is Abel polynomial.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/polynomial.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!     constexpr auto abel(integral_value auto n, floating_value auto x, floating_value auto a)                           noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto abel[conditional_expr auto c](integral_value auto n, floating_value auto x, floating_value auto a) noexcept; // 2
//!      constexpr auto abel[logical_value auto m](integral_value auto n, floating_value auto x, floating_value auto a)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [value](@ref eve::value)
//!     * `x` :  [real floating argument](@ref eve::floating_value).
//!     * `a` :  [real floating argument](@ref eve::floating_value).
//!
//!    **Return value**
//!
//!      1.The value of the polynomial at `x` is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Abel Polynomials](https://en.wikipedia.org/wiki/Abel_polynomials)
//!   *  [Wolfram MathWorld: Abel Polynomial](https://mathworld.wolfram.com/AbelPolynomial.html)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/polynomial/abel.cpp}
//================================================================================================
  inline constexpr auto abel = functor<abel_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename I, typename T, callable_options O>
    constexpr as_wide_as_t<T, I>
    abel_(EVE_REQUIRES(cpu_),  O const&, I n, T x, T a)
    {
      using r_t = as_wide_as_t<T, I>;
      auto nn = convert(n, as_element<r_t>());
      return if_else( is_eqz(n), one,
                      if_else(n == one(as(n)), x,
                              x*pow(-fms(nn, a, x), dec(n))
                             )
                    );
    }
  }
}
