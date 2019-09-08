//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_UPGRADE_HPP_INCLUDED
#define EVE_DETAIL_UPGRADE_HPP_INCLUDED

#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve::detail
{
  template < typename T, bool is = std::is_integral_v<T>>
  struct upgrade 
  {
    using type = T; 
  }; 

  template < typename T>
  struct upgrade < T, true>
  {
    template<std::size_t Size, bool Sign, typename Dummy = void>
    struct fetch;

    template<typename Dummy>
    struct fetch<1, true, Dummy>
    {
      using type = std::int16_t;
    };
    template<typename Dummy>
    struct fetch<2, true, Dummy>
    {
      using type = std::int32_t;
    };
    template<typename Dummy>
    struct fetch<4, true, Dummy>
    {
      using type = std::int64_t;
    };
    template<typename Dummy>
    struct fetch<8, true, Dummy>
    {
      using type = std::int64_t;
    };

    template<typename Dummy>
    struct fetch<1, false, Dummy>
    {
      using type = std::uint16_t;
    };
    template<typename Dummy>
    struct fetch<2, false, Dummy>
    {
      using type = std::uint32_t;
    };
    template<typename Dummy>
    struct fetch<4, false, Dummy>
    {
      using type = std::uint64_t;
    };
    template<typename Dummy>
    struct fetch<8, false, Dummy>
    {
      using type = std::uint64_t;
    };
    
    using sel = fetch<sizeof(T), std::is_signed_v<T>>;
    using type = typename sel::type;
    
  }; 
    
  template < typename T>
  struct upgrade < T, false>
  {
    using type = double; 
  };
  
  template<typename T>
  using upgrade_t = typename upgrade<T>::type;

  
}

#endif
