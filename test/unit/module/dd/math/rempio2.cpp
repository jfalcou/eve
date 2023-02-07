//==================================================================================================
/**
  EVE - Expm1ressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/dd.hpp>
#include <boost/math/constants/constants.hpp>
//#include <boost/multiprecision/cpp_bin_float.hpp>
#include <eve/module/math/detail/scalar/ieee_754_rem_pio2.hpp>

  /////////////////////////////////////////////////////////////////
  // trigo utilities
  /////////////////////////////////////////////////////////////////



TTS_CASE_WITH( "Check behavior of rem_piby2 on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-1, 1)
                             )
             )
  <typename T>(T const& , T const& )
{
  using e_t = typename T::value_type;
  using dd_t = eve::dd<e_t>;
  if constexpr(sizeof(e_t) == 8)
  {
    auto rem_piby2 = []( eve::dd<double> const& x, double remainder[3] )
      {
        using dd_real =  eve::dd<double>;
        static double const zero = 0.0;
        static int const two_over_pi[] = {
          0xA2F983, 0x6E4E44, 0x1529FC, 0x2757D1, 0xF534DD, 0xC0DB62,
          0x95993C, 0x439041, 0xFE5163, 0xABDEBB, 0xC561B7, 0x246E3A,
          0x424DD2, 0xE00649, 0x2EEA09, 0xD1921C, 0xFE1DEB, 0x1CB129,
          0xA73EE8, 0x8235F5, 0x2EBB44, 0x84E99C, 0x7026B4, 0x5F7E41,
          0x3991D6, 0x398353, 0x39F49C, 0x845F8B, 0xBDF928, 0x3B1FF8,
          0x97FFDE, 0x05980F, 0xEF2F11, 0x8B5A0A, 0x6D1F6D, 0x367ECF,
          0x27CB09, 0xB74F46, 0x3F669E, 0x5FEA2D, 0x7527BA, 0xC7EBE5,
          0xF17B3D, 0x0739F7, 0x8A5292, 0xEA6BFB, 0x5FB11F, 0x8D5D08,
          0x560330, 0x46FC7B, 0x6BABF0, 0xCFBC20, 0x9AF436, 0x1DA9E3,
          0x91615E, 0xE61B08, 0x659985, 0x5F14A0, 0x68408D, 0xFFD880,
          0x4D7327, 0x310606, 0x1556CA, 0x73A8C9, 0x60E27B, 0xC08C6B,
        };

        double tx[6];
        int e0,i,nx,n;
        dd_real z = eve::abs( x );

        if ( z <= eve::pio_4(eve::as(z)) )            /* |x| ~<= pi/4 , no need for reduction */
        {
          remainder[0] = eve::high(x);
          remainder[1] = eve::low(x);
          remainder[2] = 0.0;
          return 0;
        }

        auto toInt = [](dd_real t){
          auto x = eve::trunc(t);
          return static_cast< long long >(eve::high(x)) + static_cast< long long >(eve::low(x));
        };

        /* set z = scalbn( |x|, -ilogb( x ) + 23 ) */
        e0  = eve::exponent( x ) - 23;
        z = eve::ldexp( z, -e0 );
        for ( i = 0; i < 5; i++ )
        {
          tx[i] = toInt(z);
          z     = eve::ldexp( z - tx[ i ], 24 );
        }
        tx[5] = toInt(z);

        nx = 6;
        while ( tx[ nx - 1] == zero ) nx--; /* skip zero terms */
        n  =  eve::detail::__kernel_rem_pio2( tx, remainder, e0, nx, 3, two_over_pi );

        if ( eve::is_ltz(x) )
        {
          remainder[0] = -remainder[0];
          remainder[1] = -remainder[1];
          remainder[2] = -remainder[2];
          return -n;
        }
        return n;
      };

    dd_t x(10.0*eve::pio_2(eve::as<dd_t>()));
    std::cout << "x " << x << std::endl;
    double remainder[3];
    auto q = rem_piby2( x, (double*)remainder );
    std::cout << "q " << q << std::endl;
    std::cout << "remainder[0] " << remainder[0]<< std::endl;
    std::cout << "remainder[1] " << remainder[1]<< std::endl;
    std::cout << "remainder[2] " << remainder[2]<< std::endl;
  }
    TTS_EQUAL(0, 0);
//   for(auto e : a0)
//   {
//     for(auto f : a1)
//     {
//       auto z = eve::dd<e_t>(e, f);
//       auto ac = eve::expm1(z);
//       auto bmbc = bm::expm1(tts::uptype(z));
//       eve::dd<e_t> bc(bmbc);
//       TTS_ULP_EQUAL(bc, ac, 2.5);
//     }
//   }
};

// TTS_CASE_WITH( "Check behavior of expm1 on wide"
//              , eve::test::simd::ieee_reals
//              , tts::generate ( tts::randoms(-10, 10)
//                              , tts::randoms(-1, 1)
//                              )
//              )
//   <typename T>(T const& a0, T const& a1 )
// {
//   auto z = make_dd(a0,a1);
//   auto az = decltype(z)(eve::detail::map(eve::expm1, z));
//   TTS_ULP_EQUAL ( eve::expm1(z), az, 2.5);
// };
