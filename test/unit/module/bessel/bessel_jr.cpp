//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"

#include <eve/module/bessel.hpp>

TTS_CASE_TPL ( "Check eve::cyl_bessel_j over real, floating positive orsers"
             , eve::test::scalar::ieee_reals
              )
<typename T>(tts::type<T>)
{
  auto pr = tts::prec<T>(); //0.08, 0.0008);
  auto constexpr N = 11;
  using a_t  = std::array<T, 8 >;
  using aN_t = std::array<a_t, N >;
  a_t re{2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00, 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};
  aN_t resN8;
  //res are taken from octave 9.2.0 besselj outputs
  int p=0;
   resN8[p] = a_t{4.3049351732812502e-01,6.7139670714180388e-01,6.0684880800761865e-01,3.4788533475125594e-01,1.8843024746696045e-02,-2.5043719366491068e-01,-3.6767487332724130e-01,-3.0911683169597870e-01,};
    ++p; //1  1.500e+00
    resN8[p] = a_t{4.3309881918378326e-02,2.4029783912342725e-01,4.3581621392440240e-01,5.2473378154316941e-01,4.5885445154807680e-01,2.5784341908742220e-01,-2.4196645430744927e-03,-2.2337743182629205e-01,};
    ++p; //2  2.500e+00
    resN8[p] = a_t{2.6053018556586637e-03,4.9496810228477989e-02,1.6223862832956226e-01,3.0803189217770616e-01,4.2520967029982992e-01,4.5399778768129662e-01,3.6606176363185833e-01,1.8024523641157947e-01,};
    ++p; //3  3.500e+00
    resN8[p] = a_t{1.1181567593280482e-04,7.1862120189627081e-03,4.1356222339015938e-02,1.1699932716038511e-01,2.2696759732261662e-01,3.3952209101954944e-01,4.0915495746736158e-01,3.9669015914511840e-01,};
    ++p; //4  4.500e+00
    resN8[p] = a_t{3.7305827734485446e-06,8.0667390426096195e-04,8.0516989487386514e-03,3.3216145373417202e-02,8.7297807525433646e-02,1.7143764314418569e-01,2.7040150353959247e-01,3.5376074705300298e-01,};
    ++p; //5  5.500e+00
    resN8[p] = a_t{1.0180727065155908e-07,7.3853119385948162e-05,1.2704191543063208e-03,7.5612179899294009e-03,2.6477650331868271e-02,6.6514432216679673e-02,1.3164804961182436e-01,2.1558805690815591e-01,};
    ++p; //6  6.500e+00
    resN8[p] = a_t{2.3504837752892616e-09,5.7104089844679230e-06,1.6866028500813095e-04,1.4394370804259062e-03,6.6551452650667319e-03,2.1104134325150310e-02,5.1404839955978360e-02,1.0229091179117278e-01,};
    ++p; //7  7.500e+00
    resN8[p] = a_t{4.7026277642567685e-11,3.8219741213480387e-07,1.9335966344092155e-05,2.3573286237759720e-04,1.4310233603470818e-03,5.6839220535714096e-03,1.6854821372113148e-02,4.0139222569776326e-02,};
    ++p; //8  8.500e+00
    resN8[p] = a_t{8.3010683912351318e-13,2.2552197554149199e-08,1.9511827338590252e-06,3.3893309434077898e-05,2.6916131725786795e-04,1.3324000968421331e-03,4.7778979510655888e-03,1.3495307160105293e-02,};
    ++p; //9  9.500e+00
    resN8[p] = a_t{1.3109907764681585e-14,1.1899462857329262e-09,1.7586099449805452e-07,4.3447461137876957e-06,4.5022573002515367e-05,2.7681522177496506e-04,1.1950153319123841e-03,3.9800508382601945e-03,};
    ++p; //10  1.050e+01
    resN8[p] = a_t{1.8731930632173081e-16,5.6781874776346454e-11,1.4322498766290250e-08,5.0259730007473458e-07,6.7834850156136236e-06,5.1676012032692698e-05,2.6772233923114439e-04,1.0471862873838744e-03,};

  using eve::spherical;
  auto v0 = T(0.5);
  auto h =  eve::half(eve::as<T>());
  for(int j=0; j < 8 ; ++j)
  {
    auto c = re[j];
    auto fac = eve::sqrt(eve::pio_2(eve::as(c))*eve::rec(c));
    for(int i=0; i < N; ++i)
    {
      auto v =  v0+i;
//      std::cout<< "v " << v << " j " << j  << " c[" << i << "] = " << c << std::endl;
      auto res = resN8[i][j];
      TTS_RELATIVE_EQUAL(eve::bessel_j(v, c), res, pr);
      TTS_RELATIVE_EQUAL(eve::bessel_j[spherical](v, c), eve::bessel_j(v+h, c)*fac, tts::prec<T>());
    }
  }
};

