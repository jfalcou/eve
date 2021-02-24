//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/add.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <algorithm>

TTS_CASE_TPL("Check eve::add[if_not_(condition)] return type", EVE_TYPE)
{
  TTS_EXPR_IS( (eve::add[ eve::if_not_(T()) ](T(), T())), T);
  TTS_EXPR_IS( (eve::add[ eve::if_not_(eve::logical<T>()) ](T(), T())), T);
  TTS_EXPR_IS( (eve::add[ eve::if_not_(true) ](T(), T())), T);
}

TTS_CASE_TPL("Check eve::add[if_not_(condition)] behavior", EVE_TYPE)
{
  T tv{2};
  T fv{3};
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  // All basic TRUE
  TTS_EQUAL(eve::add[ eve::if_not_(1)    ](tv, fv) , tv);
  TTS_EQUAL(eve::add[ eve::if_not_(1.0)  ](tv, fv) , tv);
  TTS_EQUAL(eve::add[ eve::if_not_(true) ](tv, fv) , tv);
  TTS_EQUAL(eve::add[ eve::if_not_(t)    ](tv, fv) , tv);

  // All basic FALSE
  TTS_EQUAL(eve::add[ eve::if_not_(0)    ](tv, fv) , tv + fv );
  TTS_EQUAL(eve::add[ eve::if_not_(0.0)  ](tv, fv) , tv + fv );
  TTS_EQUAL(eve::add[ eve::if_not_(false)](tv, fv) , tv + fv );
  TTS_EQUAL(eve::add[ eve::if_not_(f)    ](tv, fv) , tv + fv );

  // Mixed case
  eve::as_logical_t<T> m;
  bool k = true;
  #if defined(EVE_SIMD_TESTS)
  for(std::size_t i=0;i<eve::cardinal_v<T>;++i)
  {
    m.set(i, k);
    k = !k;
  }
  #else
  m = k;
  #endif

  TTS_EQUAL(eve::add[ eve::if_not_(m )](tv, fv) , eve::if_else(m,tv, eve::add(tv, fv)) );
}
