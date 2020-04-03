//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_AS_WIDE_HPP_INCLUDED
#define EVE_AS_WIDE_HPP_INCLUDED

#include <eve/forward.hpp>

namespace eve
{
  template<typename Type, typename Size>
  struct as_wide
  {
    using type = eve::wide<Type, Size>;
  };

  template<typename Type, typename N, typename Size>
  struct as_wide<wide<Type,N>,Size>
  {
    using type = wide<Type, Size>;
  };

  template<template<class...> class Type, typename... Ts, typename Size>
  struct as_wide< Type<Ts...>,Size>
  {
    using type = Type< typename as_wide<Ts,Size>::type... >;
  };

  template<typename Type, typename Size>
  using as_wide_t = typename as_wide<Type, Size>::type;
}

#endif
