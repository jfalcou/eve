//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "unit/algo/algo_test.hpp"
#include <algorithm>
#include <eve/module/core.hpp>
#include <eve/algo/iota.hpp>
#include <eve/views/iota.hpp>
#include <eve/views/zip.hpp>
#include <eve/algo/transform.hpp>
//#include <eve/views/transform.hpp>
#include <iostream>
#include <ranges>
#include <eve/concept/value.hpp>


template<eve::floating_scalar_value T>
auto linspace2(T a,  T b, std::ptrdiff_t n)
{
  return  eve::views::map ( eve::views::iota(T{0},n), lerpoid<T>{a,b,n} );
}

template < typename R, eve::floating_scalar_value T> R linspace(R & r, T a,  T b, ptrdiff_t n)
{
  EVE_ASSERT(eve::is_finite(a), "a is not finite");
  EVE_ASSERT(eve::is_finite(b), "b is not finite");
  r.resize(n);
  eve::algo::iota(r, T{0});
    T nm1 = eve::rec(eve::dec(T(n)));
  auto f = [a, b, nm1](auto i){return eve::lerp(a, b, i*nm1); };
  eve::algo::transform_inplace(r, f);
  return r;
}

template <typename R, eve::floating_scalar_value T> auto linspace_view(R & r, T a, T b, ptrdiff_t n)
{
  r.resize(n);
  auto io = eve::views::iota(T{0}, n);
  T nm1 = eve::rec(eve::dec(T(n)));
  auto f = [a, b, nm1](auto i){return eve::lerp(a, b, i*nm1); };
  eve::algo::transform_to(eve::views::zip(io, r), f); // views::transform... are missing pipe operator also missing
 //  T nm1 = eve::rec(eve::dec(T(n)));
 //   auto f = [a, b, nm1](auto i){return eve::lerp(a, b, i*nm1); };
 //   return eve::views::iota(T{0}, n) | eve::algo::transform_inplace(f);
  return r;
}

template <eve::floating_scalar_value T> auto linspace_scaled(T a, T b, ptrdiff_t n)
{
  T nm1 = eve::rec(eve::dec(T(n)));
  auto io = eve::views::iota_scaled(T{a}, T(b-a)*nm1, n);
  return io;
}

EVE_TEST_TYPES("Check iota_scaled_iterator, conversions", eve::test::scalar::ieee_reals)
<typename T>(eve::as<T> )
{

  auto print = [&](auto v, std::string s) {
        for (std::cout << s << " : "; auto iv: v)
            std::cout << iv << " ";
        std::cout << "\n";
    };

  std::vector<T>  r;
  r = linspace(r, T(0.0), T(1.0), 100);
  print(r, "r");
  std::vector < T > r1;
  r1 = linspace_view(r1, T(0.0), T(1.0), 100);
  print(r1, "r1");
//  auto r2(linspace_scaled(T(0.0), T(1.0), 100));
//  print(r2, "r2");

  for (int i : eve::views::iota(1, 10))
    std::cout << i << ' ';
  std::cout << '\n';

  //std::ranges::iota_view(T(0.0), 100);
//   for(T rr : std::ranges::iota_view(T(0.0), 100)) std::cout << rr << " ";
//   std::cout << std::endl;
 {
 }
};
