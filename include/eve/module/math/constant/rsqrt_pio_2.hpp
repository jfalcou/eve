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
//!   @var rsqrt_pio_2
//!   @brief Callable object computing the constant \f$(\pi/2)^{-1/2}\f$.
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
//!      T rsqrt_pio_2(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::rsqrt_pio_2(as<T>())` returns the inverse of  \f$\sqrt{\pi/2}\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/rsqrt_pio_2.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(rsqrt_pio_2_, rsqrt_pio_2);

namespace detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE auto rsqrt_pio_2_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.988454p-1);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.9884533d43651p-1);
  }

  template<floating_real_value T, typename D>
  EVE_FORCEINLINE constexpr auto rsqrt_pio_2_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.988454p-1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.9884533d43651p-1);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.988452p-1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.9884533d4365p-1);
    }
  }
}
}
