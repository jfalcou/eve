//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_EXT_AS_PACK_HPP_INCLUDED
#define EVE_EXT_AS_PACK_HPP_INCLUDED

#include <eve/arch/spec.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/detail/aggregate_pack.hpp>

namespace eve { namespace ext
{
  template< typename Type, typename Size, typename EnableIf = void>
  struct as_pack;

  template< typename Type, typename Size>
  struct as_pack< Type, Size
                , std::enable_if_t<(Size::value > expected_cardinal_v<Type>)>
                >
  {
    using type = detail::aggregate_pack < typename as_pack<Type,typename Size::split_type>::type
                                        , Size::value
                                        >;
  };

  template< typename Type, typename Size>
  using as_pack_t = typename as_pack<Type,Size>::type;
} }

#endif
