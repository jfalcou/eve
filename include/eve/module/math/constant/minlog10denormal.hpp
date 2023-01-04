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
//!   @var minlog10denormal
//!   @brief Callable object computing the least value for which eve::exp10 is not denormal.
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
//!      T minlog10denormal(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::minlog10denormal(as<T>())` returns the least value for which
//!      eve::exp10 is not denormal.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/minlog10denormal.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(minlog10denormal_, minlog10denormal);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto minlog10denormal_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;

    if constexpr( std::is_same_v<t_t, float> ) return Constant<T, 0xc2349e36U>();
    else if constexpr( std::is_same_v<t_t, double> ) return Constant<T, 0xc07439b7422d1bfbULL>();
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto
  minlog10denormal_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return minlog10denormal(as<T>());
  }
}
}
