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
#include <eve/module/math/regular/atanh.hpp>

namespace eve
{
  template<typename Options>
  struct acoth_t : elementwise_callable<acoth_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(acoth_t, acoth_);
};

//================================================================================================
//! @addtogroup math_invhyper
//! @{
//! @var acoth
//!
//! @brief Callable object computing  \f$\frac{1}{2}\log((x+1)/(x-1))\f$.
//!
//!   **Defined in Header**
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
//!      template< eve::floating_value T > T acoth(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cotangent of the input.
//!      The inverse hyperbolic sine is semantically equivalent to \f$\frac{1}{2}\log((x+1)/(x-1))\f$.
//!
//!      In particular:
//!
//!     * If the element is \f$\pm1\f$, \f$\pm0\f$ is returned.
//!     * If the element is \f$\pm\infty\f$, \f$\pm1\f$ is returned.
//!     * If the element is less than one or a `NaN`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/acoth.cpp}
//!  @}
//================================================================================================
  inline constexpr auto acoth = functor<acoth_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acoth_(EVE_REQUIRES(cpu_), O const&, T const& x)
    {
      return eve::atanh(rec[pedantic2](x));
    }
  }
}
