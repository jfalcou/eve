//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include "../complex/measures.hpp"
#include <eve/module/fft/regular/revbin_permute.hpp>


TTS_CASE_TPL("Check revbin_permute", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, std::uint8_t> && eve::cardinal_v<T> == 1)
  {
    auto pr = [](auto name, auto v){
      std::cout << name << " = (";
      for(size_t i=0; i < v.size() ; ++i) std::cout << v[i] << " ";
      std::cout << ")\n";
    };

    size_t n = 16;
    std::vector<int> vi(n);
    for(size_t i=0; i < n ; ++i) vi[i] = i;
    pr("vi ", vi);
    std::cout << " =============================== " << std::endl;

    vi = eve::revbin_permute(vi);
    pr("vi  ", vi);
    vi = eve::revbin_permute(vi);
    pr("rvi ", vi);
    std::cout << " =============================== " << std::endl;
    vi= eve::raw(eve::revbin_permute)(vi);
    pr("vi  ", vi);
    vi= eve::raw(eve::revbin_permute)(vi);
    pr("rvi ", vi);
    TTS_EQUAL(0, 0);
  };
  };
