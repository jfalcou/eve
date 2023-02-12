//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/doublereal.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>


TTS_CASE_WITH( "Check behavior of cos on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(20000000, 3.14*20000000)
                              , tts::randoms(0, +0.0001)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  using dd_t = eve::doublereal<e_t>;
  if constexpr(sizeof(e_t) == 8)
  {
     for(auto e : a0)
     {
       for(auto f : a1)
       {
         auto z = dd_t(e, f);
 //      std::cout << "e,  f " << e << " --- " << f << std::endl;
 //       auto hs = eve::half_circle(cos);
 //       auto sf = hs(z);
         auto sf  = eve::full_circle(eve::cos)(z);
         auto s   = (eve::cos)(z);  //dd_t(eve::cos(eve::high(z)));
         TTS_ULP_EQUAL(sf, s , 0.5);
       }
     }
//     auto pio4 = eve::pio_4(eve::as<dd_t>());
//     auto pio8 = eve::pio_4(eve::as<dd_t>())/2;
//     for (int i = 0; i < 16;  i++)
//     {
//       auto fs = eve::full_circle(eve::cos)(pio8+i*pio4);
//       auto s   = (eve::cos)(pio8+i*pio4);
//       std::cout << "fs " << fs << std::endl;
//       std::cout << " s " << s << std::endl;
//       TTS_ULP_EQUAL(fs, s, 0.5);
//     }
  }
};

// TTS_CASE_WITH( "Check behavior of cos on wide"
//              , eve::test::simd::ieee_reals
//              , tts::generate ( tts::randoms(-1.544*20000, 1.54*20000)
//                              , tts::randoms(-0.001, +0.001)
//                              )
//              )
//   <typename T>(T const& a0, T const& a1 )
// {
//   using e_t = typename T::value_type;
//   if constexpr(sizeof(e_t) == 8)
//   {
//     auto z = make_doublereal(a0,a1);
//     auto az = decltype(z)(eve::detail::map(eve::cos, z));
//     auto cz = eve::cos(z);
//     TTS_EQUAL ( cz, az);
//     TTS_ULP_EQUAL(cz, az, 0.5);
//   }
// };
