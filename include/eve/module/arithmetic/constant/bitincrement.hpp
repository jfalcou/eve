//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/module/core/constant/constant.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var bitincrement
  //!
  //! @brief Callable object computing the bit increment.
  //!
  //! **Required header:** `#include <eve/function/bitincrement.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the bitincrement constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::bitincrement(as<T>())` returns a value of type T such as each element has all
  //! bits exept the lowest set to zero.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/bitincrement.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(bitincrement_, bitincrement);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto bitincrement_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_integral_v<t_t>) return T(1);
      else if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0X1U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x1ULL>();
    }
  }
}
