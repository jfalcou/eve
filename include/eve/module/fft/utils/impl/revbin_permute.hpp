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
    template < range R>
    inline void revbin_permute_leq_64(R & f) noexcept
    // Must have f.size() \in {1, 2, 4, 8, 16, 32, 64}
    {
      auto n = size(f);
      auto fbeg = f.data();
      EVE_ASSERT(n <= 64 && is_pow2(n), "size is greater than 64 or is not a power of 2");
      auto iswap = [fbeg](auto k, auto r) noexcept {
        auto t(*(fbeg+k));  *(fbeg+k) = *(fbeg+r); *(fbeg+r) = t;
      };

      switch ( n ) {
      case 1:  break;
      case 2:  break;
      case 4: { iswap(1, 2);
          break; }
      case 8: { iswap(1, 4);  iswap(3, 6);
          break; }
      case 16:{ iswap(1, 8);  iswap(2, 4);   iswap(3, 12);  iswap(5, 10);  iswap(7, 14);  iswap(11, 13);
          break; }
      case 32:{ iswap(1, 16); iswap(2, 8);   iswap(3, 24);  iswap(5, 20);  iswap(6, 12);  iswap(7, 28);
                iswap(9, 18); iswap(11, 26); iswap(13, 22); iswap(15, 30); iswap(19, 25); iswap(23, 29);
          break; }
      case 64:{ iswap(1, 32); iswap(2, 16);  iswap(3, 48);  iswap(4, 8);   iswap(5, 40);  iswap(6, 24);
                iswap(7, 56); iswap(9, 36);  iswap(10, 20); iswap(11, 52); iswap(13, 44); iswap(14, 28);
                iswap(15, 60);iswap(17, 34); iswap(19, 50); iswap(21, 42); iswap(22, 26); iswap(23, 58);
                iswap(25, 38);iswap(27, 54); iswap(29, 46); iswap(31, 62); iswap(35, 49); iswap(37, 41);
                iswap(39, 57);iswap(43, 53); iswap(47, 61); iswap(55, 59);
          break; }
      default:;  // normally have asserted here
      }
    }

    inline auto revbin_le64(auto iswap, auto n) noexcept
    {
      switch ( n ) {
      case 1:  break;
      case 2:  break;
      case 4: { iswap(1, 2);
          break; }
      case 8: { iswap(1, 4);  iswap(3, 6);
          break; }
      case 16:{ iswap(1, 8);  iswap(2, 4);   iswap(3, 12);  iswap(5, 10);  iswap(7, 14);  iswap(11, 13);
          break; }
      case 32:{ iswap(1, 16); iswap(2, 8);   iswap(3, 24);  iswap(5, 20);  iswap(6, 12);  iswap(7, 28);
                iswap(9, 18); iswap(11, 26); iswap(13, 22); iswap(15, 30); iswap(19, 25); iswap(23, 29);
          break; }
      case 64:{ iswap(1, 32); iswap(2, 16);  iswap(3, 48);  iswap(4, 8);   iswap(5, 40);  iswap(6, 24);
                iswap(7, 56); iswap(9, 36);  iswap(10, 20); iswap(11, 52); iswap(13, 44); iswap(14, 28);
                iswap(15, 60);iswap(17, 34); iswap(19, 50); iswap(21, 42); iswap(22, 26); iswap(23, 58);
                iswap(25, 38);iswap(27, 54); iswap(29, 46); iswap(31, 62); iswap(35, 49); iswap(37, 41);
                iswap(39, 57);iswap(43, 53); iswap(47, 61); iswap(55, 59);
          break; }
      default:;  // normally have asserted here
      }
    }

    template < range R>
    inline void revbin_permute_le_64(R & f) noexcept
    // Must have f.size() \in {1, 2, 4, 8, 16, 32, 64}
    {
      auto n = std::size(f);
      auto fbeg = f.data();
      EVE_ASSERT(n <= 64 && is_pow2(n), "size is greater than 64 or is not a power of 2");
      auto iswap = [fbeg](auto k, auto r)  {
        auto t(*(fbeg+k));  *(fbeg+k) = *(fbeg+r); *(fbeg+r) = t;
      };
      revbin_le64(iswap, n);
    }

    template < range R>
    inline void revbin_permute_le_64(R & fr, R& fi) noexcept
    {
      auto n = std::size(fr);
      auto frbeg = fr.data();
      auto fibeg = fi.data();
      EVE_ASSERT(n <= 64 && is_pow2(n), "size is greater than 64 or is not a power of 2");
      auto iswap = [frbeg, fibeg](auto k, auto r)  noexcept {
        auto tr(*(frbeg+k));  *(frbeg+k) = *(frbeg+r); *(frbeg+r) = tr;
        auto ti(*(fibeg+k));  *(fibeg+k) = *(fibeg+r); *(fibeg+r) = ti;
      };
      revbin_le64(iswap, n);
    }

    inline auto revbin_gt64(auto iswap, auto n)  noexcept
    {
      auto revbin = [](auto x, auto ldn) noexcept {
        auto siz = sizeof(element_type_t< decltype(x)>)*8;
        return  eve::bit_reverse(x) >> (siz-ldn);
      };
      EVE_ASSERT(n > 64u, "revbin_permute_gt_64 : not enough datas elements");
      EVE_ASSERT(is_pow2(n), "data size must be a power of 2");
      const size_t ldn =  eve::countr_zero(n);
      const size_t nh = (n>>1);
      const size_t n1  = n - 1;
      const size_t nx1 = nh - 2;
      const size_t nx2 = n1 - nx1;

      size_t k = 0,  r = 0;
      while ( k < (n >> 2)  )
      {
        if ( r>k ){  iswap(k, r); iswap(n1^k, n1^r); iswap(nx1^k, nx1^r); iswap(nx2^k, nx2^r); }
        ++k;
        r ^= nh;
        if ( r>k ) { iswap(k, r); iswap(n1^k, n1^r); }
        ++k;
        r = revbin(k, ldn);
        if ( r>k ) { iswap(k, r); iswap(n1^k, n1^r); }
        ++k;
        r ^= nh;
        if ( r>k ) {  iswap(k, r); iswap(nx1^k, nx1^r); }
        ++k;
        r = revbin(k, ldn);
      }
    }

    template < range R>
    inline auto revbin_permute_gt_64(R & fr, R & fi)  noexcept
    {
      auto frbeg = fr.data();
      auto fibeg = fi.data();
      auto iswap = [frbeg, fibeg](auto k, auto r)  noexcept {
        auto tr(*(frbeg+k));  *(frbeg+k) = *(frbeg+r); *(frbeg+r) = tr;
        auto ti(*(fibeg+k));  *(fibeg+k) = *(fibeg+r); *(fibeg+r) = ti;
      };
      revbin_gt64(iswap, std::size(fr));
    }

    template < range R>
    inline auto revbin_permute_gt_64(R & f)  noexcept
    {
      auto fbeg = f.data();
      auto iswap = [fbeg](auto k, auto r)  noexcept {
        auto t(*(fbeg+k));  *(fbeg+k) = *(fbeg+r); *(fbeg+r) = t;
      };
      revbin_gt64(iswap, std::size(f));
    }
  }

  template<range R>
  EVE_FORCEINLINE constexpr void
  revbin_permute_(EVE_SUPPORTS(cpu_), aos_type const &, R & f) noexcept
  {
    auto n = std::size(f);
    if ( n<=64 )
      internal::revbin_permute_le_64(f);
    else
      internal::revbin_permute_gt_64(f);
  }

  template<range R>
  EVE_FORCEINLINE constexpr void
  revbin_permute_(EVE_SUPPORTS(cpu_), aos_type const &, R & fr, R & fi) noexcept
  {
    EVE_ASSERT(std::size(fr) == std::size(fi), "fr and fi must share the same size");
    auto n = std::size(fr);
    if ( n<=64 )
      internal::revbin_permute_le_64(fr, fi);
    else
      internal::revbin_permute_gt_64(fr, fi);
  }

  template <range R>
  auto revbin_permute_(EVE_SUPPORTS(cpu_), soa_type const &, R & f)  noexcept
    requires(eve::is_complex_v<typename R::value_type>)
  {
    using T = typename R::value_type;
    auto n = std::size(f);
    std::vector<T> g(n);
    for(size_t i=0; i < n ; ++i) g[i] = f.get(i);
    aos(revbin_permute)(g);
    for(size_t i=0; i < n ; ++i)  f.set(i, g[i]);
  }
}
