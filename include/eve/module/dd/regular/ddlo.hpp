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
  //! @var real ddlo
  //!
  //! @brief Callable object computing real ddlo part of values.
  //!
  //! **Required header:** `#include <eve/module/complex.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of the dd lo part                       |
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
  //!   the lo part  of the input.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/dd/real ddlo.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct ddlo_; }
  template<> struct supports_conditional<tag::ddlo_> : std::false_type {};

  EVE_MAKE_CALLABLE(ddlo_, ddlo);

  namespace detail
  {
    EVE_FORCEINLINE auto dd_unary_dispatch(eve::tag::ddlo_, auto && v) noexcept
    {
      return get<1>(EVE_FWD(v));
    }
  }
}
