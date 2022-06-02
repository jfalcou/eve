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
  //! @var exp_i
  //!
  //! @brief Callable object computing exp_iinary part of values.
  //!
  //! **Required header:** `#include <eve/module/complex.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of exp(i*x)                               |
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
  //! @godbolt{doc/complex/exp_i.cpp}
  //!
  //!  @}
  //================================================================================================
//   namespace tag { struct exp_i_; }
//   template<> struct supports_conditional<tag::exp_i_> : std::false_type {};

  EVE_MAKE_CALLABLE(exp_i_, exp_i);

  namespace detail
  {
    template<floating_real_value V>
    EVE_FORCEINLINE auto exp_i_( EVE_SUPPORTS(cpu_)
                               , V const & v) noexcept
    {
      using c_t = eve::as_complex_t<V>;
      auto [s, c] = sincos(v);
      return c_t{c, s};
    }
  }
}
