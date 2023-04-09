//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <vector>
#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/concept/range.hpp>
#include <type_traits>

namespace eve::detail
{
  namespace internal
  {
    uint32_t rw(uint32_t k)
    {
      static const unsigned char b[256] = {
        0, 128, 64, 192, 32, 160, 96, 224, 16, 144, 80, 208, 48, 176, 112, 240,
        8, 136, 72, 200, 40, 168, 104, 232, 24, 152, 88, 216, 56, 184, 120, 248,
        4, 132, 68, 196, 36, 164, 100, 228, 20, 148, 84, 212, 52, 180, 116, 244,
        12, 140, 76, 204, 44, 172, 108, 236, 28, 156, 92, 220, 60, 188, 124, 252,
        2, 130, 66, 194, 34, 162, 98, 226, 18, 146, 82, 210, 50, 178, 114, 242,
        10, 138, 74, 202, 42, 170, 106, 234, 26, 154, 90, 218, 58, 186, 122, 250,
        6, 134, 70, 198, 38, 166, 102, 230, 22, 150, 86, 214, 54, 182, 118, 246,
        14, 142, 78, 206, 46, 174, 110, 238, 30, 158, 94, 222, 62, 190, 126, 254,
        1, 129, 65, 193, 33, 161, 97, 225, 17, 145, 81, 209, 49, 177, 113, 241,
        9, 137, 73, 201, 41, 169, 105, 233, 25, 153, 89, 217, 57, 185, 121, 249,
        5, 133, 69, 197, 37, 165, 101, 229, 21, 149, 85, 213, 53, 181, 117, 245,
        13, 141, 77, 205, 45, 173, 109, 237, 29, 157, 93, 221, 61, 189, 125, 253,
        3, 131, 67, 195, 35, 163, 99, 227, 19, 147, 83, 211, 51, 179, 115, 243,
        11, 139, 75, 203, 43, 171, 107, 235, 27, 155, 91, 219, 59, 187, 123, 251,
        7, 135, 71, 199, 39, 167, 103, 231, 23, 151, 87, 215, 55, 183, 119, 247,
        15, 143, 79, 207, 47, 175, 111, 239, 31, 159, 95, 223, 63, 191, 127, 255
      };

      uint8_t
        b0 = b[k >> 0*8 & 0xff],
        b1 = b[k >> 1*8 & 0xff],
        b2 = b[k >> 2*8 & 0xff],
        b3 = b[k >> 3*8 & 0xff];
      return b0 << 3*8 | b1 << 2*8 | b2 << 1*8 | b3 << 0*8;
    }

    template < typename T>
    auto r(auto k)
    {
      return /*1./4294967296. * rw(k); */ldexp(T(rw(k)), -int(sizeof(k)));;
    }
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto
  fft_000_(EVE_SUPPORTS(cpu_), std::vector<T> & a) noexcept
  {

    auto pr = [](auto name,  auto n){
      std::cout << name << "= (";
      for(size_t i=0; i < n.size()-1; ++i) std::cout << n[i] << ",  ";
      std::cout << n[n.size()-1] << ")\n";
   };
    auto sa = a.size();
    std::vector<T> vin(sa);
    std::vector<T> vout(sa);
    using e_t = underlying_type_t<T>;

    auto r = [](auto k){ return ldexp(e_t(internal::rw(k)), -32); };

    auto ep = [](auto x){return exp_ipi((x+x)); };


    auto butterflies = [ep, r](auto const m, auto& vout, auto const& vin, auto const k0, auto const  c0)
    {
      // Coefficient for k1 is coefficient for k0 divided by 1<<m.
      const int c1 = c0 >> m;
      auto bd = 1 << m;
//       std::cout << "c0 =  " << c0 << std::endl;
//       std::cout << "c1 =  " << c1 << std::endl;
//       std::cout << "bd =  " << bd << std::endl;
      for (int k2 = 0; k2 < c1 ; ++k2)
      {
        for (int k1 = 0; k1 < bd; ++k1)
        {
          auto sum = zero(as<element_type_t<T>>());
          for (int j1 = 0; j1 < bd; ++j1)
          {
//            std::cout << eve::ldexp(r(k1), 4) << std::endl;
            sum += ep(j1*r(k1)) * ep(j1*r(bd*k0)) * vin[c0*k0 + c1*j1 + k2];
           }
//          std::cout << "sum " << sum << std::endl;
          vout[c0*k0 + c1*k1 + k2] = sum;
        }
      }
    };
    int N = bit_width(a.size())-1;
    std::cout << "N " << N << std::endl;
    auto n = N&1 ? 3 : 2;
    auto P = (N-n)/2+1;
    std::vector<int> mm(P, 2);
    mm[0] = n;
    std::vector<int> nn(P);
    nn[0] = 0;
    for(int i=1; i < P; ++i) nn[i] = nn[i-1]+mm[i-1];
    pr("nn", nn);
    std::cout << "sa " << a.size()<< std::endl;
    pr("a", a);
    std::cout << "P  " << P << std::endl;
    if(N&1)
      butterflies(3, vout, a, 0, 1<<N);
    else
      butterflies(2, vout, a, 0, 1<<N);
    std::cout << "icitte" << std::endl;
    pr("vout", vout);
    vin = vout;
    int p = 1;
    for (; p < P ; ++p)
    {
//      n+= 2;
      std::cout << "latte = n" << n << std::endl;
      std::cout << "latte = p" << p << std::endl;
      std::cout << " (1<<n) = " <<  (1<<n) << std::endl;
      //     std::cout << "n     = " << n << std::endl;
      std::cout << "nn[p] = " << nn[p]<< std::endl;
      for (int k0 = 0; k0 < (1<<nn[p]); ++k0)
      {
        butterflies(2, vout, vin, k0, 1<<(N-nn[p]));
        pr("vout", vout);
        vin = vout;
      }
    }
//     if (p < P-1)
//       for (int k0 = 0; k0 < 1<<(N-4); ++k0)
//       {
//         butterflies(2, vout, vin, k0, 16);
//         vin = vout;
//       }

//     for (int k0 = 0; k0 < 1<<(N-2); ++k0){
//       butterflies(2, vout, vin, k0, 4);
//     }
    pr("vout", vout);
    return vout;
  }
}
