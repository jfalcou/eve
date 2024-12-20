//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/elliptic.hpp>
#include <eve/module/math.hpp>

//==================================================================================================
// Jacobi AM reference function
//==================================================================================================
#include <math.h>
#include <float.h>

double jacobi_am(double u, char arg,  double x)
{
  static const int N = 30;            // More than sufficient for extended precision
                                     // Near m = 1, usually an N of 10 would do.
  long double a[N+1];
  long double g[N+1];
  long double c[N+1];
  long double two_n;
  long double phi;
  long double k;
  int n;

  // Check special case x = 0, i.e. k = m = alpha = 0.

  if ( x == 0.0 ) return u;

  switch (arg)
  {
    case 'a': k = sinl( fabsl(x) ); break;
    case 'm': k = sqrtl( fabsl(x) ); break;
    default:  k = fabsl(x);
  }

  // Check special case k = 1
  if ( k == 1.0 ) return 2.0 * atan( exp(u) ) - eve::pio_2(eve::as<double>());

  /*
    If k > 1, then perform a Jacobi modulus transformation.
    Initialize the sequence of arithmetic and geometric means, a = 1, g = k'.
  */
  a[0] = 1.0l;
  g[0] = sqrtl(1.0L- k * k);
  c[0] = k;

  /*
    Perform the sequence of Gaussian transformations of arithmetic and
    geometric means of successive arithmetic and geometric means until
    the two means converge to a common mean (upto machine accuracy)
    starting with a = 1 and g = k', which were set above.
  */
   two_n = 1.0l;
   for (n = 0; n < N; n++)
   {
     if ( fabsl(a[n] - g[n]) < (a[n] * eve::eps(eve::as<double>()))) break;
      two_n += two_n;
      a[n+1] = 0.5 * (a[n] + g[n]);
      g[n+1] = sqrtl(a[n] * g[n]);
      c[n+1] = 0.5 * (a[n] - g[n]);
   }

  // Prepare for the inverse transformation of phi = x * cm. //
  phi = two_n * a[n] * u;

  // Perform backward substitution
  for (; n > 0; n--)
    phi = 0.5l * ( phi + asinl( c[n] * sinl(phi) / a[n]) );

  return static_cast<double>(phi);
}

