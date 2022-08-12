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
//!   @var rayleigh_kurtosis_excess
//!   @brief Callable object computing the Rayleigh kurtosis excess value :
//!   \f$-(6\pi^2-24\pi+16)/(4-\pi^2)\f$.
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
//!      T rayleigh_kurtosis_excess(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::allbits(as<T>())` returns a value of type T with all bits set.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/rayleigh_kurtosis_excess.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(rayleigh_kurtosis_excess_, rayleigh_kurtosis_excess);

namespace detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE auto rayleigh_kurtosis_excess_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.f5f162p-3);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.f5f161186c5f2p-3);
  }

  template<floating_real_value T, typename D>
  EVE_FORCEINLINE constexpr auto
  rayleigh_kurtosis_excess_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.f5f162p-3);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.f5f161186c5f2p-3);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.f5f16p-3);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.f5f161186c5f1p-3);
    }
  }
}
}
