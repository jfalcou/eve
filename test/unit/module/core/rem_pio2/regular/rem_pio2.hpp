//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rem_pio2.hpp>
#include <eve/function/rem_pio2_cephes.hpp>
#include <eve/function/rem_pio2_medium.hpp>
#include <eve/function/reduce_medium.hpp>
#include <eve/function/reduce_large.hpp>
#include <eve/function/next.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/function/dist.hpp>  
#include <eve/constant/mzero.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <utility>

TTS_CASE("Check eve::rem_pio2 return type")
{
  TTS_EXPR_IS(eve::rem_pio2(Type(0)), (std::tuple<Type, Type, Type>));
}

// TTS_CASE("Check eve::eve::rem_pio2 behavior")
// {

//   Value zz = 4.01706e+08; //eve::Valmax<Value>();
//   int i = 0; 
//   while (zz > 10)
//   {
//     std::cout << i << " -> " << zz << std::endl;
//     ++i; 
//     auto z =  Type(zz);
//     Type n0, r0, dr0, n1, r1; //, dr1; 
// //    std::tie(n1, r1, dr1) = eve::reduce_large(z);
//     std::tie(n0, r0, dr0) = eve::rem_pio2(z);
//     std::tie(n1, r1     ) = eve::rem_pio2_cephes(double(z));
    
// //    std::tie(n1, r1     ) = eve::rem_pio2_medium(z); 
//     TTS_ULP_EQUAL(r0, r1, 0.5);
//     TTS_EQUAL(n0, n1);
//     zz /= 1.1;     
//   }
// }

TTS_CASE("exhaustive check")
{
//  int i =  0; 
  float zz =  0.0f;  //587817151.0f; //eve::Valmax<Value>();
  while (true)
  {
    Value n0, n1, r0, r1, dr0, dr1;
//    double dbln1,  dblr1; 
    std::tie(n0, r0, dr0) = eve::rem_pio2(zz);
    std::tie(n1, r1, dr1) = eve::reduce_medium(zz);
//    std::tie(dbln1, dblr1     ) = eve::rem_pio2_cephes(double(zz));
//    std::tie(dbln1, dblr1     ) = eve::rem_pio2_medium(double(zz));
//     r1 = dblr1;
//     dr1 = dblr1-r1; 
//    auto dd = eve::dist(dr1, dr0); 
    auto d  = eve::ulpdist(r1, r0);
    float nn1, nn0; 
    if (n1 != n0)
    {
       nn1 = n1*eve::Pio_2<double>();
       nn0 = n0*eve::Pio_2<double>();
    }
    else
    {
      nn1 =  nn0 = 0;
    }
    
    auto dc = eve::ulpdist(std::cos(r0+nn0), std::cos(r1+nn1));
    auto ds = eve::ulpdist(std::sin(r0+nn0), std::sin(r1+nn1));
    if(dc > 0.5 || ds >  0.5)
    {
      std::cout << "r0 =  " << r0 << ",  r1 =  " << r1 << std::endl;
      std::cout << "n0 =  " << n0 << ",  n1 =  " << n1 << std::endl;    
      std::cout << std::cos(r0+nn0)  << " <--> " << std::cos(r1+nn1) << std::endl;
      std::cout << std::sin(r0+nn0)  << " <--> " << std::sin(r1+nn1) << std::endl;   
      std::cout << "cos or sin failed for z = " << zz << " with " << eve::max(ds, dc) << " ulps" << std::endl;
      std::cout << "d =  " << d << std::endl;
      break; 
    }
      
//     if (abs(r1) > 0.78539818525315f || d > 0.5)
//     {
//       auto d1 = eve::ulpdist(eve::abs(r0-r1), 1.57079637050629f);
//       auto d2 = eve::ulpdist(eve::abs(r0), eve::abs(r1));
//       auto test = abs(r1) >  eve::Pio_4<float>(); 
//       if (d1 > 1 || test)
//       {
//         ++i;
//         std::cout << "test =  " << test << std::endl; 
//         std::cout << std::setprecision(15) << "r0          " << r0 << std::endl;
//         std::cout << std::setprecision(15) << "r1          " << r1 << std::endl;
//         std::cout << std::setprecision(15) << "n0          " << n0 << std::endl;
//         std::cout << std::setprecision(15) << "n1          " << n1 << std::endl;
//         std::cout << "d1          " << d1 << std::endl;
//         std::cout << "d2          " << d2 << std::endl;  
//         std::cout << "max z =     " << zz << std::endl;
//         std::cout << "with err =  " << d << std::endl;
//         std::cout << "dd          " << dd<< std::endl;
//         std::cout <<  eve::dist(r1, r0)<< std::endl;; 
//         std::cout << eve::dist(float(double(r1)+double(dr1)), float(double(r0)+double(dr0))) << std::endl;
//         auto dc = eve::ulpdist(std::cos(r0), std::cos(r1));
//         auto ds = eve::ulpdist(std::sin(r0), std::sin(r1));
//         if(dc > 0.5 || ds >  0.5)
//         {
//           std::cout << "cos or sin failed for z = " << zz << " with " << eve::max(ds, dc) << " ulps" << std::endl;
//         }
        
//       }
//    }            
//     if (abs(r1) > 0.78539818525315f) break; 
    if ( zz == eve::Valmax<Value>()) break; 
    zz = eve::next(zz); 
  }
}
