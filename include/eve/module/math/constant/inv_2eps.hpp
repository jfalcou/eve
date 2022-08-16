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
//!   @var inv_2eps
//!   @brief Callable object computing half the inverse of the machine epsilon.
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
//!      T inv_2eps(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::inv_2eps(as<T>())` returns  half the inverse of the machine epsilon.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/inv_2eps.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(inv_2eps_, inv_2eps);

namespace detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto inv_2eps_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;

    if constexpr( std::is_same_v<t_t, float> ) return Constant<T, 0X4A800000U>();
    else if constexpr( std::is_same_v<t_t, double> ) return Constant<T, 0X4320000000000000ULL>();
    else return T(1);
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto inv_2eps_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return inv_2eps(as<T>());
  }
}
}
