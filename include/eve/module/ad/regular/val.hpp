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
  //! **Return value** x
  //!
  //! #### Example
  //!
  //! @godbolt{doc/ad/val.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct val_; }
  template<> struct supports_conditional<tag::val_> : std::false_type {};

  EVE_MAKE_CALLABLE(val_, val);

  namespace detail
  {
    template<floating_real_value V>
    EVE_FORCEINLINE V val_( EVE_SUPPORTS(cpu_)
                           , V const & v) noexcept
    {
      return v;
    }
  }
}
