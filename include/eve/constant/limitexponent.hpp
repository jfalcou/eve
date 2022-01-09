//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/traits/as_integer.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var limitexponent
  //!
  //! @brief Callable object computing the greatest exponent value plus one.
  //!
  //! **Required header:** `#include <eve/function/limitexponent.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the limitexponent constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < floating_real_value T > auto operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::limitexponent(as<T>())` is semantically equivalent to
  //!   - as_integer_t<T>(128) if eve::element_type_t<T> is float
  //!   - as_integer_t<T>(1024) if eve::element_type_t<T> is double
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/limitexponent.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(limitexponent_, limitexponent);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto limitexponent_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t = element_type_t<T>;
      using i_t = as_integer_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return i_t(128);
      else if constexpr(std::is_same_v<t_t, double >) return i_t(1024);
    }
  }
}
