//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math
  //! @{
  //! @var oneotwoeps
  //!
  //! @brief Callable object computing half the inverse of the machine epsilon.
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the oneotwoeps constant                               |
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
  //! the call `eve::oneotwoeps(``eve::as<T>())` is semantically equivalent to
  //! `eve::rec(2*eve::eps(``eve::as<T>()))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/oneotwoeps.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(oneotwoeps_, oneotwoeps);

  namespace detail
  {
    template<real_value T>
    EVE_FORCEINLINE constexpr auto oneotwoeps_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0X4A800000U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0X4320000000000000ULL>();
      else return T(1);
    }
 
  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto oneotwoeps_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return oneotwoeps(as<T>());
  }
  }
}
