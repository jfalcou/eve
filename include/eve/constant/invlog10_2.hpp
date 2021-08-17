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
  //! @var invlog10_2
  //!
  //! @brief Callable object computing 1/log10(2).
  //!
  //! **Required header:** `#include <eve/function/invlog10_2.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the invlog10_2 constant                           |
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
  //! the call `eve::invlog10_2(as<T>())` is semantically equivalent to  `rec(log10(T(2))`.
  //!
  //! ---
  //!
  //! #### Example
  //!  //! @godbolt{doc/core/invlog10_2.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(invlog10_2_, invlog10_2);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto invlog10_2_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = detail::value_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0x40549a78U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x400a934f0979a371ULL>();
    }
  }
}
