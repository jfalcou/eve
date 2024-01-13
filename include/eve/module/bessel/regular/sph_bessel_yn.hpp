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
  struct sph_bessel_yn_t : elementwise_callable<sph_bessel_yn_t, Options>
  {
    template<eve::ordered_value N, eve::floating_ordered_value T>
    as_wide_as_t<T, N> operator()(N n, T x) const  { return EVE_DISPATCH_CALL(n, x); }

    EVE_CALLABLE_OBJECT(sph_bessel_yn_t, sph_bessel_yn_);
  };

  //================================================================================================
  //! @addtogroup bessel
  //! @{
  //!   @var sph_bessel_yn
  //!   @brief Computes the the spherical Bessel functions of the second kind,
  //!   \f$ y_{n}(x)= \sqrt{\frac\pi{2x}}Y_{n+1/2}(x)\f$.
  //!
  //!   It is a solution of \f$ x^{2}y''+2xy'+(x^2-n(n+1))y=0\f$ for which \f$ y(0) = -\infty\f$
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
  //!      template< eve::integral_value N, eve::floating_ordered_value T >
  //!      T sph_bessel_yn(N n, T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n`:   order of the function. Order must be positive.
  //!
  //!     * `x` :  [ordered floating argument](@ref eve::floating_ordered_value).
  //!
  //!   **Return value**
  //!
  //!   The value of \f$ \displaystyle y_{n}(x)=
  //!   (-x)^n\left(\frac1x\frac{d}{dx}\right)^n \frac{\cos x}x\f$
  //!   is returned.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/sph_bessel_yn.cpp}
  //! @}
  //================================================================================================
 inline constexpr auto sph_bessel_yn = functor<sph_bessel_yn_t>;

  namespace detail
  {
    template<value I, floating_value T, callable_options O>
    EVE_FORCEINLINE auto
    sph_bessel_yn_(EVE_REQUIRES(cpu_), O const&, I n, T x) noexcept
    {
      EVE_ASSERT(all(is_gez(n) && is_flint(n)),
                 "sph_bessel_yn : some orders are non integral positive");
      EVE_ASSERT(all(is_nltz(x)), "sph_bessel_yn : some x are negative");
      using elt_t = element_type_t<T>;
      if constexpr( integral_value<I> ) return sph_bessel_yn(convert(n, as<elt_t>()), x);
      else return cyl_bessel_yn(n + half(as(x)), x) * rsqrt(2 * x * inv_pi(as(x)));
    }
  }
}
