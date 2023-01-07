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
  //! @var real ddhi
  //!
  //! @brief Callable object computing real ddhi part of values.
  //!
  //! **Required header:** `#include <eve/module/complex.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of the dd high part                       |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   dd value.
  //!
  //! **Return value**
  //!   the high part  of the input.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/dd/real ddhi.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct ddhi_; }
  template<> struct supports_conditional<tag::ddhi_> : std::false_type {};

  EVE_MAKE_CALLABLE(ddhi_, ddhi);

  namespace detail
  {
    EVE_FORCEINLINE auto dd_unary_dispatch(eve::tag::ddhi_, auto && v) noexcept
    {
      return get<0>(EVE_FWD(v));
    }
  }
}
