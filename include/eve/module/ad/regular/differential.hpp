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
  //! @brief Callable object computing imaginary part of differentialues.
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
  //!  auto operator()(maybe<valder> auto x...) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`f`:   callable t differentiate.
  //!`x`:   [maybe<valder>](@ref eve::maybe<valder>).
  //!
  //! **Return the value of the differential of f at x :\$f \sum_0^n \frac{\partial{f}}{\partial{x}}dx \$f
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/ad/differential.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct differential_; }
  template<> struct supports_conditional<tag::differential_> : std::false_type {};

  EVE_MAKE_CALLABLE(differential_, differential);

  namespace detail
  {
    template<typename Func, floating_real_value X>
    EVE_FORCEINLINE V differential_( EVE_SUPPORTS(cpu_), Func f, X const & x, X const & dx) noexcept
    {
      return der(f(as_valder_t<X>(x, dx)));
    }

    EVE_FORCEINLINE V differential_( EVE_SUPPORTS(cpu_), Func f, like<valder> auto const & x) noexcept
    {
      return der(f(x));
    }

    EVE_FORCEINLINE V differential_( EVE_SUPPORTS(cpu_), Func f, maybe<valder> auto const & x...) noexcept
    {
      return der(f(x...));
    }
  }
}
