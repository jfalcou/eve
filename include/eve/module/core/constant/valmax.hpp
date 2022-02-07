//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/max.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <limits>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var valmax
  //!
  //! @brief Callable object computing the greatest representable value.
  //!
  //! **Required header:** `#include <eve/function/valmax.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the valmax constant                               |
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
  //! the call `eve::valmax(as<T>())` is semantically equivalent to  `T(std::numeric_limits<element_type_t<T>>::max())`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/valmax.cpp}
  //!
  //! @}
  //================================================================================================

  EVE_MAKE_CALLABLE(valmax_, valmax);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE auto valmax_(EVE_SUPPORTS(cpu_), eve::as<T> const & = {}) noexcept
    {
      using t_t = element_type_t<T>;
      return T(std::numeric_limits<t_t>::max());
    }
  }
}
