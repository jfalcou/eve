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
//!   @var minlogdenormal
//!   @brief Callable object computing the least value for which eve::exp is not denormal.
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
//!      T minlogdenormal(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::minlogdenormal(as<T>())` returns  the least value for which
//!      eve::exp is not denormal.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/minlogdenormal.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(minlogdenormal_, minlogdenormal);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto minlogdenormal_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;

    if constexpr( std::is_same_v<t_t, float> ) return Constant<T, 0xc2cff1b5U>(); // -103.972084
    else if constexpr( std::is_same_v<t_t, double> )
      return Constant<T, 0xc0874910d52d3053ULL>(); //-745.1332191019413358
  }
}
}
