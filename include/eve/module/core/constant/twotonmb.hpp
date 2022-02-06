//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant.hpp>
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
  //! @var twotonmb
  //!
  //! @brief Callable object computing the 2 power of the number of mantissa bits.
  //!
  //! **Required header:** `#include <eve/function/twotonmb.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the two to the nbmantissabits power               |
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
  //! the call `eve::twotonmb(as<T>())` is semantically equivalent to
  //! `eve::exp2(T(eve::nbmantissabits(as<eve::element_type_t<T>>())))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/twotonmb.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(twotonmb_, twotonmb);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE auto twotonmb_(EVE_SUPPORTS(cpu_), eve::as<T> const & = {}) noexcept
    {
      using t_t = element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)
      {
        return Constant<T, 0X4B000000U>();
      }
      else if constexpr(std::is_same_v<t_t, double>)
      {
        return Constant<T, 0X4330000000000000ULL>();
      }
    }
  }
}
