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
#include <eve/module/math/regular/atan.hpp>
#include <eve/module/math/regular/radindeg.hpp>

namespace eve
{
template<typename Options>
struct atand_t : elementwise_callable<atand_t, Options>
{
  template<eve::floating_value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(atand_t, atand_);
};

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//! @var atand
//!
//! @brief Callable object computing arc tangent in degrees.
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
//!      T atand(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) arc cotangent of the
//! input in the range \f$[-90, 90]\f$.
//!
//! In particular:
//!
//!   * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!   * If the element is \f$\pm\infty\f$, \f$\pm\frac\pi2\f$ is returned.
//!   * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/atand.cpp}
//!  @}
//================================================================================================
  inline constexpr auto atand = functor<atand_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T atand_(EVE_REQUIRES(cpu_), O const& , T const& a)
    {
      return radindeg(atan(a));
    }
  }
}
