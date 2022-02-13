//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/roundings.hpp>
#include <eve/module/core/constant/ieee_constant.hpp>
#include <eve/module/core/constant/constant.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var logeps
  //!
  //! @brief Callable object computing the logaritm of the machine epsilon.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the logeps constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < floating_value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::logeps(as<T>())` is semantically equivalent to `eve::log(eve::eps(as<T>()))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/logeps.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(logeps_, logeps);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto logeps_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>)  return Constant<T,  0XC17F1402U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0XC04205966F2B4F12ULL>();
    }

    template<floating_value T, typename D>
    EVE_FORCEINLINE constexpr auto logeps_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      if constexpr(std::is_same_v<D, downward_type>)
        return logeps(as<T>());
      else
        return Ieee_constant<T, 0XC17F1401U, 0XC04205966F2B4F11ULL>();
    }
  }
}
