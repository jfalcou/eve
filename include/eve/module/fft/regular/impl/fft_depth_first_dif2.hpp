//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <vector>
#include <eve/module/complex.hpp>
#include <eve/module/algo.hpp>
#include <eve/concept/range.hpp>
#include <vector>

namespace eve::detail
{

// Tuning parameters:
// #define  RBP_SYMM  4  // amount of symmetry used: 1, 2, 4 (default is 4)
// #define  FAST_REVBIN  // define if using revbin(x, ldn) is faster than updating

  namespace internal
  {
    inline void swap2(auto & a,  auto & b){ auto z = a;  a = b;  b = z; };
//     inline void idx_swap(auto f, auto k,  auto r){
//       auto z = f[k];  f[k] = f[r]; f[r] = z;
//     };

//template <typename Type>
//inline void revbin_permute_2(Type *f)
//// unrolled version for length 2
//{
//}  // # of swaps = 0
//// -------------------------

    template <typename T>
    inline void revbin_permute_4(std::vector<complex<T>> &f)
    // unrolled version for length 4
    {
      swap2(f[1], f[2]);
    }  // # of swaps = 1
// -------------------------

    template <typename T>
    inline void revbin_permute_8(std::vector<complex<T>> &f)
    // unrolled version for length 8
    {
      swap2(f[1], f[4]);
      swap2(f[3], f[6]);
    }  // # of swaps = 2
// -------------------------

    template <typename T>
    inline void revbin_permute_16(std::vector<complex<T>> &f)
    // unrolled version for length 16
    {
      swap2(f[1], f[8]);
      swap2(f[2], f[4]);
      swap2(f[3], f[12]);
      swap2(f[5], f[10]);
      swap2(f[7], f[14]);
      swap2(f[11], f[13]);
    }  // # of swaps = 6
// -------------------------

    template <typename T>
    inline void revbin_permute_32(std::vector<complex<T>> &f)
    // unrolled version for length 32
    {
      swap2(f[1], f[16]);
      swap2(f[2], f[8]);
      swap2(f[3], f[24]);
      swap2(f[5], f[20]);
      swap2(f[6], f[12]);
      swap2(f[7], f[28]);
      swap2(f[9], f[18]);
      swap2(f[11], f[26]);
      swap2(f[13], f[22]);
      swap2(f[15], f[30]);
      swap2(f[19], f[25]);
      swap2(f[23], f[29]);
    }  // # of swaps = 12
// -------------------------

    template <typename T>
    inline void revbin_permute_64(std::vector<complex<T>> &f)
    // unrolled version for length 64
    {
      swap2(f[1], f[32]);
      swap2(f[2], f[16]);
      swap2(f[3], f[48]);
      swap2(f[4], f[8]);
      swap2(f[5], f[40]);
      swap2(f[6], f[24]);
      swap2(f[7], f[56]);
      swap2(f[9], f[36]);
      swap2(f[10], f[20]);
      swap2(f[11], f[52]);
      swap2(f[13], f[44]);
      swap2(f[14], f[28]);
      swap2(f[15], f[60]);
      swap2(f[17], f[34]);
      swap2(f[19], f[50]);
      swap2(f[21], f[42]);
      swap2(f[22], f[26]);
      swap2(f[23], f[58]);
      swap2(f[25], f[38]);
      swap2(f[27], f[54]);
      swap2(f[29], f[46]);
      swap2(f[31], f[62]);
      swap2(f[35], f[49]);
      swap2(f[37], f[41]);
      swap2(f[39], f[57]);
      swap2(f[43], f[53]);
      swap2(f[47], f[61]);
      swap2(f[55], f[59]);
    }  // # of swaps = 28
// -------------------------

    template<ordered_value T>
    inline void revbin_permute_leq_64(std::vector<complex<T>> &f)
    // Must have f.size() \in {2, 4, 8, 16, 32, 64}
    {
      switch ( f.size() ) {
//    case 1: break;
      case 2: break;
      case 4: revbin_permute_4(f); break;
      case 8: revbin_permute_8(f); break;
      case 16: revbin_permute_16(f); break;
      case 32: revbin_permute_32(f); break;
      case 64: revbin_permute_64(f); break;
//    default: ;  // ouch...
      }
    }
// -------------------------
  }

