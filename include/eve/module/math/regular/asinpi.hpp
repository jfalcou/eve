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
#include <eve/module/math/regular/asin.hpp>
#include <eve/module/math/regular/radinpi.hpp>

namespace eve
{
  template<typename Options>
  struct asinpi_t : elementwise_callable<asinpi_t, Options>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(asinpi_t, asinpi_);
  };

  //================================================================================================
  //! @addtogroup math_invtrig
  //! @{
  //!   @var asinpi
  //!   @brief Callable object computing te arc sine in \f$\pi\f$ multiples.
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
  //!      constexpr auto asinpi(floating_value auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto asinpi[conditional_expr auto c](floating_value auto x) noexcept; // 2
  //!      constexpr auto asinpi[logical_value auto m](floating_value auto x)    noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`: [floating value](@ref eve::floating_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!  @groupheader{External references}
  //!   *  [C++ standard reference: asin](https://en.cppreference.com/w/cpp/numeric/math/asin)
  //!   *  [Wolfram MathWorld: InverseSine](https://mathworld.wolfram.com/InverseSine.html)
  //!   *  [Wikipedia:Inverse trigonometric functions ](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions)
  //!   *  [DLMF:Inverse trigonometric functions](https://dlmf.nist.gov/4.23)
  //!
  //! **Return value**
  //!
  //!    1. Returns the [elementwise](@ref glossary_elementwise) value in \f$\pi\f$ multiples
  //!      of the arc sine of the input in the range \f$]-\frac12, \frac12]\f$.
  //!      In particular:
  //!      * If the element is \f$\pm0\f$, \it is returned unmodified.
  //!      * If the element \f$|x| > 1\f$, `NaN` is returned.
  //!      * If the element is a `Nan`, `NaN` is returned.
  //!    2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/math/asinpi.cpp}
  //================================================================================================
  inline constexpr auto asinpi = functor<asinpi_t>;
  //================================================================================================
  //!  @}
  //================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    constexpr EVE_FORCEINLINE T asinpi_(EVE_REQUIRES(cpu_), O const& , T const& a0)
    {
      return radinpi(asin(a0));
    }
  }
}
