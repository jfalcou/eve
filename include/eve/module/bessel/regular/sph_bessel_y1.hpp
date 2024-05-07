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
  struct sph_bessel_y1_t : elementwise_callable<sph_bessel_y1_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr
    T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(sph_bessel_y1_t, sph_bessel_y1_);
  };

  //================================================================================================
  //! @addtogroup bessel
  //! @{
  //!   @var sph_bessel_y1
  //!   @brief Computes the spherical Bessel function of the second kind,
  //!   \f$ y_{1}(x)= \sqrt{\frac\pi{2x}}Y_{3/2}(x) \f$.
  //!
  //!   It is a solution of \f$ x^{2}y''+2xy'+(x^2-2)y=0\f$ for which \f$ y(0) = -\infty\f$.
  //!
  //!   **Defined in header**
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
  //!      template<eve::floating_value T> constexpr T sph_bessel_y1(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `x`: [floating argument](@ref eve::floating_value).
  //!
  //!   **Return value**
  //!
  //!   The value of \f$\displaystyle y_{1}(x)=-\frac{\cos x }{x^2}-\frac{\sin x }x\f$
  //!   is returned.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/sph_bessel_y1.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto sph_bessel_y1 = functor<sph_bessel_y1_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    T sph_bessel_y1_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
    {
      return if_else(x == inf(as(x)), zero, -cos(x)/sqr(x)-sinc(x));
    }
  }
}
