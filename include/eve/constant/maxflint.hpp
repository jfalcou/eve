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
  //! @var maxflint
  //!
  //! @brief Callable object computing the greatest real n representing an integer and
  //! such that n != n+1.
  //!
  //! **Required header:** `#include <eve/function/maxflint.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the maxflint constant                               |
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
  //! the call `eve::maxflint(as<T>())` is semantically equivalent to
  //!   - T(16777216.0f) if eve::element_type_t<T> is float
  //!   - T(9007199254740992.0) if eve::element_type_t<T> is double
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/maxflint.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(maxflint_, maxflint);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto maxflint_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = detail::value_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0x4b800000U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x4340000000000000LL>();
    }
  }
}
