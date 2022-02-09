//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/constant.hpp>
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
  //! @var smallestposval
  //!
  //! @brief Callable object computing the smallest normal positive value.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the smallestposval constant                       |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::smallestposval(as<T>())` is semantically equivalent to:
  //!   - T(1) if eve::element_type_t<T> is integral
  //!   - T(1.1754944e-38f)if eve::element_type_t<T> is float
  //!   - T(2.225073858507201e-308) if eve::element_type_t<T> is double
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/smallestposval.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(smallestposval_, smallestposval);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE auto smallestposval_(EVE_SUPPORTS(cpu_), eve::as<T> const & = {}) noexcept
    {
      using t_t = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>)
      {
        return Constant<T, 0X00800000U>();
      }
      else if constexpr(std::is_same_v<t_t, double>)
      {
        return Constant<T, 0X0010000000000000ULL>();
      }
      else if constexpr(std::is_integral_v<t_t>)
      {
        return T(1);
      }
    }
  }
}
