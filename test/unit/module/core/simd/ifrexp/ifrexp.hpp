//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IFREXP_HPP
#define IFREXP_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/wide.hpp>
#include <eve/function/load.hpp>
#include <eve/detail/meta.hpp>

using eve::fixed;

TTS_CASE_TPL("Check raw_(ifrexp) behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using t_t =  wide<Type, T>; 
  using i_t =  eve::detail::as_integer_t<T>;
  using wi_t =  eve::detail::as_integer_t<t_t>;
  t_t lhs([](auto i, auto) { return i; }), rhs([](auto i, auto c) { return Type(i); });
  Type m[T::value];
  i_t e[T::value];
  for(int i=0; i < T::value ; ++i)
  {
    std::tie(m[i], e[i]) = eve::raw_(eve::ifrexp)(Type(i+1));
  }
  t_t refm([m](auto i, auto){return m[i+1]; }); 
  wi_t refe([e](auto i, auto){return e[i+1]; }); 
  auto [vm, ve] =  eve::raw_(eve::ifrexp)(lhs); 
  TTS_EQUAL(refm, vm);
  TTS_EQUAL(refe, ve);
}

TTS_CASE_TPL("Check ifrexp behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using t_t =  wide<Type, T>; 
  using i_t =  eve::detail::as_integer_t<T>;
  using wi_t =  eve::detail::as_integer_t<t_t>;
  t_t lhs([](auto i, auto) { return i; }), rhs([](auto i, auto c) { return Type(i); });
  Type m[T::value];
  i_t e[T::value];
  for(int i=0; i < T::value ; ++i)
  {
    std::tie(m[i], e[i]) = eve::ifrexp(Type(i));
  }
  t_t refm([m](auto i, auto){return m[i]; }); 
  wi_t refe([e](auto i, auto){return e[i]; }); 
  auto [vm, ve] =  eve::ifrexp(lhs); 
  TTS_EQUAL(refm, vm);
  TTS_EQUAL(refe, ve);
}

TTS_CASE_TPL("Check pedantic_(ifrexp) behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using t_t =  wide<Type, T>; 
  using i_t =  eve::detail::as_integer_t<T>;
  using wi_t =  eve::detail::as_integer_t<t_t>;
  t_t lhs([](auto i, auto) { return i; }), rhs([](auto i, auto c) { return Type(i); });
  Type m[T::value];
  i_t e[T::value];
  for(int i=0; i < T::value ; ++i)
  {
    std::tie(m[i], e[i]) = eve::pedantic_(eve::ifrexp)(Type(i));
  }
  t_t refm([m](auto i, auto){return m[i]; }); 
  wi_t refe([e](auto i, auto){return e[i]; }); 
  auto [vm, ve] =  eve::pedantic_(eve::ifrexp)(lhs); 
  TTS_EQUAL(refm, vm);
  TTS_EQUAL(refe, ve);
}
#endif
