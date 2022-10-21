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
//!   @var sqrteps
//!   @brief Computes the square root of the machine epsilon.
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
//!      T sqrteps(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::sqrteps(as<T>())` is semantically equivalent to
//!      `eve::sqrt (eve::eps (as<T>()))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/sqrteps.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(sqrteps_, sqrteps);

namespace detail
{
  template<typename T> EVE_FORCEINLINE auto sqrteps_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) { return Constant<T, 0x39B504F3U>(); }
    else if constexpr( std::is_same_v<t_t, double> )
    {
      return Constant<T, 0x3E50000000000000ULL>();
    }
    else if constexpr( std::is_integral_v<t_t> ) { return T(1); }
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto sqrteps_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> )
    {
      if constexpr( std::is_same_v<D, upward_type> ) return Constant<T, 0x39B504F4U>();
      else return sqrteps(as<T>());
    }
    else return sqrteps(as<T>());
  }
}
}
