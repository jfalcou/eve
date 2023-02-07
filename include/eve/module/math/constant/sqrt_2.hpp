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
//!   @var sqrt_2
//!   @brief Callable object computing the constant \f$\sqrt2\f$.
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
//!      T sqrt_2(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::sqrt_2(as<T>())` returns the square root of 2.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sqrt_2.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(sqrt_2_, sqrt_2);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE auto sqrt_2_(EVE_SUPPORTS(cpu_), eve::as<T> const& = {}) noexcept
  {
    return Ieee_constant<
        T,
        0X3FB504F3U,
        0X3FF6A09E667F3BCDULL>(); // 1.41421356237309504880168872420969807856967187537694
  }

  template<floating_value T, typename D>
  EVE_FORCEINLINE constexpr auto sqrt_2_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    if constexpr( std::is_same_v<D, upward_type> )
      return Ieee_constant<T, 0X3FB504F4U, 0X3FF6A09E667F3BCDULL>();
    else return Ieee_constant<T, 0X3FB504F3U, 0X3FF6A09E667F3BCCULL>();
  }
}
}
