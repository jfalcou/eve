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
#include <eve/module/fft/utils.hpp>

namespace eve::detail
{
  template <typename Type>
  static inline void sumdiff3_r(Type &a, Type b, Type &d)
  // {a,b,d} <--| {a+b, b, b-a}  (used in split-radix FFTs)
  // NEVER call like func(a,b,a) or func(a,b,b)
  { d=b-a; a+=b; }

  ///////////////////////////////////////////////////////////////////
  // fft decimation in frequency radix 4

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE  void
  fft_split_(EVE_SUPPORTS(cpu_), aos_type const &
              , R & fr
              , R & fi
              , T fac) noexcept
  //  requires(std::is_floating_point_v<typename R::value_type>)
  {

    [[maybe_unused]] auto pr = [](auto name, auto v){
      std::cout << name << " = (";
      for(size_t i=0; i < v.size() ; ++i) std::cout << *(v.begin()+i) << " ";
      std::cout << ")\n";
    };
//     auto cubeit = [](auto cs)  {
//       auto [c, s] = cs;
//       auto tq = T(3)/4;
//       return as_complex<decltype(s)>{ 4*c*fms(c, c, tq), 4*s*fsm(tq, s, s)};
//     };
    auto n =  fr.size();
    using i_t = decltype(n);
    using c_t = eve::complex<T>;
    auto flip = []<typename U>(U c){
      return U{imag(c), real(c)};
    };
    EVE_ASSERT(is_pow2(n),  "data size is not a power of 2");
    auto ldn = eve::countr_zero(n); //eve::log2(n));
    if ( !ldn )  return;
    auto frbeg = fr.data();
    auto fibeg = fi.data();

    i_t n2 = 2 * n;
    for (i_t k=0; k<ldn; k++)
    {
      n2 >>= 1;
      i_t n4 = n2 >> 2;
      auto ph0 = 2*rec(T(n2));
      if(n4 >= eve::nofs_cardinal_v<T>)
      {
        auto js = eve::views::iota(T{0}, n4);
        auto phs= eve::views::iota_with_step(T{0}, ph0, n4);
        auto view = eve::views::zip(js, phs);
        auto doit = [flip, n, n2, n4, frbeg, &fibeg](auto zz, auto ignore){
           auto [j, ph] = load[ignore](zz);
           auto cs1 = exp_ipi(ph);
           auto cs3 = sqr(cs1)*cs1;
           auto sc1 = flip(cs1);
           auto ix = i_t(j.get(0));
           i_t id = (n2<<1);
           while ( ix<n )
           {
//             std::cout << "ix " << ix << " id " << id << std::endl;
             for (i_t i0=ix; i0<n; i0+=id)
             {
               i_t i1 = i0 + n4;
               i_t i2 = i1 + n4;
               i_t i3 = i2 + n4;
               auto fri0 = load(frbeg+i0);
               auto fri1 = load(frbeg+i1);
               auto fri2 = load(frbeg+i2);
               auto fri3 = load(frbeg+i3);
               auto fii0 = load(fibeg+i0);
               auto fii1 = load(fibeg+i1);
               auto fii2 = load(fibeg+i2);
               auto fii3 = load(fibeg+i3);
               using w_t = decltype(fri0);

               w_t tr0, tr1;
               sd(fri0, fri2, tr0);
               sd(fri1, fri3, tr1);

               w_t ti0, ti1;
               sd(fii0, fii2, ti0);
               sd(fii1, fii3, ti1);

               w_t t3, t4;
               sd(tr0, ti1, t3);
               tr0 = -tr0;

               sumdiff3_r(tr1, ti0, t4);
               kumi::tie(fri2, fii2) = kumi::to_tuple(sc1*eve::as_complex_t<w_t>{t4, tr0});
               kumi::tie(fii3, fri3) = kumi::to_tuple(cs3*eve::as_complex_t<w_t>{tr1, t3});
               store(fri0, frbeg+i0);
               store(fri1, frbeg+i1);
               store(fri2, frbeg+i2);
               store(fri3, frbeg+i3);
               store(fii0, fibeg+i0);
               store(fii1, fibeg+i1);
               store(fii2, fibeg+i2);
               store(fii3, fibeg+i3);
             }
             ix = (id<<1) - n2 + i_t(j.get(0));
             id <<= 2;
           }
        };
        eve::algo::for_each[eve::algo::expensive_callable](view, doit);
      }
      else
      {
        for (i_t j=0; j<n4; j++)
        {
          auto a = j * ph0;
          auto cs1 = exp_ipi(a);
          auto cs3 =sqr(cs1)*cs1;
          auto sc1 = flip(cs1);
          i_t ix = j;
          i_t id = (n2<<1);
          while ( ix<n )
          {
            for (i_t i0=ix; i0<n; i0+=id)
            {
              i_t i1 = i0 + n4;
              i_t i2 = i1 + n4;
              i_t i3 = i2 + n4;
              auto fri0 = (frbeg+i0);
              auto fri1 = (frbeg+i1);
              auto fri2 = (frbeg+i2);
              auto fri3 = (frbeg+i3);
              auto fii0 = (fibeg+i0);
              auto fii1 = (fibeg+i1);
              auto fii2 = (fibeg+i2);
              auto fii3 = (fibeg+i3);

              T tr0, tr1;
              sd(*fri0, *fri2, tr0);
              sd(*fri1, *fri3, tr1);

              T ti0, ti1;
              sd(*fii0, *fii2, ti0);
              sd(*fii1, *fii3, ti1);

              T t3, t4;
              sd(tr0, ti1, t3);
              tr0 = -tr0;

              sumdiff3_r(tr1, ti0, t4);
              kumi::tie(*fri2, *fii2) = kumi::to_tuple(sc1*c_t{t4, tr0});
              kumi::tie(*fii3, *fri3) = kumi::to_tuple(cs3*c_t{tr1, t3});
           }

            ix = (id<<1) - n2 + j;
            id <<= 2;
          }
        }
      }
    }
    for (i_t ix=0, id=4;  ix<n;  id*=4)
    {
      for (i_t i0=ix; i0<n; i0+=id)  sd(*(frbeg+i0), *(frbeg+i0+1));

        ix = 2*(id-1);
    }

    for (i_t ix=0, id=4;  ix<n;  id*=4)
    {
      for (i_t i0=ix; i0<n; i0+=id)  sd(*(fibeg+i0), *(fibeg+i0+1));

        ix = 2*(id-1);
    }
    aos(revbin_permute)(fr);
    aos(revbin_permute)(fi);
    scaleit(fr, fi, fac);
  }

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE  void
  fft_split_(EVE_SUPPORTS(cpu_), aos_type const &
              , R &f
              , T fac) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
    auto n =  f.size();
    using i_t =  decltype(n);
    using c_t = eve::complex<T>;
    std::vector<T> fr(n),  fi(n);
    auto b = f.begin();
    for(i_t i=0; i < n; ++i)
    {
      auto z = *(b+i);
      fr[i] = real(z);
      fi[i] = imag(z);
    }
    aos(fft_split)(fi, fr, fac);
    for(i_t i=0; i < n; ++i)
    {
      *(b+i) = c_t(fr[i], fi[i]);
    }
  }

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE  void
  fft_split_(EVE_SUPPORTS(cpu_), soa_type const &
           , R &f
           , T fac) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
    auto [fr, fi] = soac2ri(f);
    aos(fft_split)(fi, fr, fac);
  }

}
