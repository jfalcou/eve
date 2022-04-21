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
#include <eve/module/algo.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <iostream>
#include <numeric>
namespace eve::detail
{
  //================================================================================================
  //N parameters
  //================================================================================================
  // pedantic just ensure that if one element is infinite the sum is infinite (even if nans are present)
  template<real_value T0, real_value ...Ts>
  auto asum_(EVE_SUPPORTS(cpu_), pedantic_type const &, T0 a0, Ts... args)
  {
    using r_t = common_compatible_t<T0,Ts...>;
    r_t that(eve::abs(a0));
    auto inf_found = is_infinite(that);
    auto addabs = [&inf_found](auto that, auto next)->r_t{
      auto z = eve::abs(next);
      inf_found = inf_found || is_infinite(z);
      that+= z;
      return that;
    };
    ((that = addabs(that,args)),...);
    return if_else(inf_found, inf(as<r_t>()), that);
  }

  // regular just do the naive summation
  template<real_value T0, real_value ...Ts>
  common_compatible_t<T0,Ts...> asum_(EVE_SUPPORTS(cpu_), T0 a0, Ts... args)
  {
    using r_t = common_compatible_t<T0,Ts...>;
    r_t that(eve::abs(a0));
    auto addabs = [](auto that, auto next)->r_t{
      that+= eve::abs(next);
      return that;
    };
    ((that = addabs(that,args)),...);
    return that;
  }

  // comp performs kahan compensation using the two_add algorithm
  template<real_value T0, real_value ...Ts>
  auto asum_(EVE_SUPPORTS(cpu_), comp_type const &, T0 a0, Ts... args)
  {
    using r_t = common_compatible_t<T0,Ts...>;
    r_t that(eve::abs(a0));
    auto inf_found = is_infinite(that);
    r_t c(0);
    auto kaddabs = [&c, &inf_found](auto that, auto next)->r_t{
      auto a = eve::abs(next);
      auto [s, err] = two_add(that, a);
      c+= err;
      inf_found = inf_found || is_infinite(a);
      return s;
    };
    ((that = kaddabs(that,args)),...);
    return if_else(inf_found, inf(as<r_t>()), that+c);
  }

  ////////////////////////////////////////////////////////////////////////////////
  //range algorithms
  ////////////////////////////////////////////////////////////////////////////////
  // regular just naive sum but simd reduce used
  template<range R>
  auto asum_(EVE_SUPPORTS(cpu_), R const & xs)
    requires (!simd_value<R>)
  {
    using r_t = typename R::value_type;
    auto first = begin(xs);
    auto last  = end(xs);
    if (first == last) return r_t(0);
    auto that = abs(r_t(*first));
    if (std::distance(first, last) == 1) return that;
    else
    {
      auto absadd = [](auto x){ return eve::abs(x);};
      return eve::algo::reduce(xs, std::pair{absadd, r_t(0)}, r_t(0));
    }
  }
  template<range R>
  auto asum_(EVE_SUPPORTS(cpu_), pedantic_type const &, R const & xs)
    requires (!simd_value<R>)
  {
    using r_t = typename R::value_type;
    auto first = begin(xs);
    auto last  = end(xs);
    if (first == last) return r_t(0);
    auto that = abs(r_t(*first));
    if (std::distance(first, last) == 1) return that;
    else
    {
      ++first;
      auto inf_found = is_infinite(that);
      r_t c(0);
      for(; first != last; ++first)
      {
        auto a = eve::abs(*first);
        auto [s, err] = two_add(that, a);
        that = s;
        c+= err;
        inf_found = inf_found || is_infinite(a);
      };
      return if_else(inf_found, inf(as<r_t>()), that+c);
    }
  }

//   template<range R>
//   auto asum_(EVE_SUPPORTS(cpu_), R const & xs)
//     requires (!simd_value<R>)
//   {
//     using r_t = typename R::value_type;
//     return std::transform_reduce(begin(xs), end(xs), r_t(0), eve::add, eve::abs);
//   }

  template<range R>
  auto asum_(EVE_SUPPORTS(cpu_), comp_type const &, R const & xs)
    requires (!simd_value<R>)
  {
    using v_t = typename R::value_type;
    using r_t =  kumi::tuple<v_t, v_t>;
    auto red = [](auto that, auto x){
      auto & [s, err] = two_add(get<0>(that), x);
      err+= get<1>(that);
      return r_t{s, err};
    };
    auto that= std::transform_reduce(begin(xs), end(xs), r_t{0, 0}, red, eve::abs);
    return get<0>(that)+get<1>(that);
  }


//   template<range R>
//   auto asum_(EVE_SUPPORTS(cpu_), R const & xs)
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