  template < typename T>
  auto revbin_permute(std::vector<eve::complex<T>>  & f)
  {
    auto n = f.size();
    auto  idx_swap = [&f](auto k,  auto r){
      auto z = f[k];  f[k] = f[r]; f[r] = z;
    };
    auto revbin = [](size_t x){ // Return x with reversed bit order.
                                // version using dynamically generated masks:
      size_t s = sizeof(size_t)*8 >> 1;
      size_t m = allbits(as<size_t>()) >> s;
      while ( s )
      {
        x = ( (x & m) << s ) ^ ( (x & (~m)) >> s );
        s >>= 1;
        m ^= (m<<s);
      }
      return  x;
    };

    auto  rvb = [revbin](size_t x, size_t ldn){
      // Return word with the ldn least significant bits
      //   (i.e. bit_0 ... bit_{ldn-1})  of x reversed,
      //   the other bits are set to zero.
      return  revbin(x) >> (sizeof(size_t)*8-ldn);
      // Bit-wise algorithm for small ldn:
      //    ulong r = 0;
      //    while ( ldn-- != 0 ) { r <<= 1; r += (x&1); x >>= 1; }
      //    return  r;
    };

    if ( n<=64 )
    {
      internal::revbin_permute_leq_64(f);
      return;
    }

    constexpr size_t  RBP_SYMM = 4; //, FAST_REVBIN = false,

    const size_t nh = (n>>1);
    const size_t n1  = n - 1;     // = 11111111
    const size_t nx1 = nh - 2;    // = 01111110
    const size_t nx2 = n1 - nx1;  // = 10111101

    size_t k = 0,  r = 0;
    while ( k < (n/RBP_SYMM)  )  // n>=16, n/2>=8, n/4>=4
    {
      // ----- k%4 == 0:
      if ( r>k )
      {
        idx_swap(k, r);          // <nh, <nh 11
        idx_swap(n1^k, n1^r);    // >nh, >nh 00
        idx_swap(nx1^k, nx1^r);  // <nh, <nh 11
        idx_swap(nx2^k, nx2^r);  // >nh, >nh 00
      }

      ++k;
      r ^= nh;

      // ----- k%4 == 1:
      if ( r>k )
      {
        idx_swap(k, r);  // <nh, >nh 10
        idx_swap(n1^k, n1^r);  // >nh, <nh 01
      }

      ++k;
      const size_t ldn = countr_zero(n);
      r = rvb(k, ldn);

      // ----- k%4 == 2:
      if ( r>k )
      {
        idx_swap(k, r);  // <nh, <nh 11
        idx_swap(n1^k, n1^r);  // >nh, >nh 00
      }

      ++k;
      r ^= nh;

      // ----- k%4 == 3:
      if ( r>k )
      {
        idx_swap(k, r);    // <nh, >nh 10
        idx_swap(nx1^k, nx1^r);   // <nh, >nh 10
      }

      ++k;


      r = rvb(k, countr_zero(n));
    }
  }

  template < typename T>
  auto revbin_permute(eve::algo::soa_vector<eve::complex<T>>  & f)
  {
    auto n = f.size();
    std::vector<eve::complex<T>> g(n);
    for(size_t i=0; i < n ; ++i) g[i] = f.get(i);
    revbin_permute(g);
    for(size_t i=0; i < n ; ++i)  f.set(i, g[i]);
  }

  template<value T, value T1>
  EVE_FORCEINLINE constexpr auto
  fft_df2_(EVE_SUPPORTS(cpu_), std::vector<eve::complex<T>> & f, T1 fac, T1 s) noexcept
  {
    using  c_t = complex<T>;
    auto n =  f.size();
    using i_t = decltype(n);
    EVE_ASSERT(is_pow2(n),  "data size is not a power of 2");
    std::vector<c_t> c(n);
    auto ldn = eve::countr_zero(n); //eve::log2(n));
    for (i_t ldm=ldn; ldm>=1; --ldm)
    {
      const ulong m = (1UL<<ldm);
      const i_t mh = m >> 1;
      const T  phi = s / T(mh);
      for (i_t r=0; r<n; r+=m)
      {
        for (i_t j=0; j<mh; ++j)
        {
          i_t i0 = r + j;
          i_t i1 = i0 + mh;
          auto u = f[i0];
          auto v = f[i1];

          f[i0] = (u + v);
          f[i1] = (u - v) *  exp_ipi( phi*j );
        }
      }
    }
    revbin_permute(f);
    for(size_t i=0; i < n; ++i) f[i] *= fac;
    return f;
  }

