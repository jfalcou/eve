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
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var halfeps
  //!
  //! @brief Callable object computing the the half of the machine epsilon.
  //!
  //! **Required header:** `#include <eve/function/halfeps.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the halfeps constant                              |
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
  //! the call `eve::halfeps(as<T>())` is semantically equivalent to [eve::eps(as<T>())](@ref eve::eps)/2.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/halfeps.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(halfeps_, halfeps);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto halfeps_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = detail::value_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0X33800000U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0X3CA0000000000000ULL>();
    }
  }
}
