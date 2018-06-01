//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_PACK_HPP_INCLUDED
#define EVE_PACK_HPP_INCLUDED

#include <eve/arch/spec.hpp>
#include <eve/arch/limits.hpp>
#include <eve/ext/as_pack.hpp>
#include <eve/module/core/type/pack.hpp>

namespace eve
{
  template<std::size_t Cardinal>
  struct fixed : std::integral_constant< std::size_t, Cardinal>
  {
    static_assert( Cardinal == 1 || Cardinal % 2 == 0, "Cardinal must be a power of 2" );
    static constexpr bool is_default = false;
  };

  template<std::size_t Cardinal>
  struct defaulted : std::integral_constant< std::size_t, Cardinal>
  {
    static constexpr bool is_default = true;
  };

  template< typename Type
          , typename Size = defaulted<limits<EVE_CURRENT_API>::expected_cardinal<Type>>
          >
  using pack = ext::as_pack_t<Type,Size>;
}

#endif
