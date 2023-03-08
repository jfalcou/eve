//==================================================================================================
/**
  EVE - Cbrtressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "measures.hpp"
#include <eve/module/dd.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

TTS_CASE_WITH( "Check behavior of cbrt on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-100, 100)
                             , tts::randoms(-100, 100)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  using e_t = typename T::value_type;
  using dd_t= eve::dd<e_t>;
  auto thresh = 2*eve::high(eve::eps(eve::as<eve::dd<e_t>>()));
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto x = dd_t(e, f);
      auto cbrtdd = eve::cbrt(eve::dd<e_t>(e, f));
      auto cbrt128 =  cbrt(tts::uptype(x));
      std::cout << "cbrtdd  = " << std::setprecision(20) << cbrtdd<< std::endl;
      std::cout << "cbrt128 = " <<cbrt128<< std::endl;
      std::cout << "diff " <<  (abs((tts::uptype(cbrtdd)-cbrt128)/cbrt128)) << "? < " << thresh<< std::endl;
      TTS_EXPECT ( (abs((tts::uptype(cbrtdd)-cbrt128)/cbrt128)) < thresh);
    }
      TTS_EQUAL(eve::cbrt(eve::inf(eve::as<dd_t>())), eve::inf(eve::as<dd_t>()));
      TTS_EQUAL(eve::cbrt(eve::minf(eve::as<dd_t>())), eve::minf(eve::as<dd_t>()));
      TTS_EXPECT(eve::is_nan(eve::cbrt(eve::nan(eve::as<dd_t>()))));
  }
};

TTS_CASE_WITH( "Check behavior of cbrt on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-100, 100)
                             , tts::randoms(-100, 100)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  if(a0.size() == 2 and sizeof(eve::element_type_t<T>) == 8)
  {
    auto z = make_dd(a0,a1);
    auto az = decltype(z)(eve::detail::map(eve::cbrt, z));
    auto cz = eve::cbrt(z);
//   std::cout << az << std::endl;
//   std::cout << eve::cbrt(z)<< std::endl;
    TTS_EQUAL ( cz, az);
//    std::cout << eve::abs(eve::cbrt(z)-az) << std::endl;
//  TTS_EQUAL (0, 0);
    std::cout << " ================================= " << std::endl;
    std::cout << az*az*az-z << std::endl;
    std::cout << cz*cz*cz-z << std::endl;
  }
//   dd < fa(0x1.8f05a2p+0, 0x0p+0);
//   eve::dd < T > b(0x1.8f05ap+0, 0x0p+0);
//   std::cout << std::hexfloat << a < "   " << b << std::endl;
 };
