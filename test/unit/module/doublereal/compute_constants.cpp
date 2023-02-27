//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "measures.hpp"
#include <eve/module/doublereal.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

eve::doublereal<double> cvt(boost::multiprecision::cpp_bin_float_quad a)
{
  double h = double(a);
  double l = double(a-h);
  return eve::doublereal<double>(h, l);
}
eve::doublereal<float> cvt(double a)
{
  float h = float(a);
  float l = float(a-h);
  return eve::doublereal<float>(h, l);
}

TTS_CASE_WITH( "Check behavior of exp on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& , T const& )
{
  using boost::multiprecision::cpp_bin_float_quad;
  using f128 = cpp_bin_float_quad;
   using e_t = T::value_type;
   using dd_t = typename eve::doublereal<e_t>;
   dd_t ct = eve::pio_2(eve::as<dd_t>());
   std::cout << "ct " << ct << std::endl;
    auto zdr = tts::uptype(ct);
   auto zbm = bm::atan(f128(1))*2;

   dd_t zbr_small, zbr_large;
   if (zdr < zbm)
   {
     zbr_small = ct;
     zbr_large = eve::next(ct);
   }
   else if (zdr ==  zbm)
   {
     zbr_small = ct;
     zbr_large = ct;
   }
   else if (zdr > zbm)
   {
     zbr_small = eve::prev(ct);
     zbr_large = ct;
   }
   std::cout << "small " <<  zbr_small << std::endl;
   std::cout << "large " <<  zbr_large << std::endl;
   TTS_EQUAL(0, 0);
};
