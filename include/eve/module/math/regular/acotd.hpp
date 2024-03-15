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

namespace eve
{
  template<typename Options>
  struct acotd_t : elementwise_callable<acotd_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(acotd_t, acotd_);
};

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//! @var acotd
//!
//! @brief Callable object computing arc cotangent in degree.
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
//!      T acotd(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) arc cotangent of the
//! input in the range \f$]-90, 90]\f$.
//!
//! In particular:
//!
//!   * If the element is \f$\pm0\f$, \f$\pm90\f$ is returned.
//!   * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
//!   * If the element is a `Nan`, `NaN` is returned.
//!
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/acotd.cpp}
//!  @}
//================================================================================================
  inline constexpr auto acotd = functor<acotd_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acotd_(EVE_REQUIRES(cpu_), O const&, T const& a)
    {
      return radindeg(acot(a));
    }
  }
}
