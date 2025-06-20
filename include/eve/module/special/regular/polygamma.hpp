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
#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/regular/zeta.hpp>
#include <eve/module/special/regular/trigamma.hpp>

namespace eve
{
template<typename Options>
struct polygamma_t : callable<polygamma_t, Options>
{
  template<eve::scalar_value N, eve::floating_value T>
  constexpr EVE_FORCEINLINE T operator()(N n, T v) const  { return EVE_DISPATCH_CALL(n, v); }

  EVE_CALLABLE_OBJECT(polygamma_t, polygamma_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var polygamma
//!   @brief `elementwise_callable` object computing the Polygamma function i.e.
//!   the second derivative of the \f$\log\Gamma\f$  function.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto polygamma(scalar_value auto n, floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto polygamma[conditional_expr auto c](scalar_value auto n, floating_value auto x) noexcept; // 2
//!      constexpr auto polygamma[logical_value auto m](scalar_value auto n, floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [scalar_value](@ref eve::value). (see note below)
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of the Polygamma function: \f$\psi(x) = \frac{\Gamma'(x)}{\Gamma(x)}\f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @note Only integral (or flint) positive values of n correspond to the proper polygamma definition. You can use
//!        non intetgral values but the function result may be different to
//!        the standard definitions of polygamma extension.
//!
//!  @groupheader{External references}
//!   *  [DLMF: Gamma and Psi Functions](https://dlmf.nist.gov/5.2#i)
//!   *  [Wolfram MathWorld: Polygamma Function](https://mathworld.wolfram.com/PolygammaFunction.html)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/polygamma.cpp}
//================================================================================================
  inline constexpr auto polygamma = functor<polygamma_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename N, typename T, callable_options O>
    constexpr T  polygamma_(EVE_REQUIRES(cpu_), O const&, N m, T z) noexcept
    {
      if (is_eqz(m)) return eve::digamma(z);
      if (m == 1)    return eve::trigamma(z);
      auto pi  = eve::pi(eve::as(z));

      auto mediumcotderiv = [](auto n, auto x)
        {
          constexpr std::array<kumi::tuple
        }:
      
        auto largecotderiv = [](auto n, auto x)
        {
        auto p = n+1;
        x -= eve::nearest(x);
        auto s = eve::rec(eve::pow(x, p));
        n = 1;
        auto s0 = eve::zero(eve::as(s));
        while (1)
        {
          s0 = s;
          auto a = eve::pow(x+n, p);
          auto b = eve::pow(x-n, p);
          auto t = (a + b) / (a * b);
          s += t;
          if (eve::all(s == s0)) break;
          n += 1;
        }
        std::cout << "2 n " << n << std::endl;
        return s*eve::inv_pi(eve::as(x)); ;
      };

      auto cotderiv =  [pi, largecotderiv](auto n,  auto x){ //derivatives of order n of cotpi(x);
        std::cout << "1 n " << n << std::endl;
        using elt_t =  eve::element_type_t<T>;
        auto pi2 = eve::pi2(eve::as(x));
        switch (n){
        case 0 : return eve::cotpi(x);
        case 1 : return -eve::sqr(eve::cscpi(x));
        case 2 : return 2*pi2*eve::cotpi(x)*eve::sqr(eve::cscpi(x));
        case 3 : return -2*pi*pi2*eve::sqr(eve::cscpi(x))*(2*eve::sqr(cotpi(x)) + eve::sqr(cscpi(x)));
        case 4 : return 8*eve::sqr(pi2)*cotpi(x)*eve::sqr(cscpi(x))*(eve::sqr(cotpi(x)) + 2*eve::sqr(cscpi(x)));
        default :return eve::sign_alternate(n)*largecotderiv(n, x)*tgamma(elt_t(n+1));
        }
      };
      using elt_t =  eve::element_type_t<T>;

      int s = m+1;
      auto gez = eve::is_gez(z);
      auto mg = -eve::tgamma(elt_t(s));
      auto hupos  = eve::hurwitz(s,z);
      auto sa = eve::sign_alternate(m);
      if (eve::all(gez))
        return sa*hupos*mg;
      else
      {
        auto huneg = eve::hurwitz(s, eve::oneminus(z));
        return eve::if_else(gez, mg*sa*hupos, (mg*huneg - pi*cotderiv(m,z)));
      }
    }
  }
}
