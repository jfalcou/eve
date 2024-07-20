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
  struct sph_bessel_jn_t : strict_elementwise_callable<sph_bessel_jn_t, Options>
  {
    template<eve::value N, eve::floating_value T>
    requires (same_lanes_or_scalar<N, T>)
    EVE_FORCEINLINE constexpr as_wide_as_t<T, N> operator()(N n, T x) const noexcept
    { return EVE_DISPATCH_CALL(n, x); }

    EVE_CALLABLE_OBJECT(sph_bessel_jn_t, sph_bessel_jn_);
  };

  //================================================================================================
  //! @addtogroup bessel
  //! @{
  //!   @var sph_bessel_jn
  //!   @brief Computes the spherical Bessel functions of the first kind,
  //!   \f$ j_{n}(x)= \sqrt{\frac\pi{2x}}J_{n+1/2}(x)\f$.
  //!
  //!   It is the solution of \f$ x^{2}y''+2xy'+(x^2-n(n+1))y=0\f$ for which \f$ y(0) = 0\f$
  //!   if \f$n \ne 0\f$ else \f$1\f$.
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
  //!      constexpr auto sph_bessel_jn(value auto n, floating_value auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto sph_bessel_jn[conditional_expr auto c](value auto n, floating_value auto x) noexcept; // 2
  //!      constexpr auto sph_bessel_jn[logical_value auto m](value auto n, floating_value auto x)    noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n`: Order of the function.
  //!     * `x`: [Floating argument](@ref eve::floating_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1.The value of \f$ \displaystyle j_{n}(x)=
  //!      (-x)^n\left(\frac1x\frac{d}{dx}\right)^n \frac{\sin x}x\f$ is returned.
  //!     2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/sph_bessel_jn.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto sph_bessel_jn = functor<sph_bessel_jn_t>;

  namespace detail
  {
    template<typename I, typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_wide_as_t<T, I>
    sph_bessel_jn_(EVE_REQUIRES(cpu_), O const&, I n, T x) noexcept
    {
      EVE_ASSERT(all(is_gez(n) && is_flint(n)), "eve::sph_bessel_jn : some orders are non integral positive");
      EVE_ASSERT(all(is_nltz(x))              , "eve::sph_bessel_jn : some x are negative");
      using elt_t = element_type_t<T>;
      if constexpr( integral_value<I> ) return sph_bessel_jn(convert(n, as<elt_t>()), x);
      else return if_else(abs(x) < eps(as(x)),
                          if_else(is_eqz(n), one(as(x)), zero),
                          cyl_bessel_jn(n + half(as(n)), x) * rsqrt(2 * x * inv_pi(as(x))));
    }
  }
}
