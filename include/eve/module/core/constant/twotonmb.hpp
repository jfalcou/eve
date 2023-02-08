//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/constant/constant.hpp>
#include <eve/module/core/decorator/roundings.hpp>

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var twotonmb
//!   @brief Computes the  2 power of the number of mantissa bits of a floating value.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value T >
//!      T nbmantissabits(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!       The call `eve::twotonmb(as<T>())` is semantically equivalent to
//!      `eve::exp2 (T(eve::nbmantissabits (as<eve::element_type_t<T>>())))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/nbmantissabits.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(twotonmb_, twotonmb);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE auto twotonmb_(EVE_SUPPORTS(cpu_), eve::as<T> const& = {}) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) { return Constant<T, 0X4B000000U>(); }
    else if constexpr( std::is_same_v<t_t, double> )
    {
      return Constant<T, 0X4330000000000000ULL>();
    }
  }

  template<floating_value T, typename D>
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  EVE_FORCEINLINE constexpr auto twotonmb_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
  {
    return twotonmb(as<T>());
  }
}
}
