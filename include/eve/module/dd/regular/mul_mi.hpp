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
  //! @var mul_mi
  //!
  //! @brief Callable object computing mul_mi part of values.
  //!
  //! **Required header:** `#include <eve/module/complex.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of mul_mi part                               |
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
  //! `complex < decltype(x)> equal to x multiplied by -i (i*i = -1).
  //!
  //! #### Example
  //!
  //! @godbolt{doc/complex/mul_mi.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct mul_mi_; }
  template<> struct supports_conditional<tag::mul_mi_> : std::false_type {};

  EVE_MAKE_CALLABLE(mul_mi_, mul_mi);

  namespace detail
  {
    template<floating_value V>
    EVE_FORCEINLINE auto mul_mi_( EVE_SUPPORTS(cpu_)
                                , V v) noexcept
    {
      using c_t = eve::as_complex_t<V>;
      return c_t{zero(as(v)), -v};
    }
  }
}
