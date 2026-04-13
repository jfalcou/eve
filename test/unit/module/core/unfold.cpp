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
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::unfold", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::unfold(T()), (kumi::result::fill_t<eve::cardinal_v<T>, v_t>));
  TTS_EXPR_IS(eve::unfold(T(), v_t()), (kumi::result::fill_t<eve::cardinal_v<T>+1, v_t>));
  TTS_EXPR_IS(eve::unfold(T(), T(), v_t()), (kumi::result::fill_t<2*eve::cardinal_v<T>+1, v_t>));
};

//==================================================================================================
// Tests for eve::unfold
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::unfold(eve::wide)",
              eve::test::simd::all_types_wf16,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax))
             )
  <typename T>(T const& a0, T const& a1)
{
  using v_t = eve::element_type_t<T>;
  constexpr auto N = eve::cardinal_v<T>;
  auto gen =  [](auto x){
    auto g = [x](auto i){ return x.get(i); };
    return kumi::generate<N>(g) ;
  };
  TTS_EQUAL(eve::unfold(a0), gen(a0));
  TTS_EQUAL(eve::unfold(a1), gen(a1));
  TTS_EQUAL(eve::unfold(a1, v_t(1)), (kumi::push_back(gen(a1), v_t(1))));
  TTS_EQUAL(eve::unfold(a1, v_t(1), a0),  kumi::cat(kumi::push_back(gen(a1), v_t(1)), gen(a0)));
};
