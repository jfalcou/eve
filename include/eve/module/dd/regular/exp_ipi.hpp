//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/complex/regular/traits.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup complex
  //! @{
  //! @var exp_ipi
  //!
  //! @brief Callable object computing exp_ipi(x).
  //!
  //! **Required header:** `#include <eve/module/complex.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of exp_ipi(x)                              |
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
  //! `complex < decltype(x)> equal to exp(i*pi*x) (i*i = -1).
  //!
  //! #### Example
  //!
  //! @godbolt{doc/complex/exp_ipi.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct exp_ipi_; }
  template<> struct supports_conditional<tag::exp_ipi_> : std::false_type {};

  EVE_MAKE_CALLABLE(exp_ipi_, exp_ipi);

  namespace detail
  {
    template<floating_value V> EVE_FORCEINLINE
    auto exp_ipi_(EVE_SUPPORTS(cpu_), V const & v) noexcept
    {
      using c_t = eve::as_complex_t<V>;
      auto [s, c] = sinpicospi(v);
      return c_t{c, s};
    }
  }
}
