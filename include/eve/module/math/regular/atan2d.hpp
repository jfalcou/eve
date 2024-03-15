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
#include <eve/module/math/regular/radindeg.hpp>
#include <eve/module/math/regular/atan2.hpp>

namespace eve
{
  template<typename Options>
  struct atan2d_t : elementwise_callable<atan2d_t, Options, pedantic_option>
  {
    template<eve::floating_ordered_value T, eve::floating_ordered_value U>
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    EVE_CALLABLE_OBJECT(atan2d_t, atan2d_);
  };

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//! @var atan2d
//!
//! @brief Callable object computing the arc tangent in degrees using the
//! signs of arguments to determine the correct quadrant.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T, eve::floating_value U >
//!      T atan2d(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`, `y`:   [floating real values](@ref eve::value)
//!
//! **Return value**
//!
//! the arc tangent of \f$\frac{y}x\f$  in the range [-180 , +180] radians, is returned.
//! The **IEEE** limiting values are almost all satisfied :
//!
//!   *  If `x` and `y` are both zero or infinites, Nan is returned (this is not standard
//!      conforming)
//!   *  If `y` is \f$\pm0\f$ and `x` is strictly negative or \f$-0\f$, \f$\pm180\f$ is returned
//!   *  If `y` is \f$\pm0\f$ and `x` is strictly positive or \f$+0\f$, \f$\pm0\f$ is returned
//!   *  If `y` is \f$\pm\infty\f$ and `x` is finite, \f$\pm90\f$ is returned
//!   *  If `x` is \f$\pm0\f$ and `y` is strictly negative, \f$-90\f$ is returned
//!   *  If `x` is \f$\pm0\f$ and `y` is strictly positive, \f$+90\f$  is returned
//!   *  If `x` is \f$-\infty\f$ and `y` is finite and positive, \f$+180\f$ is returned
//!   *  If `x` is \f$-\infty\f$ and `y` is finite and negative, \f$-180\f$ is returned
//!   *  If `x` is \f$+\infty\f$ and `y` is finite and positive, \f$+0\f$ is returned
//!   *  If `x` is \f$+\infty\f$ and `y` is finite and negative, \f$-0\f$ is returned
//!   *  If either `x` is Nan or `y` is Nan, Nan is returned
//!
//!   The call will return a NaN if `x` and `y` are both either null or infinite: this result is
//!   not **IEEE** conformant, but allows to simplify (and
//!   speed) the implementation. In all other cases, the result is standard conformant.
//!
//!   The result type is the [common value type](@ref common_value_t) of the two parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/atan2d.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::pedantic
//!
//!     The call `pedantic(atan2d)(`x`,`y`)` returns the same results as the regular call, but all
//!      **IEEE** limiting values are satisfied :
//!
//!       *  If `y` is \f$\pm\infty\f$ and `x` is \f$-\infty\f$,\f$\pm135\f$ is returned
//!       *  If `y` is \f$\pm\infty\f$ and `x` is \f$+\infty\f$, \f$\pm45\f$ is returned
//!       *  If `x` is \f$\pm0\f$ and `y` is \f$\pm-0\f$, \f$-90\f$ is returned
//!       *  If `x` is \f$\pm0\f$ and `y` is \f$\pm+0\f$, \f$+90\f$  is returned
//!  @}
//================================================================================================
  inline constexpr auto atan2d = functor<atan2d_t>;

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    constexpr EVE_FORCEINLINE common_value_t<T, U>
    atan2d_(EVE_REQUIRES(cpu_), O const& o, T const& a0, const U a1) noexcept
    {
      return radindeg(atan2[o](a0, a1));
    }
  }
}
