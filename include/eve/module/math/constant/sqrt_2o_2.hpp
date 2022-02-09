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
  //! @addtogroup constant
  //! @{
  //! @var sqrt_2o_2
  //!
  //! @brief Callable object computing the halfed square root of 2 value.
  //!
  //! **Required header:** `#include <eve/function/sqrt_2o_2.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the sqrt_2o_2 constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < floating_value T > T operator()(as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::sqrt_2o_2(as<T>())` is semantically equivalent to  `eve::sqrt(T(2)/2`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/sqrt_2o_2.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sqrt_2o_2_, sqrt_2o_2);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE auto sqrt_2o_2_(EVE_SUPPORTS(cpu_), eve::as<T> const & = {}) noexcept
    {
      return T(0.70710678118654752440084436210484903928483593768847);
    }
  }
}
