//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
//#include "measures.hpp"
#include <eve/module/core.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/dd.hpp>

// TTS_CASE_TPL( "Check dd::operator+", eve::test::scalar::ieee_reals)
// <typename T>(tts::type<T>)
// {
//   using dd_t   = eve::dd<T>;
//   using w_t   = eve::wide<T>;
//   using wdd_t  = eve::wide<dd_t>;
//   using eve::ddhi;
//   using eve::ddlo;
//   {
//     dd_t z1(1, eve::eps(eve::as<T>())/2);
//     dd_t z1b(z1);
//     dd_t z2(1, eve::eps(eve::as<T>()));
//     dd_t z3(eve::eps(eve::as<T>())/2, 0);
//     std::cout << std::setprecision(20) << "z1 " << z1 << std::endl;
//     std::cout << std::setprecision(20) << "z3 " << z3 << std::endl;
//     z1+= z3;
//     std::cout << std::setprecision(20) << "z1 " << z1 << std::endl;
//     std::cout << std::setprecision(20) << "z2 " << z2 << std::endl;
//     TTS_ULP_EQUAL(ddhi(z1), ddhi(z2), 0.5);
//     TTS_ULP_EQUAL(ddlo(z1), eve::zero(eve::as<T>()), 0.0);
//     T z4(eve::eps(eve::as<T>())/2);
//     z1b += z4;
//     TTS_ULP_EQUAL(ddhi(z1b), ddhi(z2), 0.5);
//     TTS_ULP_EQUAL(ddlo(z1b), eve::zero(eve::as<T>()), 0.0);

//     dd_t z2b(T(0));
//     int N = (sizeof(T) == 4) ? 40 : 60;
//     std::uint64_t a = (1ull << N) +12ull;

//     std::cout << "a " << a << std::endl;
//     z2b += a;
//     TTS_ULP_EQUAL(ddhi(z2b), T((1ull << N)), 0.5) << std::setprecision(20) << "hi " << ddhi(z2b) << '\n';
//     TTS_ULP_EQUAL(ddlo(z2b), T(12), 0.0) << std::setprecision(20) << "lo " << ddlo(z2b) << '\n';
//     std::cout << z2b << std::endl;
//   }
//   {
//     wdd_t z1(1, eve::eps(eve::as<T>())/2);
//     wdd_t z1b(z1);
//     wdd_t z2(1, eve::eps(eve::as<T>()));
//     wdd_t z3(eve::eps(eve::as<T>())/2, 0);
//     std::cout << std::setprecision(20) << "z1 " << z1 << std::endl;
//     std::cout << std::setprecision(20) << "z3 " << z3 << std::endl;
//     z1+= z3;
//     std::cout << std::setprecision(20) << "z1 " << z1 << std::endl;
//     std::cout << std::setprecision(20) << "z2 " << z2 << std::endl;
//     TTS_ULP_EQUAL(ddhi(z1), ddhi(z2), 0.5);
//     TTS_ULP_EQUAL(ddlo(z1), eve::zero(eve::as<w_t>()), 0.0);
//     w_t z4(eve::eps(eve::as<w_t>())/2);
//     z1b += z4;
//     TTS_ULP_EQUAL(ddhi(z1b), ddhi(z2), 0.5);
//     TTS_ULP_EQUAL(ddlo(z1b), eve::zero(eve::as<w_t>()), 0.0);

//     wdd_t z2b(T(0));
//     int N = (sizeof(T) == 4) ? 40 : 60;
//     std::uint64_t a = (1ull << N) +12ull;

//     std::cout << "a " << a << std::endl;
//     z2b += a;
//     TTS_ULP_EQUAL(ddhi(z2b), w_t((1ull << N)), 0.5) << std::setprecision(20) << "hi " << ddhi(z2b) << '\n';
//     TTS_ULP_EQUAL(ddlo(z2b), w_t(12), 0.0) << std::setprecision(20) << "lo " << ddlo(z2b) << '\n';
//     std::cout << z2b << std::endl;
//   }

// };

