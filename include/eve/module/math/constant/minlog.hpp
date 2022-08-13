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
//!   @var minlog
//!   @brief Callable object computing the least value for which eve::exp is not zero
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
//!      T minlog(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::allbits(as<T>())` returns the least value for which eve::exp is not zero.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/minlog.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(minlog_, minlog);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto minlog_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;

    if constexpr( std::is_same_v<t_t, float> ) return Constant<T, 0xc2aec0a5>();
    else if constexpr( std::is_same_v<t_t, double> ) return Constant<T, 0xc086232bdd7abcd3ULL>();
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto minlog_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return minlog(as<T>());
  }
}
}
