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
//!   @var rayleigh_skewness
//!   @brief Callable object computing the Rayleigh skewness value :
//!   \f$2\sqrt\pi(\pi-3)/(4-\pi^{3/2})\f$.
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
//!      T rayleigh_skewness(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::allbits(as<T>())` returns the Rayleigh skewness.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/rayleigh_skewness.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(rayleigh_skewness_, rayleigh_skewness);

namespace detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE auto rayleigh_skewness_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.4320fp-1);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.4320efa6fa904p-1);
  }

  template<floating_real_value T, typename D>
  EVE_FORCEINLINE constexpr auto
  rayleigh_skewness_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.4320fp-1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.4320efa6fa904p-1);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.4320eep-1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.4320efa6fa903p-1);
    }
  }
}
}
