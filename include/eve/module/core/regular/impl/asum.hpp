//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/two_add.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <iostream>

namespace eve::detail
{
  //================================================================================================
  //N parameters
  //================================================================================================
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

//   template<real_value T0, real_value ...Ts>
//   auto asum_(EVE_SUPPORTS(cpu_), numeric_type const &, T0 a0, Ts... args)
//   {
//     using r_t = common_compatible_t<T0,Ts...>;
//     r_t that(eve::abs(a0));
//     auto inf_found = is_infinite(that);
//     r_t c(0);
//     auto kaddabs = [&c, &inf_found](auto that, auto next)->r_t{
//       auto a = eve::abs(next);
//       inf_found = inf_found || is_infinite(a);
//       auto y = a-c;            // c is zero the first time around.
//       auto t = that + y;       // Alas, sum is big, y small, so low-order digits of y are lost.
//       c = (t - that) - y;      // (t - sum) cancels the high-order part of y; subtracting y recovers negative (low part of y)
//       return t;
//     };
//     ((that = kaddabs(that,args)),...);
// //     std::cout << std::endl << "c      " << c << std::endl;
// //     std::cout << "that   " << that << std::endl;
// //     std::cout << "that+c "<< that+c<< std::endl;
// //     std::cout << "that-c "<< that-c<< std::endl;
//     return if_else(inf_found, inf(as<r_t>()), that);
//   }


  template<real_value T0, real_value ...Ts>
  auto asum_(EVE_SUPPORTS(cpu_), numeric_type const &, T0 a0, Ts... args)
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
//     std::cout << std::endl << "c      " << c << std::endl;
//     std::cout << "that   " << that << std::endl;
//     std::cout << "that+c "<< that+c<< std::endl;
//     std::cout << "that-c "<< that-c<< std::endl;
    return if_else(inf_found, inf(as<r_t>()), that+c);
  }


  template<range R>
  auto asum_(EVE_SUPPORTS(cpu_), numeric_type const &, R const & xs)
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

//     std::cout << std::endl << "c      " << c << std::endl;
//     std::cout << "that   " << that << std::endl;
//     std::cout << "that+c "<< that+c<< std::endl;
//     std::cout << "that-c "<< that-c<< std::endl;
      return if_else(inf_found, inf(as<r_t>()), that+c);
    }
  }
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
      ++first;
        auto inf_found = is_infinite(that);
      r_t c(0);
      for(; first != last; ++first)
      {
        that += abs(*first);
      };

//     std::cout << std::endl << "c      " << c << std::endl;
//     std::cout << "that   " << that << std::endl;
//     std::cout << "that+c "<< that+c<< std::endl;
//     std::cout << "that-c "<< that-c<< std::endl;
      return that;
    }
  }
}
