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

  struct ddhi_
  {
    template<typename V>
    decltype(auto) operator()(V&& v) const noexcept
    requires (eve::is_dd<eve::element_type_t<std::decay_t<V>>>::value )
    {
      std::cout << "ddhi " << get<1>(EVE_FWD(v)) << " @@@ ";
      return get<0>(EVE_FWD(v));
    }
  };
  constexpr inline auto ddhi =  ddhi_{};
}
