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
  struct atanpi_t : elementwise_callable<atanpi_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(atanpi_t, atanpi_);
  };

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//! @var atanpi
//!
//! @brief Callable object computing arc tangent in \f$\pi\f$ multiples.
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
//!      T atanpi(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) arc cotangent of the
//!      input in the range \f$[-\frac12, \frac12]\f$.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm\frac\pi2\f$ is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/atanpi.cpp}
//!  @}
//================================================================================================
 inline constexpr auto atanpi = functor<atanpi_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T atanpi_(EVE_REQUIRES(cpu_), O const& , T const& a)
    {
      return radinpi(atan(a));
    }
  }
}
