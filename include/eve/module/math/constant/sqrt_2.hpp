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
  //! @var sqrt_3
  //!
  //! @brief Callable object computing the square root of 2 value.
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the sqrt_3 constant                               |
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
  //! the call `eve::sqrt_3(as<T>())` is semantically equivalent to  `eve::sqrt(T(2))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/sqrt_3.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sqrt_2_, sqrt_2);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE auto sqrt_2_(EVE_SUPPORTS(cpu_), eve::as<T> const & = {}) noexcept
    {
      return Ieee_constant<T, 0X3FB504F3U, 0X3FF6A09E667F3BCDULL>();  //1.41421356237309504880168872420969807856967187537694

   }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto sqrt_2_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      if constexpr(std::is_same_v<D, upward_type>)
        return Ieee_constant<T, 0X3FB504F4U, 0X3FF6A09E667F3BCDULL>();
      else
        return Ieee_constant<T, 0X3FB504F3U, 0X3FF6A09E667F3BCCULL>();
    }
  }
}
