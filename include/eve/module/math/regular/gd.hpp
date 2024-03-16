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
#include <eve/module/math/regular/atan.hpp>
#include <eve/module/math/regular/tanh.hpp>

namespace eve
{
  template<typename Options>
  struct gd_t : elementwise_callable<gd_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(gd_t, gd_);
  };

//================================================================================================
//! @addtogroup math_hyper
//! @{
//! @var gd
//!
//! @brief Callable object computing the gudermanian gd: \f$\int_0^\infty 1/\cosh x dx\f$.
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
//!      T gd(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) gudermanian of the input.
//!
//! In particular:
//!
//!   * If the element is \f$\pm0\f$, 0 is returned.
//!   * If the element is \f$\pm\infty\f$, \f$\pm\pi/2\f$ is returned.
//!   * If the element is a `NaN`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/gd.cpp}
//!
//!  @}
//================================================================================================
  inline constexpr auto gd = functor<gd_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T gd_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      return 2*atan(tanh(a0*half(as(a0))));
    }
  }
}
