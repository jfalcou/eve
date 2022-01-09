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
  //! @var invlog_2
  //!
  //! @brief Callable object computing 1/log(2).
  //!
  //! **Required header:** `#include <eve/function/invlog_2.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the invlog_2 constant                             |
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
  //! the call `eve::invlog_2(as<T>())` is semantically equivalent to `rec(log(T(2))`.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/invlog_2.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(invlog_2_, invlog_2);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto invlog_2_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0X3FB8AA3BU>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0X3FF71547652B82FEULL>();
    }
  }
}
