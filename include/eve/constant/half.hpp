//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
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
  //! @var half
  //!
  //! @brief Callable object computing the greatest positive value.
  //!
  //! **Required header:** `#include <eve/function/half.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the half constant                                 |
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
  //! the call `eve::half(as<T>())` is semantically equivalent to T(0.5)
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/half.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(half_, half);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto half_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = detail::value_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0x3F000000U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x3FE0000000000000ULL>();
    }
  }
}
