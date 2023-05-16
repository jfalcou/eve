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
//!   @var cos_pio_8
//!   @brief Callable object computing the constant \f$\cos(pi/8)\f$.
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
//!      T cos_pio_8(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::cos_pio_8(as<T>())` returns  \f$\cos(pi/8)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/cos_pio_8.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(cos_pio_8_, cos_pio_8);

namespace detail
{
  template<floating_ordered_value T>
  EVE_FORCEINLINE constexpr auto cos_pio_8_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0.923879532511286756128183189397);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0.923879532511286756128183189397);
  }

  template<floating_ordered_value T, typename D>
  EVE_FORCEINLINE constexpr auto cos_pio_8_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0.923879532511286756128183189397);//TODO
      else if constexpr( std::is_same_v<t_t, double> ) return T(0.923879532511286756128183189397);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0.923879532511286756128183189397);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0.923879532511286756128183189397);
    }
  }
}
}
