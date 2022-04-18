//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/math.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math
  //! @{
  //! @var phi
  //!
  //! @brief Callable object computing \f$\\\frac{1+\sqrt5}2\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the phi constant                               |
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
  //! the call `eve::phi(as<T>())` is semantically equivalent to  `eve::average(1, eve::sqrt(T(5)))`.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/phi.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(phi_, phi);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto phi_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      return Ieee_constant<T, 0X3FCF1BBDU, 0X3FF9E3779B97F4A8ULL>();
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto phi_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      if constexpr(std::is_same_v<D, upward_type>)
        return Ieee_constant<T, 0X3FCF1BBDU, 0X3FF9E3779B97F4A8ULL>();
      else
        return Ieee_constant<T, 0X3FCF1BBCU, 0X3FF9E3779B97F4A7ULL>();

    }
  }
}
