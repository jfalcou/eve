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
  //! @var sqrt_2
  //!
  //! @brief Callable object computing the square root of 2 value.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the sqrt_2 constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < flozting_value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::sqrt_2(as<T>())` is semantically equivalent to  `eve::sqrt(T(2))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/sqrt_2.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sqrt_2_, sqrt_2);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE auto sqrt_2_(EVE_SUPPORTS(cpu_), eve::as<T> const & = {}) noexcept
    {
      using t_t = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) {
        return Constant<T, 0x3FB504F3>(); }
      else if constexpr(std::is_same_v<t_t, double>) {
        return Constant<T, 0x3ff6A09E667F3BCCULL>(); }
    }
  }
}
