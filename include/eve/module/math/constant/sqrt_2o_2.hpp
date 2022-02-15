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
  //! @addtogroup constant
  //! @{
  //! @var sqrt_2o_2
  //!
  //! @brief Callable object computing the halfed square root of 2 value.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
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
    EVE_FORCEINLINE constexpr auto sqrt_2o_2_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0X3F3504F3U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T,0X3FE6A09E667F3BCDULL >();
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto sqrt_2o_2_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      if constexpr(std::is_same_v<D, downward_type>)
      {
        return sqrt_2o_2(as<T>());
      }
      else
      {
        return  Ieee_constant<T, 0X3F3504F4U, 0X3FE6A09E667F3BCEULL >();
      }
    }
  }
}
