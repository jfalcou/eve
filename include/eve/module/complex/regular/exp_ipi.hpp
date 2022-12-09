//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/math.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup complex
  //! @{
  //! @var exp_ipi
  //!
  //! @brief Callable object computing exp_ipiinary part of values.
  //!
  //! **Required header:** `#include <eve/module/complex.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of exp(i*pi*x)                            |
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
  //!  a complex value
  //!
  //! #### Example
  //!
  //! @godbolt{doc/complex/exp_ipi.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(exp_ipi_, exp_ipi);

  namespace detail
  {

    template<floating_ordered_value V> EVE_FORCEINLINE
    auto exp_ipi_(EVE_SUPPORTS(cpu_), V const & v) noexcept
    {
      using c_t = eve::as_complex_t<V>;
      auto [s, c] = sinpicospi(v);
      return c_t{c, s};
    }
  }
}
