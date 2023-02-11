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
  //! @addtogroup doublereal
  //! @{
  //! @var high
  //!
  //! @brief Callable object computing high part of highs.
  //!
  //! **Required header:** `#include <eve/module/doublereal.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of high part                              |
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
  //! 0 if `x` is high or the high part of `x` if x is an instance of eve::doublereal.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/doublereal/regular/high.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct high_; }
  template<> struct supports_conditional<tag::high_> : std::false_type {};

  EVE_MAKE_CALLABLE(high_, high);

  namespace detail
  {
    template<value V>
    EVE_FORCEINLINE V high_( EVE_SUPPORTS(cpu_), V v) noexcept
    {
      return v;
    }
  }
}
