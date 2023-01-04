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
//!   @var inv_2pi
//!   @brief Callable object computing the constant \f$\frac{1}{2\pi}\f$.
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
//!      T inv_2pi(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::inv_2pi(as<T>())` returns the inverse of \f$2\pi\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/inv_2pi.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(inv_2pi_, inv_2pi);

namespace detail
{
  template<floating_ordered_value T>
  EVE_FORCEINLINE auto inv_2pi_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.45f306p-3);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.45f306dc9c883p-3);
  }

  template<floating_ordered_value T, typename D>
  EVE_FORCEINLINE constexpr auto inv_2pi_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.45f308p-3);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.45f306dc9c883p-3);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.45f306p-3);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.45f306dc9c882p-3);
    }
  }
}
}
