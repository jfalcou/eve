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
#include <eve/module/math/regular/radindeg.hpp>

namespace eve
{
  template<typename Options>
  struct asind_t : elementwise_callable<asind_t, Options, raw_option>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(asind_t, asind_);
  };

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//! @var asind
//!
//! @brief Callable object computing the arc sine in degrees.
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
//!      T asind(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) arc sine of the
//! input in the range \f$[-90, 90]\f$.
//!
//! In particular:
//!
//!   * If the element is \f$1\f$, \f$+0\f$ is returned.
//!   * If the element \f$|x| > 1\f$, `NaN` is returned.
//!   * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/asind.cpp}
//!  @}
//================================================================================================
  inline constexpr auto asind = functor<asind_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T asind_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      return radindeg(asin(a0));
    }
  }
}
