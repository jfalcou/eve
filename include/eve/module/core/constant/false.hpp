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
  //! @var false_
  //!
  //! @brief Callable object computing the logical false_ value.
  //!
  //! **Required header:** #include <eve/module/core.hpp>
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the false_ constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < value T > auto operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::false_(as<T>())` returns [elementwise](@ref glossary_elementwise), the false
  //! logical value.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/false.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(false__, false_);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto false__(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
       return as_logical_t<T>(false);
    }
  }
}
