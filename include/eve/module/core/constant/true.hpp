//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/as.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var true_
  //!
  //! @brief Callable object computing the logical true_ value.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the true_ constant                                |
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
  //! the call `eve::true_(as<T>())` returns [elementwise](@ref glossary_elementwise), the true
  //! logical value.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/true.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(true__, true_);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto true__(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
       return as_logical_t<T>(true);
    }
  }
}
