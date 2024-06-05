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
#include <eve/module/math/regular/sin.hpp>

namespace eve
{
  template<typename Options>
  struct csc_t : elementwise_callable<csc_t, Options, quarter_circle_option, half_circle_option,
             full_circle_option, medium_option, big_option>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(csc_t, csc_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var csc
//!
//! @brief Callable object computing the cosecant of the input.
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
//!      template< eve::floating_value T >
//!      T csc(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//!   *   Returns the [elementwise](@ref glossary_elementwise) cosecant of the input.
//!       (the inverse of the sine)
//!
//!       In particular:
//!
//!       * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!       * If the element is \f$\pm\infty\f$, Nan is returned.
//!       * If the element is a `NaN`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/csc.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================
  inline constexpr auto csc = functor<csc_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T csc_(EVE_REQUIRES(cpu_), O const& o, T const& a0)
    {
      return eve::rec[pedantic2](sin[o](a0));
    }
  }
}
