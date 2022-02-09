//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/half.hpp>
#include <eve/concept/value.hpp>
#include <eve/module/core/constant/constant.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>
namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var mhalf
  //!
  //! @brief Callable object computing the  value negated half value.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the mhalf constant                               |
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
  //! the call `eve::mhalf(as<T>())` is semantically equivalent to  `T(-0.5)`.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/mhalf.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(mhalf_, mhalf);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto mhalf_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0xBF000000U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0xBFE0000000000000ULL>();
    }
  }
}
