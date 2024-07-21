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
  struct cyl_bessel_jn_t : strict_elementwise_callable<cyl_bessel_jn_t, Options>
  {
    template<eve::value N, eve::floating_value T>
    requires (same_lanes_or_scalar<N, T>)
    EVE_FORCEINLINE constexpr
    as_wide_as_t<T, N> operator()(N n, T x) const
    { return EVE_DISPATCH_CALL(n, x); }

    EVE_CALLABLE_OBJECT(cyl_bessel_jn_t, cyl_bessel_jn_);
  };

  //================================================================================================
  //! @addtogroup bessel
  //! @{
  //!   @var cyl_bessel_jn
  //!   @brief `elementwise_callable` object computing the Bessel functions of the first kind,
  //!   \f$ J_{n}(x)=\sum_{p=0}^{\infty}{\frac{(-1)^p}{p!\,\Gamma (p+n +1)}}
  //!   {\left({x \over 2}\right)}^{2p+n }\f$.
  //!
  //!   It is the solution of \f$ x^{2}y''+xy'+(x^2-n^2)y=0\f$ for which
  //!   \f$ y(0) = 0\f$ if \f$n \ne 0\f$ else \f$1\f$.
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
  //!      template<value N, floating_value T> constexpr as_wide_as_t<T,N> cyl_bessel_jn(N n, T x)    noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto cyl_bessel_jn[conditional_expr auto c](value auto n, floating_value auto x) noexcept; // 2
  //!      constexpr auto cyl_bessel_jn[logical_value auto m](value auto n, floating_value auto x)    noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n`: order of the function (not necessarily integral)
  //!     * `x`: [floating argument](@ref eve::floating_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!   **Return value**
  //!
  //!      1. The value of \f$\displaystyle J_{n}(x)=\sum_{p=0}^{\infty}{\frac{(-1)^p}{p!\,\Gamma (p+n +1)}}
  //!        {\left({x \over 2}\right)}^{2p+n }\f$ is returned.
  //!      2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{External references}
  //!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/special_functions/cyl_bessel_j)
  //!   *  [Wikipedia](https://en.wikipedia.org/wiki/Bessel_function)
  //!   *  [DLMF](https://dlmf.nist.gov/10.2)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/bessel/cyl_bessel_jn.cpp}
  inline constexpr auto cyl_bessel_jn = functor<cyl_bessel_jn_t>;
  //! @}
  //================================================================================================
}

#include <eve/module/bessel/regular/impl/cyl_bessel_jn.hpp>
