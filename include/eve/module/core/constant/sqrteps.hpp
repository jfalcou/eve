//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/decorator/roundings.hpp>
#include <eve/module/core/constant/constant.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var sqrteps
  //!
  //! @brief Callable object computing the square root of the machine epsilon value.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the sqrteps constant                               |
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
  //! the call `eve::sqrteps(as<T>())` is semantically equivalent to  `eve::sqrt(eve::eps(as<T>()))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/sqrteps.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sqrteps_, sqrteps);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE auto sqrteps_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)
      {
        return Constant<T, 0x39B504F3U >();
      }
      else if constexpr(std::is_same_v<t_t, double>)
      {
        return Constant<T, 0x3E50000000000000ULL>();
      }
      else if constexpr(std::is_integral_v<t_t>)
      {
        return T(1);
      }
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto sqrteps_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)
      {
        if constexpr(std::is_same_v<D, upward_type>)
           return Constant<T, 0x39B504F4U >();
        else
         return sqrteps(as<T>());
      }
      else return sqrteps(as<T>());
    }
  }
}
