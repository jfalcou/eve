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
#include <eve/module/core.hpp>
#include <eve/module/math/regular/asin.hpp>

namespace eve
{
  template<typename Options>
  struct acsc_t : elementwise_callable<acsc_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(acsc_t, acsc_);
};

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//! @var acsc
//!
//! @brief Callable object computing the arc cosecant.
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
//!      template< eve::floating_value T > T acsc(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//!   * Returns the [elementwise](@ref glossary_elementwise) arc cosecant of the
//!      input in the range \f$[-\pi/2 , \pi/2]\f$.
//!
//!      In particular:
//!
//!     * If the element is \f$\pm1\f$, \f$\pm\frac\pi2\f$ is returned.
//!     * If the element \f$|x| < 1\f$, `NaN` is returned.
//!     * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
//!     * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/acsc.cpp}
//!  @}
//================================================================================================
  inline constexpr auto acsc = functor<acsc_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acsc_(EVE_REQUIRES(cpu_), O const&, T const& a)
    {
      return eve::asin(rec[pedantic2](a));
    }
  }
}
