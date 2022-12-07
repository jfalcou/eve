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
  //! @addtogroup complex
  //! @{
  //! @var imag
  //!
  //! @brief Callable object computing imaginary part of values.
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
  //!  auto operator()(value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!
  //! **Return value**
  //! 0 if `x` is real or the imaginary part of `x` if x is an instance of eve::complex.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/complex/imag.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct imag_; }
  template<> struct supports_conditional<tag::imag_> : std::false_type {};

  EVE_MAKE_CALLABLE(imag_, imag);

  namespace detail
  {
    template<ordered_value V>
    EVE_FORCEINLINE V imag_( EVE_SUPPORTS(cpu_), V const &) noexcept
    {
      return V(0);
    }
  }
}
