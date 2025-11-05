//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <cmath>

 //==================================================================================================
 //= Types tests
 //==================================================================================================
//  TTS_CASE_TPL("Check return types of eve::next", eve::test::simd::ieee_reals_wf16)
//  <typename T>(tts::type<T>)
//  {
//    using v_t  = eve::element_type_t<T>;
//    using i_t  = eve::as_integer_t<T, signed>;
//    using u_t  = eve::as_integer_t<T, unsigned>;
//    using si_t = eve::as_integer_t<v_t, signed>;
//    using su_t = eve::as_integer_t<v_t, unsigned>;

//    TTS_EXPR_IS(eve::next(T()), T);
//    TTS_EXPR_IS(eve::next(T(), i_t()), T);
//    TTS_EXPR_IS(eve::next(T(), u_t()), T);
//    TTS_EXPR_IS(eve::next(T(), si_t()), T);
//    TTS_EXPR_IS(eve::next(T(), su_t()), T);
//  };

 //==================================================================================================
 //= Tests for eve::next
 //==================================================================================================
TTS_CASE_WITH("Check behavior of eve::next(eve::wide)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
  <typename T>(T const& )
{
  using v_t = eve::element_type_t<T>;
  if constexpr(sizeof(v_t) == 2)
  {
    using w_t = eve::wide<eve::float16_t>;
    std::cout << "w_t -> " << tts::typename_<w_t> << std::endl;
//    std::cout << "a0  -> " << a0 << std::endl;
//    w_t one(2.345f); //= eve::one(eve::as<w_t>());
//    w_t one(eve::inf(eve::as<w_t>()));
//    w_t one(eve::nan(eve::as<w_t>()));
    w_t one(eve::mzero(eve::as<w_t>()));
//     w_t one(eve::mindenormal(eve::as<w_t>()));
    std::cout << std::hexfloat <<  "one     ->  " << one << std::endl;
    auto nextone = eve::next(one);
    std::cout << std::hexfloat <<  "nextone  ->  " << nextone << std::endl;
    auto rnextone = eve::next[eve::raw](one);
     std::cout << std::hexfloat <<  "rnextone  -> " << rnextone << std::endl;
//     TTS_IEEE_EQUAL(rnextone, nextone);
    auto pnextone = eve::next[eve::pedantic](one);
    std::cout << std::hexfloat <<  "pnextone  -> " << pnextone << std::endl;



  }
};
