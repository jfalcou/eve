//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/ad/regular/traits.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup ad
  //! @{
  //! @var exp_i
  //!
  //! @brief Callable object computing var(x).
  //!
  //! **Required header:** `#include <eve/module/ad.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of var                                     |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating_value](@ref eve::floating_value).
  //!
  //! **Return value**
  //! `as_valder<decltype(x)> :the variable is x so its derivative is 1.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/ad/var.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct var_; }
  template<> struct supports_conditional<tag::var_> : std::false_type {};

  EVE_MAKE_CALLABLE(var_, var);

  namespace detail
  {
    template < floating_value T >
    EVE_FORCEINLINE auto var_( EVE_SUPPORTS(cpu_), const T & x)
    {
      using vd_t = eve::as_valder_t<T>;
      return vd_t{x, T(1)};
    };
  }
}
