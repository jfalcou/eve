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
  struct legendre_t : strict_elementwise_callable < legendre_t, Options
                                                  , successor_option, p_kind_option, q_kind_option
                                                  , condon_shortley_option, associated_option, spherical_option
                                                  >
  {
    template<eve::floating_value ...Ts>
    requires (same_lanes_or_scalar<Ts...>)
    constexpr EVE_FORCEINLINE
    eve::common_value_t<Ts ...> operator()(Ts...b) const noexcept
    {
      return EVE_DISPATCH_CALL(b...);
    }
    template<eve::integral_value T0, eve::floating_value ...Ts>
    requires (same_lanes_or_scalar<T0, Ts...>)
    constexpr EVE_FORCEINLINE
    as_wide_as_t<eve::common_value_t<Ts ...>, T0> operator()(T0 a, Ts...b) const noexcept
    {
      return EVE_DISPATCH_CALL(convert(a, as<element_type_t<common_value_t<Ts...>>>{}), b...);
    }
    template<eve::integral_value T0, eve::integral_value T1, eve::floating_value ...Ts>
    requires (same_lanes_or_scalar<T0, T1, Ts...>)
    constexpr EVE_FORCEINLINE
    as_wide_as_t<eve::common_value_t<Ts ...>, eve::common_value_t<T0, T1>> operator()(T0 a, T1 b, Ts...c) const noexcept
    {
      auto ct = as<element_type_t<common_value_t<Ts...>>>();
      return EVE_DISPATCH_CALL(convert(a, ct), convert(b, ct), c...);
    }

    EVE_CALLABLE_OBJECT(legendre_t, legendre_);
  };

//================================================================================================
//! @addtogroup polynomial
//! @{
//!   @var legendre
//!   @brief Computes the value of the Legendre and associated
//!   Legendre polynomials of order `n` at `x`:
//!
//!    * The Legendre polynomial of order n is given by \f$\displaystyle \mbox{L}_{n}(x)
//!      = \frac{e^x}{n!}\frac{d^n}{dx^n}(x^ne^{-x})\f$.
//!    *  The associated legendre polynomial is given by  \f$\displaystyle \mbox{L}_{n}^{m} =
//!      (-1)^m\frac{d^m}{dx^m}\mbox{L}_{n+m}(x)\f$.
//!
//!   **Defined in header**
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
//!      constexpr auto legendre(integral_value auto n, floating_value auto x)             noexcept; // 1
//!
//!      // Semantic options
//!      constexpr auto legendre[p_kind](integral_value auto n, floating_value auto x)     noexcept; // 1
//!      constexpr auto legendre[q_kind](integral_value auto n, floating_value auto x)     noexcept; // 2
//!      constexpr auto legendre[associated](integral_value auto n,
//!                                          integral_value auto m,
//!                                          floating_value auto x)                        noexcept; // 3
//!      constexpr auto legendre[condon_shortley](integral_value auto n,
//!                                               floating_value auto x)                   noexcept; // 4
//!      constexpr auto legendre[sph](integral_value auto l, integral_value auto m,
//!                                   floating_value auto theta)                           noexcept; // 5
//!      constexpr auto legendre[successor](integral_value auto l,
//!                                         floating_value auto x,
//!                                         integral_value auto ln, integral_value lnm1)   noexcept; // 6
//!      constexpr auto legendre[successor](integral_value auto l,integral_value auto m,
//!                                         floating_value auto x,
//!                                         integral_value auto ln, integral_value lnm1)   noexcept; // 6
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`, `m`, `ln`, `lnm1` : [integral positive arguments](@ref eve::integral_value).
//!     * `x` : [floating argument](@ref eve::floating_value).
//!
//!    **Return value**
//!
//!      1. The value of the Legendre polynomial  of order `n` at `x` is returned.
//!      2. The value of the Legendre polynomial  of order `n` at `x` of the  second kind is returned.
//!      3. The value of the associated legendre polynomial of orders `n`, `m` at `x` is returned.
//!      4. multiplies the associated legendre polynomial value by the Condon-Shortley phase \f$(-1)^m\f$
//!        to match the definition given by Abramowitz and Stegun (8.6.6). This is currently
//!        the version implemented in boost::math.
//!      5. returns the spherical associated Legendre function of degree l, order m, and polar angle theta in radian
//!         (that is the classical spherical harmonic with \f$\phi = 0\f$),
//!         i.e. \f$\displaystyle (-1)^m\frac{(2l+1)(l-m)!}{4\pi(l+m)!}\mbox{P}^m_{l}(\cos\theta)\f$
//!      6. The `successor` option implements the three term recurrence relation for the
//!         (associated) Legendre polynomials, \f$\displaystyle \mbox{P}^m_{l+1} =
//!         \left((2l+1)\mbox{P}^m_{l}(x)-l\mbox{P}^m_{l-1}(x)\right)/(l+m+1)\f$
//!         (\f$m = 0\f$ and no \f$m\f$ in call are equivalent here).
//!
//!  @groupheader{External references}
//!   *  [DLMF: Classical Orthogonal Polynomials](https://dlmf.nist.gov/18.3)
//!   *  [C++ standard reference: legendre](https://en.cppreference.com/w/cpp/numeric/special_functions/legendre)
//!   *  [Wolfram MathWorld: Legendre Polynomial](https://mathworld.wolfram.com/LegendrePolynomial.html)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/polynomial/regular/legendre.cpp}
//================================================================================================
  inline constexpr auto legendre = functor<legendre_t>;
//================================================================================================
//!@}
//================================================================================================
}

#include <eve/module/polynomial/regular/impl/legendre.hpp>
