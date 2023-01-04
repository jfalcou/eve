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
//!   @var sinh_1
//!   @brief Callable object computing the constant \f$\sinh(1)\f$.
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
//!      T sinh_1(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::sinh_1(as<T>())` returns the hyperbolic sine of 1.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sinh_1.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(sinh_1_, sinh_1);

namespace detail
{
  template<floating_ordered_value T>
  EVE_FORCEINLINE auto sinh_1_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.2cd9fcp+0);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.2cd9fc44eb982p+0);
  }

  template<floating_ordered_value T, typename D>
  EVE_FORCEINLINE constexpr auto sinh_1_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.2cd9fep+0);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.2cd9fc44eb983p+0);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.2cd9fcp+0);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.2cd9fc44eb982p+0);
    }
  }
}
}
