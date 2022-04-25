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
#include <iomanip>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of sum"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::sum(std::vector<v_t>())  , v_t);

//   TTS_EXPR_IS( eve::sum(T(), T(), T()  )  , T);
//   TTS_EXPR_IS( eve::sum(T(), v_t(), T())  , T);
//   TTS_EXPR_IS( eve::sum(v_t(), T(), T())  , T);
//   TTS_EXPR_IS( eve::sum(T(), T(), v_t() ) , T);
//   TTS_EXPR_IS( eve::sum(v_t(), v_t(), T()) , T);
//   TTS_EXPR_IS( eve::sum(v_t(), T(), v_t()) , T);
//   TTS_EXPR_IS( eve::sum(v_t(), v_t(), v_t()) , v_t);
};

//==================================================================================================
// sum tests
//==================================================================================================

EVE_TEST( "Check behavior of sum on all types full range"
        , eve::test::simd::ieee_reals
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(  T const&)
{
  using eve::sum;
  using v_t = eve::element_type_t<T>;
  constexpr size_t N = 1000000;
  {
    std::vector<v_t> vd(N);
    v_t sign(1);
    for(size_t i=0; i < vd.size() ; ++i, sign = -sign) vd[i] = sign/v_t(N-i+1);

    __float128 s(0);
    __float128 signl(1);
    for(size_t i=0; i < vd.size() ; ++i, signl = -signl){
      s+= __float128(signl/v_t(N-i+1));
    }
    auto as = eve::sum(vd);
    auto cas= eve::comp(eve::sum)(vd);
    auto fas= eve::faithfull(eve::sum)(vd);
    std::cout << "s    " << std::setprecision(16) << double(s)  << std::endl;
    std::cout << "as   " << std::setprecision(sizeof(v_t)*2) << as << " -> " << eve::ulpdist( v_t(s),  as) << std::endl;
    std::cout << "cas  " << std::setprecision(sizeof(v_t)*2) << cas<< " -> " << eve::ulpdist( v_t(s), cas) << std::endl;
    std::cout << "fas  " << std::setprecision(sizeof(v_t)*2) << fas<< " -> " << eve::ulpdist( v_t(s), fas) << std::endl;
    TTS_ULP_EQUAL(v_t(s), as,  50);
    TTS_ULP_EQUAL(v_t(s), cas, 25);
    TTS_ULP_EQUAL(v_t(s), fas, 1);
  }

  std::cout << eve::faithfull(eve::sum)(1.0, 10.0, 2.45) << std::endl;

//  {
//     std::vector<v_t> vd(N);
//     v_t s(1);
//     v_t f(1/v_t(3));

//     for(size_t i=0; i < vd.size() ; ++i, s*= -f) vd[i] = s;

//     __float128 s(0);
//     __float128 signl(1);
//     for(size_t i=0; i < vd.size() ; ++i, signl = -signl){
//       s+= __float128(signl/v_t(i+1));
//     }
//     auto as = eve::sum(vd);
//     auto cas= eve::comp(eve::sum)(vd);
//     std::cout << "log_2" << std::setprecision(16) << eve::log_2(eve::as(as)) << std::endl;
//     std::cout << "s    " << std::setprecision(16) << double(s)  << std::endl;
//     std::cout << "as   " << std::setprecision(sizeof(v_t)*2) << as << " -> " << eve::ulpdist( v_t(s),  as) << std::endl;
//     std::cout << "cas  " << std::setprecision(sizeof(v_t)*2) << cas<< " -> " << eve::ulpdist( v_t(s), cas) << std::endl;
//     TTS_ULP_EQUAL(v_t(s), as,  50);
//     TTS_ULP_EQUAL(v_t(s), cas, 25);
//     TTS_ULP_EQUAL(eve::log_2(eve::as(as)), as,  50);
//     TTS_ULP_EQUAL(eve::log_2(eve::as(as)), cas, 25);
//   }



};