// TTS_CASE_TPL( "Check dd::operator-", eve::test::scalar::ieee_reals)
// <typename T>(tts::type<T>)
// {
//   using dd_t   = eve::dd<T>;
//   using eve::ddhi;
//   using eve::ddlo;
//   {
//     dd_t z1(1, eve::eps(eve::as<T>())/2);
//     dd_t z1b(z1);
//     dd_t z2(1, eve::eps(eve::as<T>()));
//     dd_t z3(eve::eps(eve::as<T>())/2, 0);
//     std::cout << std::setprecision(20) << "z1 " << z1 << std::endl;
//     std::cout << std::setprecision(20) << "z3 " << z3 << std::endl;
//     z1-= z3;
//     std::cout << std::setprecision(20) << "z1 " << z1 << std::endl;
//     std::cout << std::setprecision(20) << "z2 " << z2 << std::endl;
//     TTS_ULP_EQUAL(ddhi(z1), ddhi(z2), 0.5);
//     TTS_ULP_EQUAL(ddlo(z1), eve::zero(eve::as<T>()), 0.0);
//     T z4(eve::eps(eve::as<T>())/2);
//     z1b -= z4;
//     TTS_ULP_EQUAL(ddhi(z1b), ddhi(z2), 0.5);
//     TTS_ULP_EQUAL(ddlo(z1b), eve::zero(eve::as<T>()), 0.0);

//     dd_t z2b(T(0));
//     int N = (sizeof(T) == 4) ? 40 : 60;
//     std::uint64_t a = -(1ll << N) -12ll;

//     std::cout << "a " << a << std::endl;
//     z2b -= a;
//     TTS_ULP_EQUAL(ddhi(z2b), T((1ull << N)), 0.5) << std::setprecision(20) << "hi " << ddhi(z2b) << '\n';
//     TTS_ULP_EQUAL(ddlo(z2b), T(12), 0.0) << std::setprecision(20) << "lo " << ddlo(z2b) << '\n';
//     std::cout << z2b << std::endl;
//   }
//   {
//   using w_t   = eve::wide<T>;
//   using wdd_t  = eve::wide<dd_t>;
//     wdd_t z1(1, eve::eps(eve::as<T>())/2);
//     wdd_t z1b(z1);
//     wdd_t z2(1, eve::eps(eve::as<T>()));
//     wdd_t z3(eve::eps(eve::as<T>())/2, 0);
//     std::cout << std::setprecision(20) << "z1 " << z1 << std::endl;
//     std::cout << std::setprecision(20) << "z3 " << z3 << std::endl;
//     z1-= z3;
//     std::cout << std::setprecision(20) << "z1 " << z1 << std::endl;
//     std::cout << std::setprecision(20) << "z2 " << z2 << std::endl;
//     TTS_ULP_EQUAL(ddhi(z1), ddhi(z2), 0.5);
//     TTS_ULP_EQUAL(ddlo(z1), eve::zero(eve::as<w_t>()), 0.0);
//     w_t z4(eve::eps(eve::as<w_t>())/2);
//     z1b -= z4;
//     TTS_ULP_EQUAL(ddhi(z1b), ddhi(z2), 0.5);
//     TTS_ULP_EQUAL(ddlo(z1b), eve::zero(eve::as<w_t>()), 0.0);

//     wdd_t z2b(T(0));
//     int N = (sizeof(T) == 4) ? 40 : 60;
//     std::int64_t a = -(1ll << N) - 12ll;

//     std::cout << "a " << a << std::endl;
//     z2b -= a;
//     TTS_ULP_EQUAL(ddhi(z2b), w_t((1ll << N)), 0.5) << std::setprecision(20) << "hi " << ddhi(z2b) << '\n';
//     TTS_ULP_EQUAL(ddlo(z2b), w_t(12), 0.0) << std::setprecision(20) << "lo " << ddlo(z2b) << '\n';
//     std::cout << z2b << std::endl;
//   }
// };


