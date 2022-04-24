/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <algorithm>
#include <eve/module/compensated.hpp>
#include <vector>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of asum"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::asum(std::vector<v_t>())  , v_t);

//   TTS_EXPR_IS( eve::asum(T(), T(), T()  )  , T);
//   TTS_EXPR_IS( eve::asum(T(), v_t(), T())  , T);
//   TTS_EXPR_IS( eve::asum(v_t(), T(), T())  , T);
//   TTS_EXPR_IS( eve::asum(T(), T(), v_t() ) , T);
//   TTS_EXPR_IS( eve::asum(v_t(), v_t(), T()) , T);
//   TTS_EXPR_IS( eve::asum(v_t(), T(), v_t()) , T);
//   TTS_EXPR_IS( eve::asum(v_t(), v_t(), v_t()) , v_t);
};

//==================================================================================================
// asum tests
//==================================================================================================

EVE_TEST( "Check behavior of asum on all types full range"
        , eve::test::simd::ieee_reals
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(  T const&)
{
  using eve::asum;
//   using eve::detail::map;
//   using eve::abs;
//   using v_t = eve::element_type_t<T>;
//   auto m = [](auto a, auto b, auto c)-> v_t {return abs(a)+abs(b)+abs(c); };
//   auto s = [](auto a)                -> v_t {return eve::sign(a);  };
//   TTS_ULP_EQUAL(asum((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
//   TTS_ULP_EQUAL(eve::pedantic(asum)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
//   TTS_ULP_EQUAL(eve::diff_1st(asum)((a0), (a1), (a2)), map(s, a0), 2);
//   TTS_ULP_EQUAL(eve::diff_2nd(asum)((a0), (a1), (a2)), map(s, a1), 2);
//   TTS_ULP_EQUAL(eve::diff_3rd(asum)((a0), (a1), (a2)), map(s, a2), 2);

  using v_t = eve::element_type_t<T>;
  std::vector<v_t> vd(100000);
  for(size_t i=0; i < vd.size() ; ++i) vd[i] = 1/v_t(i+1);
  //  std::cout << eve::asum(vd) << std::endl;
  //  std::cout << eve::numeric(eve::asum)(vd)<< std::endl;

  __float128 s(0);
  for(size_t i=0; i < 100000 ; ++i){
    s+= __float128(1/v_t(i+1));
  }
//  std::cout << double(s) << std::endl;
  TTS_ULP_EQUAL(v_t(s), eve::asum(vd), 0.5);
  TTS_ULP_EQUAL(v_t(s), eve::comp(eve::asum)(vd), 0.5);

};
