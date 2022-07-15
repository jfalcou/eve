//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
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
  //!     template< eve::integral_value N, eve::floating_real_value T >
  //!      eve::as_wide_as<T, N> legendre(N n, T x) noexcept;                               //1
  //!
  //!     template< eve::integral_value N, eve::integral_value M, eve::floating_real_value T >
  //!      eve::as_wide_as<T, N> legendre(N n, M m, T x) noexcept;                          //2
  //!   }
  //!   @endcode
  //!
  //!   1.) legendre polynomial of order n
  //!   **Parameters**
  //!
  //!     * `n`, `m` :  [integral positive arguments](@ref eve::integrall_value).
  //!
  //!     * `x` :  [real floating argument](@ref eve::floating_real_value).
  //!
  //!    **Return value**
  //!
  //!    the value of the polynomial at `x` is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/polynomial/regular/legendre.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!     * eve::p_kind, eve::q_kind
  //!
  //!     The expression `p_kind(legendre)(n,x)` is equivalent to `legendre(n,x)`.
  //!
  //!     The expression `q_kind(legendre)(n,x)` return the value at `x` of the
  //!     second kind legendre function of order `n`.
  //!
  //!     **Example**
  //!
  //!        @godbolt{doc/polynomial/kind/legendre.cpp}
  //!
  //!     * eve::successor
  //!
  //!       The expression `successor(legendre)(l, x, ln, lnm1)`
  //!       (or `successor(legendre)(l, m, x, ln, lnm1)`)
  //!       implements the three term recurrence relation for the
  //!       (associated) Legendre polynomials,
  //!       \f$\displaystyle \mbox{P}^m_{l+1} =
  //!       \left((2l+1)\mbox{P}^m_{l}(x)-l\mbox{P}^m_{l-1}(x)\right)/(l+m+1)\f$
  //!       These functions can be used to create a sequence of values evaluated at
  //!       the same `x` and for rising `l`.
  //!       (  \f$m = 0\f$ and no \f$m\f$ in call are equivalent here).
  //!
  //!       **Example**
  //!
  //!          @godbolt{doc/polynomial/successor/legendre.cpp}
  //!
  //!     * eve::condon_shortley
  //!
  //!       The expression `condon_shortley(legendre)(l, m, x)` multiplies the associated
  //!       legendre polynomial value by the Condon-Shortley phase \f$(-1)^m\f$
  //!       to match the definition given by Abramowitz and Stegun (8.6.6). This is currently
  //!       the version implemented in boost::math 1.79.
  //!
  //!     **Example**
  //!
  //!        @godbolt{doc/polynomial/condon_shortley/legendre.cpp}
  //!
  //!     * eve::sph
  //!
  //!       The expression `sph(legendre)(l, m, theta)` returns the spherical associated
  //!       Legendre function of degree l, order m, and polar angle theta in radian
  //!       (that is the classical spherical harmonic with \f$\phi = 0\f$),
  //!       i.e. \f$\displaystyle\
  //!       (-1)^mfrac{(2l+1)(l-m)!}{4\pi(l+m)!}\mbox{P}^m_{l}(\cos\theta)\f$
  //!
  //!       **Example**
  //!
  //!          @godbolt{doc/polynomial/sph/legendre.cpp}
  //!@}
  //================================================================================================
  EVE_MAKE_CALLABLE(legendre_, legendre);
}

#include <eve/module/polynomial/regular/impl/legendre.hpp>
