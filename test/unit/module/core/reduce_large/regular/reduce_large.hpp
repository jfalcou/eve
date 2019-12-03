//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/reduce_large.hpp>
#include <eve/function/rem_pio2.hpp>
#include <eve/function/rem_pio2_cephes.hpp>
#include <eve/function/reduce_large.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/function/dist.hpp>  
#include <eve/constant/mzero.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <utility>

// TTS_CASE("Check eve::reduce_large return type")
// {
//   TTS_EXPR_IS(eve::reduce_large(Type(0)), (std::tuple<Type, Type, Type>));
// }

TTS_CASE("Check eve::eve::reduce_large behavior")
{

  Value zz = 9007199254740992.0; //eve::Valmax<Value>();
  int i = 0; 
  while (zz > 1.0)
  {
    std::cout << i << " -> " << zz << std::endl;
    ++i; 
    auto z =  Type(zz);
    Type n0, r0, dr0, n1, r1, dr1; //, dr1; 
    std::tie(n0, r0, dr0) = eve::rem_pio2(z);
    std::tie(n1, r1, dr1) = eve::reduce_large(z);
    std::cout << r0 <<  " < -> " << r1 << std::endl; 
    TTS_ULP_EQUAL(r0+dr0, r1+dr1, 0.5);qqq
//    TTS_EQUAL(dr0, dr1); 
    TTS_EQUAL(n0, n1);
    zz /= 10;     
  }
}

// TTS_CASE("Check eve::eve::reduce_fast behavior")
// {
//   Type ulp(0.5); 
//   TTS_EQUAL(0, 0); 
//   int i = 1; 
//   Value zz = 1.0f; //0x1.7d4998p+38; //0x1.47d0fcp+33; //0x1.ffffffp+27; //eve::Valmax<Value>();
//   while (true)
//   {
//     ++i;
//     if (i%100000  == 0) std::cout << "." << std::flush; 
//     if (i%10000000 == 0) std::cout << std::endl << "i " << i << " zz " << zz << std::endl; 
//     Type n0, r0, dr0, n1, r1, dr1; 
//     std::tie(n0, r0, dr0) = eve::rem_pio2(zz);
//     std::tie(n1, r1, dr1) = eve::reduce_large(zz);
// //     TTS_ULP_EQUAL(r0, r1, 0.5);
// //     TTS_EQUAL(n0, n1);
//     auto d = eve::ulpdist(r1, r0);
//     Type nn0, nn1; 
//     if (d > ulp )
//     {
// //     ulp *= 2; 
//  //       std::cout << " autre dist " <<  eve::ulpdist(r1, -r0) << std::endl;
// //       std::cout << "r0 =  " << r0 <<  " -- r1 =  " << r1 << std::endl;
// //       std::cout << "n0 =  " << n0 <<  " -- n1 =  " << n1 << std::endl;
// //       std::cout << "r0-r1 " << r0+r1 << std::endl; 
//       if (n0 == n1)
//       {
//         nn0 = nn1 = 0;
//       }
//       else
//       {
//         nn0 = n0*eve::Pio_2<double>();
//         nn1 = n1*eve::Pio_2<double>(); 
//       }
// //       auto dc = eve::ulpdist(std::cos(double(r0)+double(dr0)+double(nn0)), std::cos(double(r1)+double(dr1)+double(nn1));
// //       auto ds = eve::ulpdist(std::sin(double(r0)+double(dr0)+double(nn0)), std::sin(double(r1)+double(dr1)+double(nn1)); 
//       auto dc = eve::ulpdist(std::cos(r0+nn0), std::cos(r1+nn1));
//       auto ds = eve::ulpdist(std::sin(r0+nn0), std::sin(r1+nn1)); 

//       if (dc > ulp || ds >  ulp)
//       {
//         std::cout << "dc =  " << dc <<  " -- ds =  " << ds << std::endl; 
//         std::cout << std::defaultfloat << "ulp = " << ulp << " z =  "  << eve::prev(zz) <<  " -> " << std::hexfloat << eve::prev(zz) << std::endl;
// //         std::cout << "i = " << i << " z =  " << std::dec << eve::prev(zz) <<  " -> " << std::hexfloat << eve::prev(zz) << std::endl;
// //         std::cout << std::defaultfloat << "ulp =  " << d << std::endl;
// //         std::cout << "r0 =  " << r0 <<  " -- r1 =  " << r1 << std::endl;
// //         std::cout << "n0 =  " << n0 <<  " -- n1 =  " << n1 << std::endl;    
//          break; 
//       }
//       if ( zz == eve::Valmax<Value>()) break; 
//     }
//     zz  = eve::next(zz) ;   
//  }
  
//}
