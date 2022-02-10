//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

 #include <eve/module/core/regular/roundings.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/as.hpp>

#include <concepts>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var as_value
  //!
  //! @brief Callable object that converts eve constant or just a value to a type.
  //! Useful in a generic context
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the resulting value                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < typename From, value T > T operator()( From from, as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!  From: either smth convertible to T or one of eve/constant
  //!
  //! **Return value**
  //!
  //! T equivalent of from

  EVE_MAKE_CALLABLE(as_value_, as_value);

  namespace detail
  {
    template<typename From, value T>
    EVE_FORCEINLINE constexpr auto as_value_(EVE_SUPPORTS(cpu_), From from, as<T> const & t) noexcept
    {
           if constexpr ( !value<From>                               ) return from(t);
      else if constexpr ( std::integral<T> || std::floating_point<T> ) return (T)from;
      else                                                             return T{from};
    }
 
  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto as_value_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return as_value(as<T>());
  }
  }
}
