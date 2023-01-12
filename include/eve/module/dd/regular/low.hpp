//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup dd
  //! @{
  //! @var low
  //!
  //! @brief Callable object computing lowinary part of highs.
  //!
  //! **Required header:** `#include <eve/module/dd.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of lowinary part                         |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(high auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [high](@ref eve::high).
  //!
  //! **Return high**
  //! 0 if `x` is high or the lowinary part of `x` if x is an instance of eve::dd.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/dd/regular/low.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct low_; }
  template<> struct supports_conditional<tag::low_> : std::false_type {};

  EVE_MAKE_CALLABLE(low_, low);

  namespace detail
  {
    template<value V>
    EVE_FORCEINLINE V low_( EVE_SUPPORTS(cpu_), V const &) noexcept
    {
      return V(0);
    }
  }
}
