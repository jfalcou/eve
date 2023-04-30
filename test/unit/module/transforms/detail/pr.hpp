//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include <iostream>
#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>

template<eve::algo::relaxed_range R>
inline void pr(auto name, R const & v,  auto max = 16u) noexcept {
  auto n = std::size(v);
  auto m = (n > max) ? max: v.size();
  auto vd = v.data();
  std::cout << name << " = (";
  for(size_t i=0; i < m ; ++i) std::cout << +eve::read(vd, i) << " ";
  if (v.size() > max+1) std::cout << "... " << +eve::read(vd, n-1);
  else if (n > max) std::cout << eve::read(vd, n-1);
  std::cout << ")\n";
}

template<typename T>
inline void pr(auto name, R const T* vd,  auto siz n, auto max = 16u) noexcept {
  pr(eve::as_range(vd, vd+n), max);
};

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
