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
//!   @var invlog_phi
//!   @brief Callable object computing the inverse of the logarithm of the golden ratio :
//!   \f$1/\log((1+\sqrt5)/2)\f$.
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
//!      T invlog_phi(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::allbits(as<T>())` returns the inverse of the logarithm of the golden ratio?
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/invlog_phi.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(invlog_phi_, invlog_phi);

namespace detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE auto invlog_phi_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.09fecp+1);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.09fec09279922p+1);
  }

  template<floating_real_value T, typename D>
  EVE_FORCEINLINE constexpr auto invlog_phi_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.09fec2p+1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.09fec09279922p+1);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.09fecp+1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.09fec09279921p+1);
    }
  }
}
}
