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
//!   @var pi_minus_3
//!   @brief Callable object computing the constant \f$\pi-3\f$.
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
//!      T pi_minus_3(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::pi_minus_3(as<T>())` returns  \f$\pi-3\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/pi_minus_3.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(pi_minus_3_, pi_minus_3);

namespace detail
{
  template<flating_ordered_value T>
  EVE_FORCEINLINE auto pi_minus_3_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.21fb54p-3);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.21fb54442d184p-3);
  }

  template<flating_ordered_value T, typename D>
  EVE_FORCEINLINE constexpr auto pi_minus_3_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.21fb56p-3);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.21fb54442d185p-3);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.21fb54p-3);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.21fb54442d184p-3);
    }
  }
}
}
