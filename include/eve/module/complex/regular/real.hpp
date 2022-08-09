//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
  //! @var real
  //!
  //! @brief Callable object computing real part of values.
  //!
  //! **Required header:** `#include <eve/module/complex.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of real part                              |
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
  //! 0 if `x` is real or the real part of `x` if x is an instance of eve::complex.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/complex/real.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct real_; }
  template<> struct supports_conditional<tag::real_> : std::false_type {};

  EVE_MAKE_CALLABLE(real_, real);

  namespace detail
  {
    template<floating_real_value V>
    EVE_FORCEINLINE V real_( EVE_SUPPORTS(cpu_), V const& v) noexcept
    {
      return v;
    }
  }
}
