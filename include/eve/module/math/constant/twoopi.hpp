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
  //! @var twoopi
  //!
  //! @brief Callable object computing the \f$2/\pi\f$ value.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the twoopi constant                               |
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
  //! the call `eve::twoopi(as<T>())` is semantically equivalent to  `eve::rec(2*eve::atan``(T(1)))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/twoopi.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(twoopi_, twoopi);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE auto twoopi_(EVE_SUPPORTS(cpu_), eve::as<T> const & = {}) noexcept
    {
      using t_t = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>)
      {
        return Constant<T, 0X3F22F983U>();
      }
      else if constexpr(std::is_same_v<t_t, double>)
      {
        return Constant<T, 0X3FE45F306DC9C883ULL>();
      }
    }
  }
}
