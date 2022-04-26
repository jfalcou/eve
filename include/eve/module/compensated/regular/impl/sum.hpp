//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/module/core.hpp>
#include <eve/algo/reduce.hpp>
#include <eve/algo/transform.hpp>

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <iostream>
#include <numeric>
#include <eve/algo/views/map.hpp>

namespace eve::detail
{
  //================================================================================================
  //N parameters
  //================================================================================================

  // regular just do the naive summation
  template<real_value T0, real_value ...Ts>
  common_compatible_t<T0,Ts...> sum_(EVE_SUPPORTS(cpu_), T0 a0, Ts... args)
  {
    using r_t = common_compatible_t<T0,Ts...>;
    r_t that(eve::abs(a0));
    auto addabs = [](auto that, auto next)->r_t{
      that += next;
      return that;
    };
    ((that = addabs(that,args)),...);
    return that;
  }

  // comp performs kahan compensation using the two_add algorithm
  template<real_value T0, real_value ...Ts>
  auto sum_(EVE_SUPPORTS(cpu_), comp_type const &, T0 a0, Ts... args)
  {
    using r_t = common_compatible_t<T0,Ts...>;
    r_t that(eve::abs(a0));
    r_t c(0);
    auto kaddabs = [&c](auto that, auto next)->r_t{
      auto [s, err] = two_add(that, next);
      c+= err;
      return s;
    };
    ((that = kaddabs(that,args)),...);
    return that+c;
  }


  // faithfull performs faithfull rounding algorithm
  template<floating_scalar_value ...Ts>
  auto sum_(EVE_SUPPORTS(cpu_), faithfull_type const &, Ts... args)
  {
    using r_t = common_compatible_t<Ts...>;
    std::vector<r_t> v{r_t(args)...};
    return faithfull(sum)(v);
  }


  ////////////////////////////////////////////////////////////////////////////////
  //range algorithms
  ////////////////////////////////////////////////////////////////////////////////

  // regular eve::reduce used
  template<range R>
  auto sum_(EVE_SUPPORTS(cpu_), R const & xs)
    requires (!simd_value<R>)
  {
    using r_t = typename R::value_type;
    return eve::algo::reduce(xs, r_t(0));
  }

  //=   compensated with eve::reduce and eve::view::map
  template<range R>
  auto sum_(EVE_SUPPORTS(cpu_), comp_type const &, R const & xs)
    requires (!simd_value<R>)
  {
    using v_t = typename R::value_type;
    using r_t = kumi::tuple<v_t, v_t>;
    r_t init{v_t(0), v_t(0)};
    auto absadd = [](auto that, auto x)
    {
      auto [next, err] = two_add(get<0>(that), get<0>(x));
      return eve::zip(next, get<1>(that)+err);
    };
    auto zipit = []<typename T>(T e){ return eve::zip(e, T(0)); };
    auto [s, c] = eve::algo::reduce( eve::algo::views::map(xs, zipit)
                                      , std::pair{absadd, init}
                                      , init
                                      );
    return s+c;
  }

  //=   fast faithfull computes the sum with faithfull rounding
  template<range R>
  typename R::value_type sum_(EVE_SUPPORTS(cpu_), faithfull_type const &, R p, int )
    requires (!simd_value<R>)
  {
    using r_t = typename R::value_type;
    const r_t epsi = eps(as<r_t>())/2;
    const r_t two_realmin = 2*smallestposval(as<r_t>());
    size_t n = end(p)-begin(p);
    auto T  = eve::algo::reduce(eve::algo::views::map(p, abs), r_t(0))*inc(inc(n)*epsi);
    if (T <= two_realmin) return eve::algo::reduce(p, r_t(0));
    r_t tprim(0), tau, t, phi;
//    int cnt = 0;
    while (true)
    {
//      ++cnt;
      r_t sigma0 = 2*T*inc((3*n+2)*epsi);
//      if (cnt == 150) break;
      auto sigma =  sigma0;
//       auto zipit = []<typename T>(T e){ return eve::zip(e, T(0)); };
//       auto psig = eve::algo::views::map(p, zipit);

//       auto extract_vector = []( auto psig){
//         auto &sigma = get<1>(psig);
//         auto &p     = get<0>(psig);
//         auto sigmap = sigma + p;
//         auto q = sigmap-sigma;
//         p -= q;
//         sigma = sigmap;
//       };
//       using t_t =  kumi::tuple<r_t, r_t>;
//       t_t init{r_t(0), r_t(sigma0)};
//       auto [pipo, s] = eve::algo::reduce(psig, extract_vector
//                       , std::pair{extract_vector, init}
//                       , init);
//       sigma = s;

      for (auto cur = std::begin(p); cur != std::end(p); ++cur)
      {
        auto sigmap = sigma + *cur;
        auto q = sigmap-sigma;
        *cur -= q;
        sigma = sigmap;
      }

      tau = sigma-sigma0;
      t = tprim;
      tprim = t+tau;
      if (is_eqz(tprim)) {
        r_t res = faithfull(sum)(p);
        return res;
      }
      auto m1 = (r_t(1.5)+4*epsi)*(n*epsi)*sigma0;
      auto m2 = (2*n*epsi)*ufp(sigma0);
      phi = (2*n*(n+2)*epsi*ufp(sigma))/inc(6*epsi);
      T = min(m1, m2);
//       std::cout << "cnt =  " << cnt << std::endl;
//       std::cout << "tprim " << tprim << std::endl;
//       std::cout << "phi " << phi << std::endl;
//       std::cout << " T " <<  T << std::endl;
//       std::cout << "  two_realmin " <<  two_realmin << std::endl;
      if ((tprim >= phi) || (4*T <= two_realmin)) break;
    }
//     std::cout << "fin"<< std::endl;
//     std::cout << "cnt" << cnt << std::endl;
//     std::cout << "tprim " << tprim << std::endl;
//     std::cout << "phi " << phi << std::endl;
//     std::cout << " T " <<  T << std::endl;
    auto tau2 = (t-tprim)+tau;
    return tprim+(tau2+eve::algo::reduce(p, r_t(0)));
  }

