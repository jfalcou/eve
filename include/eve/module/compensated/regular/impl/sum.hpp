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

  //==   compensated with naive loop
  //  template<range R>
  //   auto sum_(EVE_SUPPORTS(cpu_), comp_type const &, R const & xs)
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
  //       r_t c(0), err;
  //       for(; first != last; ++first)
  //       {
  //         std::tie(that, err] = two_add(that, *first);
  //         c+= err;
  //       };
  //       return that+c;
  //     }
  //  }

  //= compensated with naive loop
 //  template<range R>
//   auto sum_(EVE_SUPPORTS(cpu_), pedantic_type const &, R const & xs)
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
//       auto inf_found = is_infinite(that);
//       r_t c(0);
//       for(; first != last; ++first)
//       {
//         auto a = eve::abs(*first);
//         auto [s, err] = two_add(that, a);
//         that = s;
//         c+= err;
//         inf_found = inf_found || is_infinite(a);
//       };
//       return if_else(inf_found, inf(as<r_t>()), that+c);
//     }
//   }


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