  template<value T, value T1>
  constexpr auto fft_df2_scalar(EVE_SUPPORTS(cpu_)
                         , eve::algo::soa_vector<eve::complex<T>> & f
                         , T1 fac
                         , T1 s) noexcept
  {
    using  c_t = complex<T>;
    auto n =  f.size();
    using i_t = decltype(n);
    EVE_ASSERT(is_pow2(n),  "data size is not a power of 2");
    std::vector<c_t> c(n);
    auto ldn = eve::countr_zero(n);
    for (i_t ldm=ldn; ldm>=1; --ldm)
    {
      const ulong m = (1UL<<ldm);
      const i_t mh = m >> 1;
      const T  phi = s / T(mh);
      for (i_t r=0; r<n; r+=m)
      {
        for (i_t j=0; j<mh; ++j)
        {
          i_t i0 = r + j;
          i_t i1 = i0 + mh;
          auto u = f.get(i0);
          auto v = f.get(i1);

          f.set(i0, (u + v));
          f.set(i1, (u - v) *  exp_ipi( phi*j));
        }
      }
    }
    revbin_permute(f);

    for(size_t i=0; i < n; ++i) f.set(i, f.get(i)*fac);
    return f;
  }


  template<value T, value T1>
  constexpr auto fft_df2_(EVE_SUPPORTS(cpu_)
                         , eve::algo::soa_vector<eve::complex<T>> & f
                         , T1 fac
                         , T1 s) noexcept
  {
    size_t cardinal = eve::nofs_cardinal_v<T>;
    using  c_t = complex<T>;
    auto n =  f.size();
    using i_t = decltype(n);
    EVE_ASSERT(is_pow2(n),  "data size is not a power of 2");
    std::vector<c_t> c(n);
    auto ldn = eve::countr_zero(n);
    int ii = 0;
    int jj = 0;
    for (i_t ldm=ldn; ldm>=1; --ldm)
    {
      const ulong m = (1UL<<ldm);
      const i_t mh = m >> 1;
      const T  phi = s / T(mh);
      if (cardinal >=  mh)
      {
        ++ii;
        for (i_t r=0; r<n; r+=m)
        {
         for (i_t j=0; j<mh; ++j)
          {
            i_t i0 = r + j;
            i_t i1 = i0 + mh;
            auto u = f.get(i0);
            auto v = f.get(i1);
            f.set(i0, (u + v));
            f.set(i1, (u - v) *  exp_ipi( phi*j));
          }
        }
      }
      else
      {
        ++jj;
        for (i_t r=0; r<n; r+=m)
        {
          auto doit = [phi](
            eve::algo::soa_vector<eve::complex<T>>& f,
            std::ptrdiff_t r,
            std::ptrdiff_t mh) {
            EVE_ASSERT(mh > eve::nofs_cardinal_v<T>, "");
            auto s = f.begin() + r;
            auto m = s + mh;

            // maybe uint64_t for doubles
            auto view = eve::views::zip(eve::algo::as_range(s, m), m,
                                        eve::views::iota(std::uint32_t{0}));

            // transform does
            eve::algo::for_each[eve::algo::expensive_callable](
              view, [phi](auto zz, auto ignore) {
                auto [u_it, v_it, _] = zz;
                auto [u, v, idx] = eve::load[ignore](zz);

                eve::store[ignore]((u + v), u_it);
                eve::store[ignore](
                  (u - v) * eve::exp_ipi(phi*eve::convert(idx, eve::as<T>{})),
                  v_it);
              });
          };
          doit(f, r, mh);
        }
      }
    }
    revbin_permute(f);
    for(size_t i=0; i < n; ++i) f.set(i, f.get(i)*fac);
    std::cout << "simd   " << jj << std::endl;
    std::cout << "scalar " << ii << std::endl;

    return f;
  }
}
