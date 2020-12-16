//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/am.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/wide.hpp>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// double Jacobi_am(double u, char arg, double x)                             //
//                                                                            //
//  Description:                                                              //
//     Let F(phi,k) = F(phi \ alpha) = F(phi | m) be Legendre's elliptic      //
//     function of the first kind with modulus k, modular angle alpha where   //
//     k = sin(alpha) or parameter m where m = k^2, i.e.                      //
//        F(phi,k) = Integral(0,phi) dtheta / sqrt(1 - k^2 sin^2(theta))      //
//        F(phi \ alpha) = Integral(0,phi) dtheta /                           //
//                                        sqrt(1 - sin^2(alpha) sin^2(theta)) //
//        F(phi | m) = Integral(0,phi) dtheta / sqrt(1 - m sin^2(theta))      //
//                                                                            //
//     This Jacobi elliptic amplitude function, am, is defined as             //
//               am(u,k) = am(u \ alpha) = am(u | m)  = phi                   //
//     where u = F(phi,k) = F(phi \ alpha) = F(phi | m).                      //
//                                                                            //
//     The common mean method, sometimes called the Gauss transform method,   //
//     is a variant of the descending Landen transformation in which two      //
//     sequences are formed: Setting a[0] = 1 and g[0] = 1-m, a[i] is the     //
//     arithmetic average and g[i] is the geometric mean of a[i-1] and g[i-1],//
//     i.e. a[i+1] = (a[i] + g[i])/2 and g[i+1] = sqrt(a[i]*g[i]).  The       //
//     sequences, a[i] and g[i], satisfy the inequalities                     //
//     g[0] < g[1] < ... < a[1] < a[0].  Further, lim g[n] = lim a[n].        //
//                                                                            //
//     Set phi[n] = 2^n a[n] u, the recursively compute phi[n-1] by           //
//        phi[n-1] = [ phi[n] + arcsin( c[n] sin(phi[n]) / a[n] ] / 2         //
//     for until n = 1.  Then am(u,k) = am(u \ alpha) = am(u | m) = phi[0].   //
//                                                                            //
//  Arguments:                                                                //
//     double  u                                                              //
//                The first argument of am(u,x) corresponding to the value of //
//                the elliptic integral of the first kind u = F(am(u,x),x).   //
//     char    arg                                                            //
//                The type of argument of the second argument of am():        //
//                  If arg = 'k', then x = k, the modulus of F(phi,k).        //
//                  If arg = 'a', then x = alpha, the modular angle of        //
//                                F(phi \ alpha), alpha in radians.           //
//                  If arg = 'm', then x = m, the parameter of F(phi | m).    //
//                  The value of arg defaults to 'k'.                         //
//     double  x                                                              //
//                The second argument of the amplitude function am(u,x)       //
//                corresponding to the second argument of the elliptic        //
//                integral of the first kind F(phi,x).  'x' may the the       //
//                modulus, modular angle, or parameter depending on the value //
//                of 'arg'.  If 'arg' = 'm', then x must be between 0 and 1   //
//                inclusively and if 'arg' = 'k', then x must be between -1   //
//                and 1 inclusively.                                          //
//                                                                            //
//  Return Value:                                                             //
//     The amplitude am(u,m) in radians.                                      //
//                                                                            //
//  Example:                                                                  //
//     double u, x;                                                           //
//     double am;                                                             //
//     char   arg;                                                            //
//                                                                            //
//     ( code to initialize u, arg, and x )                                   //
//                                                                            //
//     phi = Jacobi_am( u, arg, x );                                          //
////////////////////////////////////////////////////////////////////////////////

#include <math.h>           // required for sqrtl(), fabsl(), fabs(), asinl(),
                            // atan(), sinl(), and M_PI_2