TTS_CASE_TPL( "Check eve::ams"
            , eve::test::simd::ieee_reals
            )
  <typename T>(tts::type<T>)
{
  using eve::am;
  using eve::as;
  using eve::modular;
  using eve::eccentric;

  auto const half  =  T(0.5);
  auto const inf   =  eve::inf  (as<T>());
  auto const minf  =  eve::minf (as<T>());
  auto const nan   =  eve::nan  (as<T>());
  auto const pio_2 =  eve::pio_2(as<T>());
  auto const pio_3 =  eve::pio_3(as<T>());
  auto const one   =  eve::one  (as<T>());
  auto const zero  =  eve::zero (as<T>());

  using u_t =  eve::underlying_type_t<T>;
  auto const shalf  =  u_t(0.5);
  auto const spio_2 =  eve::pio_2(as<u_t>());
  auto const spio_3 =  eve::pio_3(as<u_t>());
  auto const sone   =  eve::one  (as<u_t>());
  auto const szero  =  eve::zero (as<u_t>());

  if constexpr( eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(am(inf  , zero) , inf   );
    TTS_IEEE_EQUAL(am(minf , zero) , minf  );
    TTS_IEEE_EQUAL(am(nan  , zero) , nan   );
    TTS_IEEE_EQUAL(am(inf  , half) , nan   );
    TTS_IEEE_EQUAL(am(minf , half) , nan   );
    TTS_IEEE_EQUAL(am(nan  , half) , nan   );
    TTS_IEEE_EQUAL(am(inf  , one)  , pio_2 );
    TTS_IEEE_EQUAL(am(minf , one)  , -pio_2);
    TTS_IEEE_EQUAL(am(nan  , one)  , nan   );
  }

  // specific values tests
  TTS_ULP_EQUAL(am(one  ,zero), T(jacobi_am(sone   , 'x', szero) ), 1);
  TTS_ULP_EQUAL(am(pio_2,zero), T(jacobi_am(spio_2 , 'x', szero) ), 1);
  TTS_ULP_EQUAL(am(pio_3,zero), T(jacobi_am(spio_3 , 'x', szero) ), 1);
  TTS_ULP_EQUAL(am(zero ,zero), T(jacobi_am(szero  , 'x', szero) ), 1);
  TTS_ULP_EQUAL(am(one  ,half), T(jacobi_am(sone   , 'x', shalf) ), 1);
  TTS_ULP_EQUAL(am(pio_2,half), T(jacobi_am(spio_2 , 'x', shalf) ), 1);
  TTS_ULP_EQUAL(am(pio_3,half), T(jacobi_am(spio_3 , 'x', shalf) ), 1);
  TTS_ULP_EQUAL(am(zero ,half), T(jacobi_am(szero  , 'x', shalf) ), 1);
  TTS_ULP_EQUAL(am(one  ,one) , T(jacobi_am(sone   , 'x', sone)  ), 1);
  TTS_ULP_EQUAL(am(pio_2,one) , T(jacobi_am(spio_2 , 'x', sone)  ), 1);
  TTS_ULP_EQUAL(am(pio_3,one) , T(jacobi_am(spio_3 , 'x', sone)  ), 1);
  TTS_ULP_EQUAL(am(zero ,one) , T(jacobi_am(szero  , 'x', sone)  ), 1);

  TTS_ULP_EQUAL(am[modular](one,    zero), T(jacobi_am(sone   , 'a', szero)), 1);
  TTS_ULP_EQUAL(am[modular](pio_2,  zero), T(jacobi_am(spio_2 , 'a', szero)), 1);
  TTS_ULP_EQUAL(am[modular](zero,   zero), T(jacobi_am(szero  , 'a', szero)), 1);
  TTS_ULP_EQUAL(am[modular](one,    half), T(jacobi_am(sone   , 'a', shalf)), 1);
  TTS_ULP_EQUAL(am[modular](pio_2,  half), T(jacobi_am(spio_2 , 'a', shalf)), 1);
  TTS_ULP_EQUAL(am[modular](zero,   half), T(jacobi_am(szero  , 'a', shalf)), 1);
  TTS_ULP_EQUAL(am[modular](one,    one ), T(jacobi_am(sone   , 'a', sone )), 1);
  TTS_ULP_EQUAL(am[modular](pio_2,  one ), T(jacobi_am(spio_2 , 'a', sone )), 1);
  TTS_ULP_EQUAL(am[modular](zero,   one ), T(jacobi_am(szero  , 'a', sone )), 1);

  TTS_ULP_EQUAL(am[eccentric](one,    zero), T(jacobi_am(sone   , 'm', szero)), 1);
  TTS_ULP_EQUAL(am[eccentric](pio_2,  zero), T(jacobi_am(spio_2 , 'm', szero)), 1);
  TTS_ULP_EQUAL(am[eccentric](zero,   zero), T(jacobi_am(szero  , 'm', szero)), 1);
  TTS_ULP_EQUAL(am[eccentric](one,    half), T(jacobi_am(sone   , 'm', shalf)), 1);
  TTS_ULP_EQUAL(am[eccentric](pio_2,  half), T(jacobi_am(spio_2 , 'm', shalf)), 1);
  TTS_ULP_EQUAL(am[eccentric](zero,   half), T(jacobi_am(szero  , 'm', shalf)), 1);
  TTS_ULP_EQUAL(am[eccentric](one,    one ), T(jacobi_am(sone   , 'm', sone )), 1);
  TTS_ULP_EQUAL(am[eccentric](pio_2,  one ), T(jacobi_am(spio_2 , 'm', sone )), 1);
  TTS_ULP_EQUAL(am[eccentric](zero,   one ), T(jacobi_am(szero  , 'm', sone )), 1);
};
