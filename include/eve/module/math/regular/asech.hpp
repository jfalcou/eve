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
#include <eve/module/math/regular/acosh.hpp>

namespace eve
{
  template<typename Options>
  struct asech_t : elementwise_callable<asech_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(asech_t, asech_);
};

//================================================================================================
//! @addtogroup math_invhyper
//! @{
//! @var asech
//!
//! @brief Callable object computing \f$\log(1/x+\sqrt{1/x^2-1})\f$.
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
//!      template< eve::floating_value T >
//!      T asech(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//!   *   Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cosine of the input.
//!      The inverse hyperbolic sine is semantically equivalent to   \f$\log(1/x+\sqrt{1/x^2-1})\f$.
//!
//!       In particular:
//!
//!       * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!       * If the element is \f$1\f$, \f$+0\f$ returned.
//!       * If the element does not belong to \f$[0,1]\f$, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/asech.cpp}
//!
//!  @}
//================================================================================================
  inline constexpr auto asech = functor<asech_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T asech_(EVE_REQUIRES(cpu_), O const&, T const& x)
    {
      return acosh(rec[pedantic2](x));
    }
  }
}
