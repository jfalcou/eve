//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math
  //! @{
  //! @var maxlog
  //!
  //! @brief Callable object computing the greatest positive value for which eve::exp
  //! returns a finite result
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the maxlog constant                               |
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
  //! the call `eve::maxlog(as<T>())` is semantically equivalent to:
  //!   - T(88.37630f) if eve::element_type_t<T> is float
  //!   - T(709.436) if eve::element_type_t<T> is double
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/maxlog.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(maxlog_, maxlog);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto maxlog_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0x42b0c0a5U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x40862b7d369a5aa7ULL>();
    }
  }
}
