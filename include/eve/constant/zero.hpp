//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/as.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var zero
  //!
  //! @brief Callable object computing the O value.
  //!
  //! **Required header:** `#include <eve/function/zero.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the zero constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::zero(as<T>())` is semantically equivalent to  `T(0)`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/zero.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(zero_, zero);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE T zero_(EVE_SUPPORTS(cpu_), eve::as<T> const &) noexcept
    {
      // This better inline.
      if constexpr ( product_type<T> ) return T{kumi::map([](auto m) { return zero(as(m)); }, T{})};
      else return T(0);
    }
  }
}
