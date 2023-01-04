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
//!   @var two_o_3
//!   @brief Callable object computing the constant \f$2/3\f$.
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
//!      T two_o_3(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::two_o_3(as<T>())` returns two third.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/two_o_3.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(two_o_3_, two_o_3);

namespace detail
{
  template<floating_ordered_value T>
  EVE_FORCEINLINE auto two_o_3_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.555556p-1);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.5555555555555p-1);
  }

  template<floating_ordered_value T, typename D>
  EVE_FORCEINLINE constexpr auto two_o_3_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.555556p-1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.5555555555556p-1);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.555554p-1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.5555555555555p-1);
    }
  }
}
}
