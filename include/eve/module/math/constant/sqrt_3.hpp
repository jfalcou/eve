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
//!   @var sqrt_3
//!   @brief Callable object computing  constant \f$\sqrt{3}\f$.
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
//!      T sqrt_3(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::sqrt_3(as<T>())` returns the square root of 3.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sqrt_3.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(sqrt_3_, sqrt_3);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE auto sqrt_3_(EVE_SUPPORTS(cpu_), eve::as<T> const& = {}) noexcept
  {
    return Ieee_constant<T, 0X3FDDB3D7U, 0X3FFBB67AE8584CAAULL>();
  }

  template<floating_value T, typename D>
  EVE_FORCEINLINE constexpr auto sqrt_3_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    if constexpr( std::is_same_v<D, upward_type> )
      return Ieee_constant<T, 0X3FDDB3D8U, 0X3FFBB67AE8584CABULL>();
    else return Ieee_constant<T, 0X3FDDB3D7U, 0X3FFBB67AE8584CAAULL>();
  }
}
}
