//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

#include <concepts>

namespace eve
{
//================================================================================================
//! @addtogroup core_conversions
//! @{
//!   @var as_value
//!   @brief converts eve constant or just a value to a type.
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
//!      template< eve::value From, eve::value T >
//!      T as_value(From x, eve::as<T> t) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`: either something convertible to T or an of eve constant
//!      * `t` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::as_value(as<T>())` returns a value of type T which is
//!      the conversion of `x` to type Target or the the eve constant of type Target.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/as_value.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(as_value_, as_value);

namespace detail
{
  template<typename From, value T>
  EVE_FORCEINLINE constexpr auto as_value_(EVE_SUPPORTS(cpu_), From from, as<T> const& t) noexcept
  {
    if constexpr( !value<From> ) return from(t);
    else if constexpr( std::integral<T> || std::floating_point<T> ) return (T)from;
    else return T {from};
  }
}
}
