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
//!   @var egamma
//!   @brief Callable object computing the Euler-Mascheroni constant : \f$\gamma =
//!   \lim_{n\to\infty}\left( \sum_{k = 0}^n \frac1k - \log n\right )\f$.
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
//!      T egamma(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::egamma(as<T>())` returns  \f$\gamma =
//!      \lim_{n\to\infty}\left( \sum_{k = 0}^n \frac1k - \log n\right )\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/egamma.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(egamma_, egamma);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto egamma_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    return Ieee_constant<T, 0x3f13c468U, 0x3fe2788cfc6fb619ULL>(); // 0.57721566490153286060651209008
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto egamma_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    if constexpr( std::is_same_v<D, upward_type> )
      return Ieee_constant<T, 0x3f13c468U, 0x3fe2788cfc6fb619ULL>();
    else return Ieee_constant<T, 0x3f13c467U, 0x3fe2788cfc6fb618ULL>();
  }
}
}
