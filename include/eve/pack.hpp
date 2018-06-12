//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_PACK_HPP_INCLUDED
#define EVE_PACK_HPP_INCLUDED

#include <eve/arch/spec.hpp>
#include <eve/arch/limits.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/ext/as_pack.hpp>
#include <eve/module/core/type/pack.hpp>

namespace eve
{
  template<std::size_t Cardinal>
  struct fixed : std::integral_constant< std::size_t, Cardinal>
  {
    static_assert( Cardinal == 1 || Cardinal % 2 == 0, "Cardinal must be a power of 2" );
    static constexpr bool is_default = false;
    using split_type = fixed<Cardinal/2>;
  };

  template<std::size_t Cardinal>
  struct defaulted : std::integral_constant< std::size_t, Cardinal>
  {
    static constexpr bool is_default = true;
    using split_type = defaulted<Cardinal/2>;
  };

  template< typename Type
          , typename Size = defaulted<expected_cardinal_v<Type>>
          >
  using pack = ext::as_pack_t<Type,Size>;
}

#endif