// TTS_CASE_TPL( "Check dd::operator*", eve::test::scalar::ieee_reals)
// <typename T>(tts::type<T>)
// {
//   using dd_t   = eve::dd<T>;
//   using eve::ddhi;
//   using eve::ddlo;
//   {
//     dd_t z1(1, eve::eps(eve::as<T>()));
//     dd_t z1b(z1);
//     dd_t z2(eve::eps(eve::as<T>()), eve::sqr(eve::eps(eve::as<T>())));
//     dd_t z3(eve::eps(eve::as<T>()), 0);
//     std::cout << std::setprecision(20) << "z1 " << z1 << std::endl;
//     std::cout << std::setprecision(20) << "z3 " << z3 << std::endl;
//     z1*= z3;
//     std::cout << std::setprecision(20) << "z1 " << z1 << std::endl;
//     std::cout << std::setprecision(20) << "z2 " << z2 << std::endl;
//     TTS_ULP_EQUAL(ddhi(z1), ddhi(z2), 0.5);
//     TTS_ULP_EQUAL(ddlo(z1), eve::zero(eve::as<T>()), 0.0);
//     T z4(eve::eps(eve::as<T>()));
//     z1b *= z4;
//     TTS_ULP_EQUAL(ddhi(z1b), ddhi(z2), 0.5);
//     TTS_ULP_EQUAL(ddlo(z1b), eve::zero(eve::as<T>()), 0.0);

//     dd_t z2b(T(1));
//     int N = (sizeof(T) == 4) ? 40 : 60;
//     std::uint64_t a = (1ll << N) + 12ll;

//     std::cout << "a " << a << std::endl;
//     z2b *= a;
//     TTS_ULP_EQUAL(ddhi(z2b), T((1ull << N)), 0.5) << std::setprecision(20) << "hi " << ddhi(z2b) << '\n';
//     TTS_ULP_EQUAL(ddlo(z2b), T(12), 0.0) << std::setprecision(20) << "lo " << ddlo(z2b) << '\n';
//     std::cout << z2b << std::endl;
//   }
//   {
//     using w_t   = eve::wide<T>;
//     using wdd_t  = eve::wide<dd_t>;
//     wdd_t z1(1, eve::eps(eve::as<T>()));
//     wdd_t z1b(z1);
//     wdd_t z2(eve::eps(eve::as<T>()), eve::sqr(eve::eps(eve::as<T>())));
//     wdd_t z3(eve::eps(eve::as<T>()), 0);
//     std::cout << std::setprecision(20) << "z1 " << z1 << std::endl;
//     std::cout << std::setprecision(20) << "z3 " << z3 << std::endl;
//     z1*= z3;
//     std::cout << std::setprecision(20) << "z1 " << z1 << std::endl;
//     std::cout << std::setprecision(20) << "z2 " << z2 << std::endl;
//     TTS_ULP_EQUAL(ddhi(z1), ddhi(z2), 0.5);
//     TTS_ULP_EQUAL(ddlo(z1), eve::zero(eve::as<w_t>()), 0.0);
//     w_t z4(eve::eps(eve::as<w_t>()));
//     z1b *= z4;
//     TTS_ULP_EQUAL(ddhi(z1b), ddhi(z2), 0.5);
//     TTS_ULP_EQUAL(ddlo(z1b), eve::zero(eve::as<w_t>()), 0.0);

//     wdd_t z2b(T(1));
//     int N = (sizeof(T) == 4) ? 40 : 60;
//     std::int64_t a = (1ll << N) + 12ll;

//     std::cout << "a " << a << std::endl;
//     z2b *= a;
//     TTS_ULP_EQUAL(ddhi(z2b), w_t((1ll << N)), 0.5) << std::setprecision(20) << "hi " << ddhi(z2b) << '\n';
//     TTS_ULP_EQUAL(ddlo(z2b), w_t(12), 0.0) << std::setprecision(20) << "lo " << ddlo(z2b) << '\n';
//     std::cout << z2b << std::endl;
//   }
// };

