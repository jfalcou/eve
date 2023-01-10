//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/dd/regular/traits.hpp>
#include <iostream>

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

  struct ddlo_
  {
    template<typename V>
    decltype(auto) operator()(V&& v) const noexcept
    requires (eve::is_dd<eve::element_type_t<std::decay_t<V>>>::value )
    {
      std::cout << "ddlo " << get<1>(EVE_FWD(v)) << " &&& ";
      return get<1>(EVE_FWD(v));
    }
  };
  constexpr inline auto ddlo =  ddlo_{};
}
