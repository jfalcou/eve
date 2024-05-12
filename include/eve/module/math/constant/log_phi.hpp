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
//!   @var log_phi
//!   @brief Callable object computing the logarithm of the golden ratio : \f$\log((1+\sqrt5)/2)\f$.
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
//!      T log_phi(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::log_phi(as<T>())` returns  the logarithm of the golden ratio.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/log_phi.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(log_phi_, log_phi);

namespace detail
{
  template<floating_ordered_value T>
  EVE_FORCEINLINE auto log_phi_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.ecc2cap-2);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.ecc2caec5160ap-2);
  }

  template<floating_ordered_value T, typename D>
  EVE_FORCEINLINE constexpr auto log_phi_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.ecc2ccp-2);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.ecc2caec5160ap-2);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.ecc2cap-2);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.ecc2caec51609p-2);
    }
  }
}
}