TTS_CASE_TPL ( "Check eve::cyl_bessel_jn over real,  floating negative orders"
             , eve::test::scalar::ieee_reals
              )
<typename T>(tts::type<T>)
{
  auto pr = tts::prec<T>(0.08, 1.0e-6);
  auto constexpr N = 11;
  using a_t  = std::array<T, 8 >;
  using aN_t = std::array<a_t, N >;
  a_t re{2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00, 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};
  aN_t resN8;
  //res are taken from octave 9.2.0 besselj outputs
  int p=0;
  resN8[p] = a_t{1.1335888194515586e+00,7.3336528159689263e-01,3.0030732566423135e-01,-9.8695516096740737e-02,-3.5418670048346185e-01,-4.0747420838569076e-01,-2.7601759079687044e-01,-4.3042138962020651e-02,};
  ++p; //-1 -1.125e+00
  resN8[p] = a_t{-1.1417005172617154e+00,-6.8221301755057162e-01,-6.4479792172169104e-01,-4.8450115810282657e-01,-2.1148717038978893e-01,8.2490021579105829e-02,2.9341346761172082e-01,3.5308261517907791e-01,};
  ++p; //-2 -2.125e+00
  resN8[p] = a_t{7.4291650600113179e+00,8.0161400789189408e-01,5.5310168837918361e-01,5.5291535181814078e-01,5.0768545318572933e-01,3.5863143245069395e-01,1.2931085699100994e-01,-1.0973399260584971e-01,};
  ++p; //-3 -3.125e+00
  resN8[p] = a_t{-1.0410480449956532e+02,-2.7246465159899778e+00,-7.3795629922626738e-01,-4.9461977740846430e-01,-4.8453320897774221e-01,-4.8359096576738231e-01,-4.1554038810323041e-01,-2.6339617891468159e-01,};
  ++p; //-4 -4.125e+00
  resN8[p] = a_t{2.1614209286809337e+03,1.6227426717045464e+01,2.1599729411291513e+00,7.3515698518306849e-01,4.6919601652746090e-01,4.3674844545618391e-01,4.4782857093014189e-01,4.2631593841676496e-01,};
  ++p; //-5 -5.125e+00
  resN8[p] = a_t{-5.9334970734225877e+04,-1.3115162389963450e+02,-9.7442653268416262e+00,-2.0324823591583248e+00,-7.6413360920017503e-01,-4.6461289607827844e-01,-4.0547865860203081e-01,-4.1297045415037748e-01,};
  ++p; //-6 -6.125e+00
  resN8[p] = a_t{2.0251167458240376e+06,1.3280767182542079e+03,5.6592215058945328e+01,7.9452364237222790e+00,2.0573747880860225e+00,8.1648370843917262e-01,4.7576170699670683e-01,3.8771236062965153e-01,};
  ++p; //-7 -7.125e+00
  resN8[p] = a_t{-8.2632932150413990e+07,-1.6137788174714406e+04,-3.9805257848026417e+02,-3.8521328553590806e+01,-7.3658151501720113e+00,-2.1674727429690530e+00,-8.8965043266678212e-01,-5.0039039540986041e-01,};
  ++p; //-8 -8.125e+00
  resN8[p] = a_t{3.9230391603988414e+09,2.2863540477142608e+05,3.2800249869079730e+03,2.2077515186322316e+02,3.1801614208672419e+01,7.3115390776947748e+00,2.3414646631147704e+00,9.8354978063775400e-01,};
  ++p; //-9 -9.125e+00
  resN8[p] = a_t{-2.1241532158945352e+11,-3.6991875393609572e+06,-3.0955127443434161e+04,-1.4563104288536495e+03,-1.5933619481464311e+02,-2.9098977260330958e+01,-7.5656386285810013e+00,-2.5732026690831207e+00,};
  ++p; //-10 -1.012e+01
  resN8[p] = a_t{1.2918009024198029e+13,6.7281537188566044e+07,3.2903237256760558e+05,1.0853252067544734e+04,9.0622598429688787e+02,1.3244012802784195e+02,2.8341403108352626e+01,8.0474018945097345e+00,};
  using eve::spherical;
  auto v0 = T(-1.0/8.0);
  auto h =  eve::half(eve::as<T>());
  for(int j=0; j < 8; ++j)
  {
    auto c = re[j];
    auto fac = eve::sqrt(eve::pio_2(eve::as(c))*eve::rec(c));
    for(int i=0; i < N; ++i)
    {
      auto v =  v0-i;
//      std::cout<< "v " << v << " j " << j  << " c[" << i << "] = " << c << std::endl;
      auto res = resN8[i][j];
      TTS_RELATIVE_EQUAL(eve::bessel_j(v, c), res, pr);
      TTS_RELATIVE_EQUAL(eve::bessel_j[spherical](v, c), eve::bessel_j(v+h, c)*fac, tts::prec<T>());
    }
  }
};
