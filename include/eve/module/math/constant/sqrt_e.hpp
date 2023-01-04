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
//!   @var sqrt_e
//!   @brief Callable object computing the constant \f$\sqrt{e}\f$.
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
//!      T sqrt_e(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::sqrt_e(as<T>())` returns  the square root of the
//!      basis of the natural logarithms.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sqrt_e.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(sqrt_e_, sqrt_e);

namespace detail
{
  template<floating_ordered_value T>
  EVE_FORCEINLINE auto sqrt_e_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.a61298p+0);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.a61298e1e069cp+0);
  }

  template<floating_ordered_value T, typename D>
  EVE_FORCEINLINE constexpr auto sqrt_e_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.a6129ap+0);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.a61298e1e069cp+0);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.a61298p+0);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.a61298e1e069bp+0);
    }
  }
}
}
