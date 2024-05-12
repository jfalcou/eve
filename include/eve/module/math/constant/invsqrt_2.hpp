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
//!   @var invsqrt_2
//!   @brief Callable object computing the constant \f$2^{-1/2}\f$.
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
//!      T invsqrt_2(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::invsqrt_2(as<T>())` returns the inverse of \f$\sqrt{2}\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/invsqrt_2.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(invsqrt_2_, invsqrt_2);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto invsqrt_2_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;

    if constexpr( std::is_same_v<t_t, float> ) return Constant<T, 0X3F3504F3U>();
    else if constexpr( std::is_same_v<t_t, double> ) return Constant<T, 0X3FE6A09E667F3BCDULL>();
  }

  template<floating_value T, typename D>
  EVE_FORCEINLINE constexpr auto invsqrt_2_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    if constexpr( std::is_same_v<D, upward_type> )
      return Ieee_constant<T, 0X3F3504F4U, 0X3FE6A09E667F3BCDULL>();
    else return Ieee_constant<T, 0X3F3504F3U, 0X3FE6A09E667F3BCCULL>();
  }
}
}
