//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/constant.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var oneosqrteps
  //!
  //! @brief Callable object computing the inverse of the square root of the machine epsilon.
  //!
  //! **Required header:** `#include <eve/function/oneosqrteps.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the oneosqrteps constant                          |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < floating_value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::oneosqrteps(as<T>())` is semantically equivalent to
  //! `eve::rec(eve::sqrt(eve::eps(as<T>())))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/arithmetic/oneosqrteps.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(oneosqrteps_, oneosqrteps);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto oneosqrteps_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0X453504F3U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0X4190000000000000UL>();
    }
  }
}
