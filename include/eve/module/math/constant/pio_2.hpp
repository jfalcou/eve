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
//!   @var pio_2
//!   @brief Callable object computing the constant \f$\pi/2\f$.
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
//!      T pio_2(as<T> x) noexcept;
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
//!  @godbolt{doc/math/pio_2.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(pio_2_, pio_2);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto pio_2_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;

    if constexpr( std::is_same_v<t_t, float> ) return Constant<T, 0x3fc90fdbU>();
    else if constexpr( std::is_same_v<t_t, double> ) return Constant<T, 0x3ff921fb54442d18ULL>();
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto pio_2_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> )
    {
      if constexpr( std::is_same_v<D, upward_type> ) return eve::pio_2(as<T>());
      else return Constant<T, 0x3fc90fdaU>();
    }
    else
    {
      if constexpr( std::is_same_v<D, downward_type> ) return eve::pio_2(as<T>());
      else return Constant<T, 0x3ff921fb54442d19ULL>();
    }
  }
}
}