TTS_CASE_TPL( "Check dd::operator/", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using dd_t   = eve::dd<T>;
  using eve::ddhi;
  using eve::ddlo;
  {
    auto ep =  eve::eps(eve::as<T>());
    dd_t z1(1, ep/2);
//    dd_t z1b(z1);
    dd_t z2(1, ep/2);
    dd_t z3(1, 0); //ep+2*ep*(eve::sqr(ep)+ep));
    std::cout << std::setprecision(20) << "z1 " << z1 << std::endl;
    std::cout << std::setprecision(20) << "z3 " << z3 << std::endl;
    z1/= z3;
    std::cout << std::setprecision(20) << "z1 " << z1 << std::endl;
    std::cout << std::setprecision(20) << "z2 " << z2 << std::endl;
    TTS_ULP_EQUAL(ddhi(z1), ddhi(z2), 0.5);
    TTS_ULP_EQUAL(ddlo(z1), eve::zero(eve::as<T>()), 0.0);
//     T z4(eve::eps(eve::as<T>()));
//     z1b /= z4;
//     TTS_ULP_EQUAL(ddhi(z1b), ddhi(z2), 0.5);
//     TTS_ULP_EQUAL(ddlo(z1b), eve::zero(eve::as<T>()), 0.0);

//     dd_t z2b(T(1));
     std::cout << " ==================================== "  << std::endl;
     int N = (sizeof(T) == 4) ? 40 : 60;
     std::uint64_t a = (1ll << N) + 12ll;
     std::cout << "a " << a << std::endl;
     dd_t z(a);
     std::cout << "z " << z << std::endl;
     dd_t zz(short(3));
     std::cout << "zz" << zz << std::endl;
     std::cout << " ==================================== "  << std::endl;


//     std::cout << "a " << a << std::endl;
//     z2b /= a;
//     TTS_ULP_EQUAL(ddhi(z2b), T((1ull << N)), 0.5) << std::setprecision(20) << "hi " << ddhi(z2b) << '\n';
//     TTS_ULP_EQUAL(ddlo(z2b), T(12), 0.0) << std::setprecision(20) << "lo " << ddlo(z2b) << '\n';
//     std::cout << z2b << std::endl;
  }
//   {
//     using w_t   = eve::wide<T>;
//     using wdd_t  = eve::wide<dd_t>;
//     auto ep =  eve::eps(eve::as<T>());
//     wdd_t z1(1, ep);
// //    wdd_t z1b(z1);
//     wdd_t z2(1, -ep);
//     wdd_t z3(1, ep+2*ep*(eve::sqr(ep)+ep));
//     std::cout << std::setprecision(20) << "z1 " << z1 << std::endl;
//     std::cout << std::setprecision(20) << "z3 " << z3 << std::endl;
//     z1/= z3;
//     std::cout << std::setprecision(20) << "z1 " << z1 << std::endl;
//     std::cout << std::setprecision(20) << "z2 " << z2 << std::endl;
//     TTS_ULP_EQUAL(ddhi(z1), ddhi(z2), 0.5);
//     TTS_ULP_EQUAL(ddlo(z1), eve::zero(eve::as<w_t>()), 0.0);
// //     w_t z4(eve::eps(eve::as<w_t>()));
// //     z1b /= z4;
// //     TTS_ULP_EQUAL(ddhi(z1b), ddhi(z2), 0.5);
// //     TTS_ULP_EQUAL(ddlo(z1b), eve::zero(eve::as<w_t>()), 0.0);

// //     wdd_t z2b(T(1));
// //     int N = (sizeof(T) == 4) ? 40 : 60;
// //     std::int64_t a = (1ll << N) + 12ll;

// //     std::cout << "a " << a << std::endl;
// //     z2b /= a;
// //     TTS_ULP_EQUAL(ddhi(z2b), w_t((1ll << N)), 0.5) << std::setprecision(20) << "hi " << ddhi(z2b) << '\n';
// //     TTS_ULP_EQUAL(ddlo(z2b), w_t(12), 0.0) << std::setprecision(20) << "lo " << ddlo(z2b) << '\n';
// //     std::cout << z2b << std::endl;
//   }
};
