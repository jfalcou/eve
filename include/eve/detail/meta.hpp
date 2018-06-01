//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_DETAIL_META_HPP_INCLUDED
#define EVE_DETAIL_META_HPP_INCLUDED

#include <type_traits>
#include <cstdint>

namespace eve { namespace detail
{
  // Types list helper
  template<typename... Types> struct types {};

  // Type identity
  template<typename T> struct always { using type = T; };

  // Normalize integral types to std::*int*_t types
  template<typename T> struct normalize
  {
    template<std::size_t Size, bool Sign, typename Dummy = void> struct fetch;

    template<typename Dummy> struct fetch<1,true,Dummy> { using type = std::int8_t;  };
    template<typename Dummy> struct fetch<2,true,Dummy> { using type = std::int16_t; };
    template<typename Dummy> struct fetch<4,true,Dummy> { using type = std::int32_t; };
    template<typename Dummy> struct fetch<8,true,Dummy> { using type = std::int64_t; };

    template<typename Dummy> struct fetch<1,false,Dummy> { using type = std::uint8_t;  };
    template<typename Dummy> struct fetch<2,false,Dummy> { using type = std::uint16_t; };
    template<typename Dummy> struct fetch<4,false,Dummy> { using type = std::uint32_t; };
    template<typename Dummy> struct fetch<8,false,Dummy> { using type = std::uint64_t; };

    using selection = std::conditional_t< std::is_integral_v<T> && !std::is_same_v<T,bool>
                                        , fetch<sizeof(T),std::is_signed_v<T>>
                                        , always<T>
                                        >;

    using type = typename selection::type;
  };
} }

#endif
