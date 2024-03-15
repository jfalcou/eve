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
#include <eve/module/math/regular/tan.hpp>
#include <eve/module/math/regular/atan.hpp>

namespace eve
{
  template<typename Options>
  struct agd_t : elementwise_callable<agd_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(agd_t, agd_);
};

//================================================================================================
//! @addtogroup math_invhyper
//! @{
//! @var agd
//!
//! @brief Callable object computing the inverse gudermanian, i.e. \f$2\tanh(\tan(x/2))\f$.
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
//!      T agd(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) inverse
//!      [gudermanian](@ref eve::gd) of the input.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, 0 is returned.
//!      * If the element is \f$\pm\pi/2\f$, \f$\infty\f$ is returned.
//!      * If the element is not in a  \f$[-\pi/2, \pi/2] \f$, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/agd.cpp}
//!
//!  @}
//================================================================================================
  inline constexpr auto agd = functor<agd_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T agd_(EVE_REQUIRES(cpu_), O const&, T const& x)
    {
      return 2*atanh(tan(x*half(as(x))));
    }
  }
}
