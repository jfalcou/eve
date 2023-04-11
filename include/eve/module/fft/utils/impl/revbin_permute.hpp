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
#include <eve/module/fft/utils/aos_soa.hpp>
#include <eve/concept/range.hpp>
#include <type_traits>
#include <eve/pattern.hpp>

namespace eve::detail
{

  namespace internal
  {
    // scalar perm
    template < range F, range I>
    auto perm(F const & f,  I const & ind) noexcept
    {
      F g(f.size());
      auto fb =  f.begin();
      auto ib =  ind.begin();
      for(auto gb =  g.begin(); gb < g.end(); ++gb, ++ib) *gb = *(fb+*ib);
      return g;
    }

    // simd perm
    template < range F, range I>
    auto simd_perm(F const & f,  I const & ind) noexcept
    {
      F g(f.size());
      auto view = eve::views::zip(ind, g);
      auto doit = [&f](auto zz, auto ignore){
        auto [ ind_it, g_it] = zz;
        auto [ ii, gg] = load[ignore](zz);
        auto r = eve::gather[ignore](f.data(), ii);
        eve::store[ignore](r, g_it);
      };
      eve::algo::for_each(view, doit);

      return g;
    }

    template < range R>
    inline void revbin_permute_leq_64(R & f)
    // Must have f.size() \in {2, 4, 8, 16, 32, 64}
    {
      auto n = f.size();
      EVE_ASSERT(n <= 64 && is_pow2(n), "size is greater than 64 or is not a power of 2");

      switch ( n ) {
      case 1:  break;
      case 2:  break;
      case 4: {
        constexpr std::array<std::uint32_t, 4> ind{0, 2, 1, 3};
        f = perm(f, ind); break;
      }
      case 8: {
        constexpr std::array<std::uint32_t, 8> ind{0, 4, 2, 6, 1, 5, 3, 7};
        perm(f, ind); break;
      }
      case 16: {
        constexpr std::array<std::uint32_t, 16> ind{0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
        f = perm(f, ind); break;
      }
      case 32: {
        constexpr std::array<std::uint32_t, 32> ind{0, 16, 8, 24, 4, 20, 12, 28, 2, 18, 10, 26, 6, 22, 14, 30 , 1, 17, 9, 25, 5, 21, 13, 29, 3, 19, 11, 27, 7, 23, 15, 31};
        f = perm(f, ind); break;
      }
      case 64: {
        constexpr std::array<std::uint32_t, 64> ind{
            0, 32, 16, 48, 8, 40, 24, 56, 4, 36,
            20, 52, 12, 44, 28, 60, 2, 34, 18, 50,
            10, 42, 26, 58, 6, 38, 22, 54, 14, 46,
            30, 62, 1, 33, 17, 49, 9, 41, 25, 57,
            5, 37, 21, 53, 13, 45, 29, 61, 3, 35, 19, 51,
            11, 43, 27, 59, 7, 39, 23, 55, 15, 47, 31, 63};
        f = perm(f, ind); break;
      }
      default:;  // not so good...
      }
    }

    template < range R>
    inline auto revbin_permute_gt_64(R & f)
    // Must have f.size() 2^n > 64
    {
      auto n = f.size();
      auto idx_swap = [&f](auto k,  auto r){
        auto pos1 = f.data()+k;
        auto pos2 = f.data()+r;
        auto z = *pos1;  *pos1 = *pos2; *pos2 = z;
      };

      auto revbin = []<typename UI>(UI x){ // Return x with reversed bit order.
        size_t s = sizeof(UI)*8 >> 1;
        size_t m = allbits(as<UI>()) >> s;
        while ( s )
        {
          x = ( (x & m) << s ) ^ ( (x & (~m)) >> s );
          s >>= 1;
          m ^= (m<<s);
        }
        return  x;
      };
      auto  rvb = [revbin](size_t x, size_t ldn){
        return  revbin(x) >> (sizeof(size_t)*8-ldn);
      };

      for (size_t x =0; x < n; ++x)
      {
        auto r = rvb(x, countr_zero(n));
        if (r>x) idx_swap(x, r);
      }
      std::cout << "gt64" << std::endl;
      return f;
    }
  }


  template<range R>
  EVE_FORCEINLINE constexpr void
  revbin_permute_(EVE_SUPPORTS(cpu_), aos_type const &, R & f) noexcept
  {
    std::cout << "revbin_permute_" << std::endl;
    auto n = f.size();
     std::cout << "size " << n << std::endl;
    if ( n<=64 )
    {
      std::cout << "le64" << std::endl;
      internal::revbin_permute_leq_64(f);
    }
    else
    {
      std::cout << "gt64" << std::endl;
      internal::revbin_permute_gt_64(f);
    }
  }