  //=   faithfull computes the sum with faithfull rounding
  template<range R>
  typename R::value_type sum_(EVE_SUPPORTS(cpu_), faithfull_type const &, R p)
    requires (!simd_value<R>)
  {
    using r_t = typename R::value_type;
    auto mu = eve::algo::reduce(p, std::pair{ maxabs, r_t(0)}, r_t(0));
    size_t n = end(p)-begin(p);
    if(is_eqz(mu) || is_eqz(n)) return mu;
    auto Ms = bit_ceil(n+2);
    auto sigma = Ms*bit_ceil(mu);
    auto phi = Ms*halfeps(as(mu));
    auto factor = phi*Ms;
    r_t t(0);
    std::vector<r_t> q(n);
    while (true)
    {
      auto extract_vector = [&sigma]( auto p){ return (sigma+p)-sigma; };
      eve::algo::transform_to(p, q, extract_vector);
      auto tau = sum(q);
      auto zipped = eve::algo::views::zip(p, q);
      eve::algo::transform_to(zipped, p, [](auto z){return get<0>(z)-get<1>(z); });
      auto tau1 = t+tau;
      if (( abs(tau1)>=factor*sigma ) || ( sigma<=smallestposval(as(tau))))
      {
        auto tau2 = tau - ( tau1 - t );
        auto res = tau1 + ( tau2 + sum(p) );
        return res;
      }
      t = tau1;
      if(is_eqz(t)){
        r_t res = faithfull(sum)(p);
        return res;
      }
      sigma = phi*sigma;
    }
  }


//   template<range R>
//   auto sum_(EVE_SUPPORTS(cpu_), comp_type const &, R const & xs)
//     requires (!simd_value<R>)
//   {
//     using v_t = typename R::value_type;
//     using r_t =  kumi::tuple<v_t, v_t>;
//     auto red = [](auto that, auto x){
//       auto & [s, err] = two_add(get<0>(that), x);
//       err+= get<1>(that);
//       return r_t{s, err};
//     };
//     auto that= std::transform_reduce(begin(xs), end(xs), r_t{0, 0}, red, eve::abs);
//     return get<0>(that)+get<1>(that);
//   }


//   template<range R>
//   auto sum_(EVE_SUPPORTS(cpu_), R const & xs)
//     requires (!simd_value<R>)
//   {
//     using r_t = typename R::value_type;
//     auto first = begin(xs);
//     auto last  = end(xs);
//     if (first == last) return r_t(0);
//     auto that = abs(r_t(*first));
//     if (std::distance(first, last) == 1) return that;
//     else
//     {
//       ++first;
//         auto inf_found = is_infinite(that);
//       r_t c(0);
//       for(; first != last; ++first)
//       {
//         that += abs(*first);
//       };

//     std::cout << std::endl << "c      " << c << std::endl;
//     std::cout << "that   " << that << std::endl;
//     std::cout << "that+c "<< that+c<< std::endl;
//     std::cout << "that-c "<< that-c<< std::endl;
//     return that;
//   }
// }


}
