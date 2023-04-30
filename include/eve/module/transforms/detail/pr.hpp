//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <iostream>
#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>

template<eve::algo::relaxed_range R>
inline void pr(auto name, R const & v,  size_t max = 16u) noexcept {
  auto n = std::size(v);
  auto m = (n > max) ? max: v.size();
  auto vd = v.data();
  std::cout << name << " = (";
  for(size_t i=0; i < m ; ++i) std::cout << +eve::read(vd, i) << " ";
  if (n > max+1) std::cout << "... " << +eve::read(vd, n-1);
  else if (n > max) std::cout << eve::read(vd, n-1);
  std::cout << ")\n";
};

template<typename U>
inline void pr(auto name,  U* vd,  auto nn, size_t max = 16u) noexcept {
  size_t n(nn);
  auto m = (n > max) ? max: n;
  std::cout << name << " = (" << std::setprecision(17);

  for(size_t i=0; i < m ; ++i) std::cout << +vd[i] << " ";
if (n > max+1) std::cout << "... " << +vd[n-1];
  else if (n > max) std::cout << +vd[n-1];
  std::cout << ")\n";
}

template<eve::algo::relaxed_range R>
void print(R const & v) noexcept
{
  auto n = std::size(v);
  auto cur = v.begin();
  if(n)
  {
    for(auto i = 1;  i !=  n; ++i, ++cur) {std::cout << +eve::read(cur) << " ";};
    if (n) std::cout << +eve::read(cur) << "\n";
  }
}
