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
//!   @var two_pi
//!   @brief Callable object computing the constant \f$2\pi\f$.
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
//!      T two_pi(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::two_pi(as<T>())` returns $2\pi\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/two_pi.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(two_pi_, two_pi);

namespace detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE auto two_pi_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.921fb6p+2);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.921fb54442d18p+2);
  }

  template<floating_real_value T, typename D>
  EVE_FORCEINLINE constexpr auto two_pi_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.921fb6p+2);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.921fb54442d19p+2);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.921fb4p+2);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.921fb54442d18p+2);
    }
  }
}
}