  template <range R>
  auto revbin_permute_(EVE_SUPPORTS(cpu_), soa_type const &, R & f)
  requires(eve::is_complex_v<typename R::value_type>)
  {
    using T = typename R::value_type;
    auto n = f.size();
    std::vector<T> g(n);
    for(size_t i=0; i < n ; ++i) g[i] = f.get(i);
    aos(revbin_permute)(g);
    for(size_t i=0; i < n ; ++i)  f.set(i, g[i]);
  }


//   template <typename T>
//   auto revbin_permute_(EVE_SUPPORTS(cpu_), eve::algo::soa_vector<eve::complex<T>>  & f)
//   {
//     auto n = f.size();
//     std::vector<eve::complex<T>> g(n);
//     for(size_t i=0; i < n ; ++i) g[i] = f.get(i);
//     revbin_permute(g);
//     for(size_t i=0; i < n ; ++i)  f.set(i, g[i]);
//     return f;
//   }

//   template < typename T>
//   auto revbin_permute_(EVE_SUPPORTS(cpu_), raw_type const &, eve::algo::soa_vector<eve::complex<T>>  & f)
//   {
//     auto n = f.size();
//     std::vector<eve::complex<T>> g(n);
//     for(size_t i=0; i < n ; ++i) g[i] = f.get(i);
//     revbin_permute(g);
//     for(size_t i=0; i < n ; ++i)  f.set(i, g[i]);
//     return f;
//   }

}








//     template<value T>
//     inline auto revbin_permute_gt_64(std::vector<T> & f)
//     {
//       [[maybe_unused]] auto revbin = []<typename UI>(UI x){ // Return x with reversed bit order.
//         using e_t = element_type_t<UI>;
//         auto s = bit_shr(sizeof(e_t)*8, 1);
// //        std::cout << "s "<< s << std::endl;
//         auto m = bit_shr(allbits(as<UI>()), s);
//         while ( s )
//         {
//           x = ( (x & m) << s ) ^ ( (x & (~m)) >> s );
//           s >>= 1;
//           m ^= (m<<s);
//         }
//         return  x;
//       };

//       [[maybe_unused]] auto  rvb = [revbin](auto x, auto ldn){
//         // Return word with the ldn least significant bits
//         //   (i.e. bit_0 ... bit_{ldn-1})  of x reversed,
//         //   the other bits are set to zero.
//         using e_t =  element_type_t<decltype(x)>;
// //        std::cout << "(sizeof(x)*8-ldn) "<< (sizeof(e_t)*8-ldn) << std::endl;
//         return  revbin(x) >> (sizeof(e_t)*8-ldn);
//       };

//       auto view = eve::views::iota(std::uint32_t{0}, f.size());
// //      std::cout <<  tts::typename_<decltype(view)> << std::endl;
//       auto doit = [&f, rvb](auto x, auto){
//         auto xx = load(x);
// //        std::cout << "xx " << xx << std::endl;
//         auto rr = rvb(xx, countr_zero(f.size()));
// //        std::cout << countr_zero(f.size()) << " ->rr = "<< rr  << std::endl;
//         auto swap_idx =  [&f](auto r,  auto x){
//           for(size_t i=0; i < cardinal_v<decltype(x)>; ++i)
//           {
//             auto ri = r.get(i);
//             auto xi = x.get(i);
//             if(ri >  xi){
//               auto z = f[ri];  f[ri] = f[xi]; f[xi] = z;
//             }
//           }
//         };

// //         auto swap_idx =  [&f](auto r,  auto x){
// //           auto fr =  gather(f.data(), r);
// //           auto fx =  gather(f.data(), x);
// //           scatter[r >  x](f.data(), r, fx);
// //           scatter[r >  x](f.data(), x, fr);
// //         };
//         swap_idx(rr, xx);
//        };
//       eve::algo::for_each(view, doit);
//       return f;
//     }
//   }

//   template<scalar_value T>
//   auto revbin_permute_(EVE_SUPPORTS(cpu_)/*, raw_type const &*/
//                       , std::vector<T> & f) noexcept
//   {
//     auto n = f.size();
//      [[maybe_unused]] auto idx_swap = [&f](auto k,  auto r){
//       auto z = f[k];  f[k] = f[r]; f[r] = z;
//     };
//      [[maybe_unused]] auto revbin = []<typename UI>(UI x){ // Return x with reversed bit order.
//       size_t s = sizeof(UI)*8 >> 1;
//       size_t m = allbits(as<UI>()) >> s;
//       while ( s )
//       {
//         x = ( (x & m) << s ) ^ ( (x & (~m)) >> s );
//         s >>= 1;
//         m ^= (m<<s);
//       }
//       return  x;
//     };

//      [[maybe_unused]] auto  rvb = [revbin](size_t x, size_t ldn){
//       // Return word with the ldn least significant bits
//       //   (i.e. bit_0 ... bit_{ldn-1})  of x reversed,
//       //   the other bits are set to zero.
// //     std::cout << "(sizeof(x)*8-ldn) "<< (sizeof(x)*8-ldn) << std::endl;
//       return  revbin(x) >> (sizeof(size_t)*8-ldn);
//     };

//     if ( n<=8 )
//     {
//       std::cout << "le64" << std::endl;
//       return internal::revbin_permute_leq_64(f);
//     }
//     else
//     {
//       //    return internal::revbin_permute_gt_64(f);
//       for (size_t x =0; x < n; ++x)
//       {
//         auto r = rvb(x, countr_zero(n));

//         if (r>x) idx_swap(x, r);
//       }
//       std::cout << "gt64" << std::endl;
//       return f;
//     }
//   }

//   template<scalar_value T>
//   auto revbin_permute_(EVE_SUPPORTS(cpu_)
//                       , std::vector<T> & f) noexcept
//   {

//     auto n = f.size();
//     auto  idx_swap = [&f](auto k,  auto r){
//       auto z = f[k];  f[k] = f[r]; f[r] = z;
//     };
//     auto revbin = [](size_t x){ // Return x with reversed bit order.
//                                 // version using dynamically generated masks:
//       size_t s = sizeof(size_t)*8 >> 1;
//       size_t m = allbits(as<size_t>()) >> s;
//       while ( s )
//       {
//         x = ( (x & m) << s ) ^ ( (x & (~m)) >> s );
//         s >>= 1;
//         m ^= (m<<s);
//       }
//       return  x;
//     };

//     auto  rvb = [revbin](size_t x, size_t ldn){
//       // Return word with the ldn least significant bits
//       //   (i.e. bit_0 ... bit_{ldn-1})  of x reversed,
//       //   the other bits are set to zero.
//       return  revbin(x) >> (sizeof(size_t)*8-ldn);
//     };

//     if ( n<=64 )
//     {
//       return internal::revbin_permute_leq_64(f);
//     }
//     constexpr size_t  RBP_SYMM = 4; // amount of symmetry used

//     const size_t nh = (n>>1);
//     const size_t n1  = n - 1;     // = 11111111
//     const size_t nx1 = nh - 2;    // = 01111110
//     const size_t nx2 = n1 - nx1;  // = 10111101

//     size_t k = 0,  r = 0;
//     while ( k < (n/RBP_SYMM)  )  // n>=16, n/2>=8, n/4>=4
//     {
//       // ----- k%4 == 0:
//       if ( r>k )
//       {
//         idx_swap(k, r);          // <nh, <nh 11
//         idx_swap(n1^k, n1^r);    // >nh, >nh 00
//         idx_swap(nx1^k, nx1^r);  // <nh, <nh 11
//         idx_swap(nx2^k, nx2^r);  // >nh, >nh 00
//       }

//       ++k;
//       r ^= nh;

//       // ----- k%4 == 1:
//       if ( r>k )
//       {
//         idx_swap(k, r);  // <nh, >nh 10
//         idx_swap(n1^k, n1^r);  // >nh, <nh 01
//       }

//       ++k;
//       const size_t ldn = countr_zero(n);
//       r = rvb(k, ldn);

//       // ----- k%4 == 2:
//       if ( r>k )
//       {
//         idx_swap(k, r);  // <nh, <nh 11
//         idx_swap(n1^k, n1^r);  // >nh, >nh 00
//       }

//       ++k;


//       // ----- k%4 == 3:
//       if ( r>k )
//       {
//         idx_swap(k, r);    // <nh, >nh 10
//         idx_swap(nx1^k, nx1^r);   // <nh, >nh 10
//       }

//       ++k;


//       r = rvb(k, countr_zero(n));

//     }
//     return f;
//   }