#include <float.h>          // required for LDBL_EPSILON


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

                        // Check special case x = 0 //
                        // i.e. k = m = alpha = 0.  //

   if ( x == 0.0 ) return u;

   switch (arg) {
   case 'a': k = sinl( fabsl(x) ); break;
   case 'm': k = sqrtl( fabsl(x) ); break;
   default:  k = fabsl(x);
   }
                   // Check special case k = 1 //

   if ( k == 1.0 ) return 2.0 * atan( exp(u) ) - eve::pio_2(eve::as<double>());

         // If k > 1, then perform a Jacobi modulus transformation. //
         // Initialize the sequence of arithmetic and geometric     //
         // means, a = 1, g = k'.                                   //

   a[0] = 1.0l;
   g[0] = sqrtl(1.0L- k * k);
   c[0] = k;

   // Perform the sequence of Gaussian transformations of arithmetic and //
   // geometric means of successive arithmetic and geometric means until //
   // the two means converge to a common mean (upto machine accuracy)    //
   // starting with a = 1 and g = k', which were set above.              //

   two_n = 1.0l;
   for (n = 0; n < N; n++) {
     if ( fabsl(a[n] - g[n]) < (a[n] * eve::eps(eve::as<double>()))) break;
      two_n += two_n;
      a[n+1] = 0.5 * (a[n] + g[n]);
      g[n+1] = sqrtl(a[n] * g[n]);
      c[n+1] = 0.5 * (a[n] - g[n]);
   }

         // Prepare for the inverse transformation of phi = x * cm. //

   phi = two_n * a[n] * u;

                      // Perform backward substitution //

   for (; n > 0; n--) phi = 0.5l * ( phi + asinl( c[n] * sinl(phi) / a[n]) );

   return (double) phi;
}




