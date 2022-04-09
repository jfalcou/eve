//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup complex
  //! @{
  //! @var imag
  //!
  //! @brief Callable object computing imaginary part of derues.
  //!
  //! **Required header:** `#include <eve/module/complex.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of imaginary part                         |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(derue auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!
  //! **Return value** 0
  //! .
  //!
  //! #### Example
  //!
  //! @godbolt{doc/complex/der.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct der_; }
  template<> struct supports_conditional<tag::der_> : std::false_type {};

  EVE_MAKE_CALLABLE(der_, der);

  namespace detail
  {
    template<typename V>
    EVE_FORCEINLINE auto der_( EVE_SUPPORTS(cpu_), V const &) noexcept
    {
      return V(0);
    }
  }
}
