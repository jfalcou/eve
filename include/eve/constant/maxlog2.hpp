//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>


namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var maxlog2
  //!
  //! @brief Callable object computing the greatest positive value.
  //!
  //! **Required header:** `#include <eve/function/maxlog2.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the maxlog2 constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < value T > T operator()( as < Target > const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::maxlog2(as<T>())` is semantically equivalent to  `TO DO`
  //!
  //! ---
  //!
  //! #### Example
  //!  //! @godbolt{doc/core/maxlog2.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(maxlog2_, maxlog2);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto maxlog2_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = detail::value_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0x42fe0000U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x408ff80000000000ULL>();
    }
  }
}
