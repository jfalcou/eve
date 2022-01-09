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
  //! @var minexponent
  //!
  //! @brief Callable object computing the least exponent value.
  //!
  //! **Required header:** `#include <eve/function/minexponent.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the minexponent constant                          |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < floating_value T > auto operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::maxlog(as<T>())` is semantically equivalent to:
  //!   - as_integer_t<T>(-126) if eve::element_type_t<T> is float
  //!   - as_integer_t<T>(-1022) if eve::element_type_t<T> is double
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/minexponent.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(minexponent_, minexponent);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto minexponent_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;
      using i_t = as_integer_t<t_t>;

      if constexpr(std::is_same_v<t_t, float>) return i_t(-126);
      else if constexpr(std::is_same_v<t_t, double >) return i_t(-1022);
    }
  }
}
