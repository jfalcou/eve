//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <type_traits>

namespace eve::detail
{
  template<typename Src, typename Tgt>
  struct copy_qualifiers
  {
  private:
      using R = std::remove_pointer_t<Tgt>;
      using U1 = std::conditional_t<std::is_const<R>::value, std::add_const_t<Src>, Src>;
      using U2 = std::conditional_t<std::is_volatile<R>::value, std::add_volatile_t<U1>, U1>;
  public:
      using type = U2;
  };

  template<typename Src, typename Tgt>
  using copy_qualifiers_t = typename copy_qualifiers<Src, Tgt>::type;
}
