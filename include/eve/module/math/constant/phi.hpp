//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var phi
//!   @brief Callable object computing the golden ratio : \f$\frac{1+\sqrt5}2\f$.
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
//!      template< eve::value T >
//!      T phi(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::phi(as<T>())` returns the golden ratio.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/phi.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(phi_, phi);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto phi_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    return Ieee_constant<T, 0X3FCF1BBDU, 0X3FF9E3779B97F4A8ULL>();
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto phi_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    if constexpr( std::is_same_v<D, upward_type> )
      return Ieee_constant<T, 0X3FCF1BBDU, 0X3FF9E3779B97F4A8ULL>();
    else return Ieee_constant<T, 0X3FCF1BBCU, 0X3FF9E3779B97F4A7ULL>();
  }
}
}
