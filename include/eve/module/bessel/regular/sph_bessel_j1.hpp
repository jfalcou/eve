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
#include <eve/module/math.hpp>

namespace eve
{
  template<typename Options>
  struct sph_bessel_j1_t : elementwise_callable<sph_bessel_j1_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr
    T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(sph_bessel_j1_t, sph_bessel_j1_);
  };

  //================================================================================================
  //! @addtogroup bessel
  //! @{
  //!   @var sph_bessel_j1
  //!   @brief Computes the spherical Bessel function of the first kind,
  //!   \f$ j_{1}(x)= \sqrt{\frac\pi{2x}}J_{3/2}(x) \f$.
  //!
  //!   It is the  solution of \f$ x^{2}y''+2xy'+(x^2-2)y=0\f$ for which \f$ y(0) = 0\f$
  //!
  //!   @groupheader{Header file}
  //!
  //!   @code
  //!   #include <eve/module/bessel.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      // Regular overload
  //!      constexpr auto sph_bessel_j1(floating_value auto x) -> decltype(x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto sph_bessel_j1[conditional_expr auto c](floating_value auto x) -> decltype(x) noexcept; // 2
  //!      constexpr auto sph_bessel_j1[logical_value auto m](floating_value auto x -> decltype(x))    noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`: positive [floating argument](@ref eve::floating_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1. The value of \f$ \displaystyle j_{1}(x)= \frac{\sin x}{x^2}- \frac{\cos x}{x}\f$
  //!        is returned.
  //!     2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/sph_bessel_j1.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto sph_bessel_j1 = functor<sph_bessel_j1_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T sph_bessel_j1_(EVE_REQUIRES(cpu_), O const&, T x)
    {
      auto rx = rec(x);
      return if_else(eve::abs(x) < eve::eps(eve::as(x)) || is_infinite(x)
                    , eve::zero
                    , (sinc(x)-cos(x))*rx
                    );
    }
  }
}