TTS_CASE_TPL("Check eve::am behavior", EVE_TYPE)
{
  using eve::am;
  using eve::tag::am_;
  using elt_t = eve::element_type_t<T>;
  using eve::as;

  auto inf   =  eve::inf(as<elt_t>());
  auto minf  =  eve::minf(as<elt_t>());
  auto nan   =  eve::nan(as<elt_t>());
  auto pio_2 =  eve::pio_2(as<elt_t>());
   auto one   =  eve::one(as<elt_t>());
  auto zero  =  eve::zero(as<elt_t>());

#ifndef boost_simd_no_invalids
  TTS_ULP_EQUAL(eve::am(inf, elt_t(0)), inf, 1.0);
  TTS_ULP_EQUAL(am(minf, elt_t(0)), minf, 1.0);
  TTS_ULP_EQUAL(am(nan, elt_t(0)), nan, 1.0);
  TTS_ULP_EQUAL(am(inf, elt_t(0.5)), nan, 1.0);
  TTS_ULP_EQUAL(am(minf, elt_t(0.5)), nan, 1.0);
  TTS_ULP_EQUAL(am(nan, elt_t(0.5)), nan, 1.0);
  TTS_ULP_EQUAL(am(inf, elt_t(1)), pio_2, 1.0);
  TTS_ULP_EQUAL(am(minf, elt_t(1)), -pio_2, 1.0);
  TTS_ULP_EQUAL(am(nan, elt_t(1)), nan, 1.0);
#endif
  // specific values tests
  TTS_ULP_EQUAL(am(one,elt_t(0)),    elt_t(jacobi_am(one,'x',elt_t(0))), 1);
  TTS_ULP_EQUAL(am(pio_2,elt_t(0)),  elt_t(jacobi_am(pio_2,'x',elt_t(0))), 1);
  TTS_ULP_EQUAL(am(zero,elt_t(0)),   elt_t(jacobi_am(zero,'x',elt_t(0))), 1);
  TTS_ULP_EQUAL(am(one,elt_t(0.5)),  elt_t(jacobi_am(one,'x',elt_t(0.5))), 1);
  TTS_ULP_EQUAL(am(pio_2,elt_t(0.5)),elt_t(jacobi_am(pio_2,'x', elt_t(0.5))), 1);
  TTS_ULP_EQUAL(am(zero,elt_t(0.5)), elt_t(jacobi_am(zero,'x', elt_t(0.5))), 1);
  TTS_ULP_EQUAL(am(one,elt_t(1)),    elt_t(jacobi_am(one,'x',elt_t(1))), 1);
  TTS_ULP_EQUAL(am(pio_2,elt_t(1)),  elt_t(jacobi_am(pio_2,'x', elt_t(1))), 1);
  TTS_ULP_EQUAL(am(zero,elt_t(1)),   elt_t(jacobi_am(zero,'x', elt_t(1))), 1);

  TTS_ULP_EQUAL(eve::ell_angle(am)(one,    elt_t(0)),   elt_t(jacobi_am(one,  'a',elt_t(0))), 1);
  TTS_ULP_EQUAL(eve::ell_angle(am)(pio_2,  elt_t(0)),   elt_t(jacobi_am(pio_2,  'a',elt_t(0))), 1);
  TTS_ULP_EQUAL(eve::ell_angle(am)(zero,   elt_t(0)),   elt_t(jacobi_am(zero,  'a',elt_t(0))), 1);
  TTS_ULP_EQUAL(eve::ell_angle(am)(one,    elt_t(0.5)), elt_t(jacobi_am(one,    'a',elt_t(0.5))), 1);
  TTS_ULP_EQUAL(eve::ell_angle(am)(pio_2,  elt_t(0.5)), elt_t(jacobi_am(pio_2,    'a', elt_t(0.5))), 1);
  TTS_ULP_EQUAL(eve::ell_angle(am)(zero,   elt_t(0.5)), elt_t(jacobi_am(zero,    'a', elt_t(0.5))), 1);
  TTS_ULP_EQUAL(eve::ell_angle(am)(one,    elt_t(1)),   elt_t(jacobi_am(one,    'a',elt_t(1))), 1);
  TTS_ULP_EQUAL(eve::ell_angle(am)(pio_2,  elt_t(1)),   elt_t(jacobi_am(pio_2,    'a', elt_t(1))), 1);
  TTS_ULP_EQUAL(eve::ell_angle(am)(zero,   elt_t(1)),   elt_t(jacobi_am(zero,    'a', elt_t(1))), 1);

  TTS_ULP_EQUAL(eve::ell_modulus(am)(one,  elt_t(0)),    elt_t(jacobi_am(one,  'm',elt_t(0)) ), 1);
  TTS_ULP_EQUAL(eve::ell_modulus(am)(pio_2,elt_t(0)),    elt_t(jacobi_am(pio_2,  'm',elt_t(0))), 1);
  TTS_ULP_EQUAL(eve::ell_modulus(am)(zero, elt_t(0)),    elt_t(jacobi_am(zero,  'm',elt_t(0))), 1);
  TTS_ULP_EQUAL(eve::ell_modulus(am)(one,  elt_t(0.5)),  elt_t(jacobi_am(one,    'm',elt_t(0.5))), 1);
  TTS_ULP_EQUAL(eve::ell_modulus(am)(pio_2,elt_t(0.5)),  elt_t(jacobi_am(pio_2,    'm', elt_t(0.5))), 1);
  TTS_ULP_EQUAL(eve::ell_modulus(am)(zero, elt_t(0.5)),  elt_t(jacobi_am(zero,    'm', elt_t(0.5))), 1);
  TTS_ULP_EQUAL(eve::ell_modulus(am)(one,  elt_t(1)),    elt_t(jacobi_am(one,    'm',elt_t(1))), 1);
  TTS_ULP_EQUAL(eve::ell_modulus(am)(pio_2,elt_t(1)),    elt_t(jacobi_am(pio_2,    'm', elt_t(1))), 1);
  TTS_ULP_EQUAL(eve::ell_modulus(am)(zero, elt_t(1)),    elt_t(jacobi_am(zero,    'm', elt_t(1))), 1);
}
