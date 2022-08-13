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
//!   @var maxlog
//!   @brief Callable object computing the greatest positive value for which eve::exp is finite.
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
//!      T maxlog(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::maxlog(as<T>())` returns the greatest positive value for
//!      which eve::exp is finite.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/maxlog.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(maxlog_, maxlog);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto maxlog_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;

    if constexpr( std::is_same_v<t_t, float> ) return Constant<T, 0x42b0c0a5U>();
    else if constexpr( std::is_same_v<t_t, double> ) return Constant<T, 0x40862b7d369a5aa7ULL>();
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto maxlog_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return maxlog(as<T>());
  }
}
}
