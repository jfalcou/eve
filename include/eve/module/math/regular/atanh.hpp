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
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/regular/log1p.hpp>

namespace eve
{
  template<typename Options>
  struct atanh_t : elementwise_callable<atanh_t, Options>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(atanh_t, atanh_);
  };

  //================================================================================================
  //! @addtogroup math_invhyper
  //! @{
  //!   @var atanh
  //!   @brief `elementwise_callable` object computing the inverse hyperbolic tangent.
  //!
  //!   @groupheader{Header file}
  //!
  //!   @code
  //!   #include <eve/module/math.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      // Regular overload
  //!      constexpr auto atanh(floating_value auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto atanh[conditional_expr auto c](floating_value auto x) noexcept; // 2
  //!      constexpr auto atanh[logical_value auto m](floating_value auto x)    noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`: [floating value](@ref eve::floating_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //! **Return value**
  //!
  //!    1. Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic tangent of the
  //!      input.
  //!      In particular:
  //!      * If the element is \f$\pm1\f$, \f$\pm\infty\f$ is returned.
  //!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
  //!      * If the absolute value of the element is greater than one or a `NaN`, `NaN` is returned.
  //!    2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{External references}
  //!   *  [C++ standard reference: atanh](https://en.cppreference.com/w/cpp/numeric/math/atanh)
  //!   *  [Wolfram MathWorld: Inverse Hyperbolic Tangent](https://mathworld.wolfram.com/InverseHyperbolicTangent.html)
  //!   *  [Wikipedia: Inverse hyperbolic functions](https://en.wikipedia.org/wiki/Inverse_hyperbolic_functions)
  //!   *  [DLMF: Inverse hyperbolic functions](https://dlmf.nist.gov/4.37)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/math/atanh.cpp}
  //================================================================================================
  inline constexpr auto atanh = functor<atanh_t>;
  //================================================================================================
  //!  @}
  //================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    constexpr EVE_FORCEINLINE T atanh_(EVE_REQUIRES(cpu_), O const& , T const& x)
    {
      auto absx = eve::abs(x);
      auto t    = absx + absx;
      auto z1   = oneminus(absx);
      auto test = absx < half(eve::as<T>());
      auto tmp  = if_else(test, absx, t) / z1;
      if constexpr( scalar_value<T> ) tmp = test ? fma(t, tmp, t) : tmp;
      else tmp = fma[test](tmp, t, t);
      return signnz(x)*half(eve::as<T>())*log1p(tmp);
    }
  }
}
