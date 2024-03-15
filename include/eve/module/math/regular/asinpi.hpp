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
#include <eve/module/math/regular/radinpi.hpp>

namespace eve
{
  template<typename Options>
  struct asinpi_t : elementwise_callable<asinpi_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(asinpi_t, asinpi_);
  };

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//! @var asinpi
//!
//! @brief Callable object computing computing the arc sine in \f$\pi\f$ multiples.
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
//!      T asinpi(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) arc sine of the
//!      input in the range \f$[-\frac12, \frac12]\f$.
//!
//!      In particular:
//!
//!      * If the element is \f$1\f$, \f$+0\f$ is returned.
//!      * If the element \f$|x| > 1\f$, `NaN` is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!  @godbolt{doc/math/regular/asinpi.cpp}
//!  @}
//================================================================================================
  inline constexpr auto asinpi = functor<asinpi_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T asinpi_(EVE_REQUIRES(cpu_), O const& , T const& a0)
    {
      return radinpi(asin(a0));
    }
  }
}
