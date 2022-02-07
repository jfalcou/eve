//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/one.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var mone
  //!
  //! @brief Callable object computing -1 value.
  //!
  //! **Required header:** `#include <eve/function/mone.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the mone constant                               |
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
  //! the call `eve::mone(as<T>())` is semantically equivalent to  `T(-1)`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/mone.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(mone_, mone);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto mone_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      return T(-1);
    }
  }
}
