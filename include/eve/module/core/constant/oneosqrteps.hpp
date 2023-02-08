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
#include <eve/module/core/regular/rec.hpp>
#include <eve/module/core/regular/sqrt.hpp>

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var oneosqrteps
//!   @brief Computes the  the inverse of the square root of the machine epsilon.
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
//!      T oneosqrteps(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::oneosqrteps(as<T>())`  is semantically equivalent to
//!      `eve::rec (eve::sqrt (eve::eps (as<T>())))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/oneosqrteps.cpp}
//! @}
//================================================================================================

EVE_MAKE_CALLABLE(oneosqrteps_, oneosqrteps);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto oneosqrteps_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;

    if constexpr( std::is_same_v<t_t, float> ) return Constant<T, 0X453504F3U>();
    else if constexpr( std::is_same_v<t_t, double> ) return Constant<T, 0X4190000000000000UL>();
  }

  template<floating_value T, typename D>
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  EVE_FORCEINLINE constexpr auto oneosqrteps_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> )
    {
      if constexpr( std::is_same_v<D, downward_type> ) return oneosqrteps(as<T>());
      else return Constant<T, 0X453504F4U>();
    }
    else return oneosqrteps(as<T>());
  }
}
}
