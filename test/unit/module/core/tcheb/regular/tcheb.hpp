//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/module/core/detail/generic/tcheb.hpp>
#include <tts/tests/relation.hpp>
#include <vector>
#include <eve/function/average.hpp>
#include <eve/function/fma.hpp>
#include <eve/constant/zero.hpp>

template < typename T> auto mytcheb(T x, std::vector<eve::element_type_t<T> > const & coefs)
{
  auto p = coefs.begin();
  T b0 = T(*p++);
  T b1 = eve::zero(eve::as(b0));
  T b2 = eve::zero(eve::as(b0)); ;

  while(p!= coefs.end())
  {
    b2 = -b1;
    b1 = b0;
    b0 = eve::fma(x, b1, b2 + *p++);
  }
  return eve::average(b0, b2);
}



TTS_CASE_TPL("Check eve::horn behavior", EVE_TYPE)
{
  using elt_t = eve::element_type_t<T>;
  std::vector<elt_t> v{1, 2, 3, 4};

  TTS_EQUAL(mytcheb(T(1.0), v), T(1.5));
  TTS_EQUAL(mytcheb(T(2.0), v), T(8.0));
  TTS_EQUAL(mytcheb(T(3.0), v), T(22.5));

}
