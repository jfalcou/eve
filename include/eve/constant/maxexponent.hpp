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
  //! @var maxexponent
  //!
  //! @brief Callable object computing the greatest positive value.
  //!
  //! **Required header:** `#include <eve/function/maxexponent.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the maxexponent constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < value T > T operator()( as < Target > const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::maxexponent(as<T>())` is semantically equivalent to  `TO DO`
  //!
  //! ---
  //!
  //! #### Example
  //!  //! @godbolt{doc/core/maxexponent.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(maxexponent_, maxexponent);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto maxexponent_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = detail::value_type_t<T>;
      using i_t = as_integer_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return i_t(127);
      else if constexpr(std::is_same_v<t_t, double >) return i_t(1023);
    }
  }
}
