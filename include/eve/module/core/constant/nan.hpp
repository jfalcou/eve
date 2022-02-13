//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/module/core/constant/allbits.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/as.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var nan
  //!
  //! @brief Callable object computing the nan value.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the nan constant                                  |
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
  //! the call `eve::nan(as<T>())` is semantically equivalent to  `T(0.0/0.0)`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/nan.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(nan_, nan);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto nan_(EVE_SUPPORTS(cpu_), as<T> const& tgt) noexcept
    {
      return allbits(tgt);
    }
  }
}
