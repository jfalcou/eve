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
  //! @var log_2
  //!
  //! @brief Callable object computing \f$\\log 2\f$.
  //!
  //! **Required header:** `#include <eve/function/log_2.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the log_2 constant                               |
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
  //! the call `eve::log_2(as<T>())` is semantically equivalent to  `eve::log(T(2.0)`.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/log_2.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(log_2_, log_2);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto log_2_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = detail::value_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0X3F317218U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0X3FE62E42FEFA39EFULL>();
    }
  }
}
