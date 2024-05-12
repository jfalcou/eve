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
//!   @var minlog2denormal
//!   @brief Callable object computing the least value for which eve::exp2 is not denormal.
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
//!      T minlog2denormal(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::minlog2denormal(as<T>())` returns  the least value for which eve::exp2
//!      is not denormal.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/minlog2denormal.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(minlog2denormal_, minlog2denormal);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto minlog2denormal_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;

    if constexpr( std::is_same_v<t_t, float> ) return T(-150);
    else if constexpr( std::is_same_v<t_t, double> ) return T(-1075);
  }

  template<floating_value T, typename D>
  EVE_FORCEINLINE constexpr auto
  minlog2denormal_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return minlog2denormal(as<T>());
  }
}
}
