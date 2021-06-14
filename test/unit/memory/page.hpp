//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/memory/aligned_allocator.hpp>
#include <eve/logical.hpp>
#include <numeric>
#include <vector>

template<typename T, typename N> auto page()
{
  constexpr std::ptrdiff_t algt = eve::alignment_v<eve::wide<T, N>>;
  using alloc_t = eve::aligned_allocator<T, N>;

  auto nb_elem  = 4096/sizeof(T);
  auto start    = nb_elem - std::max(algt,N::value);
  std::vector<T, alloc_t> ref(nb_elem);

  T k = {1};
  for(std::size_t i=start;i<nb_elem;++i) ref[i] = k++;

  return std::pair{ref,start};
}

template<typename T, typename N> auto logical_page()
{
  constexpr std::ptrdiff_t algt = eve::alignment_v<eve::logical<eve::wide<T, N>>>;
  using alloc_t = eve::aligned_allocator<eve::logical<T>, N>;

  auto nb_elem  = 4096/sizeof(T);
  auto start    = nb_elem - std::max(algt,N::value);
  std::vector<eve::logical<T>, alloc_t> ref(nb_elem);

  bool k = true;
  for(std::size_t i=start-1;i<nb_elem;++i) ref[i] = (k = !k);

  return std::pair{ref,start};
}
