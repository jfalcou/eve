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
//!   @var two_pio_3
//!   @brief Callable object computing the constant \f$2\pi/3\f$.
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
//!      T two_pio_3(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::two_pio_3(as<T>())` returns  \f$2\pi/3\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/two_pio_3.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(two_pio_3_, two_pio_3);

namespace detail
{
  template<floating_ordered_value T>
  EVE_FORCEINLINE auto two_pio_3_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.0c1524p+1);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.0c152382d7366p+1);
  }

  template<floating_ordered_value T, typename D>
  EVE_FORCEINLINE constexpr auto two_pio_3_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.0c1524p+1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.0c152382d7366p+1);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.0c1522p+1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.0c152382d7365p+1);
    }
  }
}
}
