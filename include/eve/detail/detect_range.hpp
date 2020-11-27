//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

#include <eve/function/average.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/next.hpp>

namespace eve::detail
{

template <typename T, typename F> void detect_max(F func)
{
  using v_t =  eve::element_type_t<T>;
  auto vmin = eve::range_max<T>(func)*v_t(0.9);
  auto vmax = eve::range_max<T>(func)*v_t(1.1);
  if (vmin > vmax) std::swap(vmin, vmax);
  if(eve::is_finite(func(vmin)) && !eve::is_finite(func(vmax)))
  {
    while(true)
    {
      auto v =  eve::average(vmax, vmin);
      if (eve::is_finite(func(v))) vmin = v;  else vmax = v;
//         std::cout << "vmax " << vmax <<  std::endl;
//         std::cout << "vmin " << vmin <<  std::endl;
//         std::cout << "vmin > vmax   " << (vmin > vmax) <<  std::endl;
      if(vmax <=  eve::next(vmin))
      {
        std::cout << "n " << std::hexfloat << eve::next(v) << " -> " << func(eve::next(v)) << " -> " << std::defaultfloat << std::setprecision(16) << eve::next(v) << std::endl;
        std::cout << "v " << std::hexfloat << v << " -> " << func(v) <<                       " -> " << std::defaultfloat << std::setprecision(16) << v << std::endl;
        std::cout << "p " << std::hexfloat << eve::prev(v) << " -> " << func(eve::prev(v)) << " -> " << std::defaultfloat << std::setprecision(16) << eve::prev(v) << std::endl;
        break;
      }
    }
  }
  else
    std::cout << "zut" << std::endl;
}

template <typename T, typename F> void detect_min(F func)
{
  using v_t =  eve::element_type_t<T>;
  auto vmin = eve::range_min<T>(func)*v_t(2);
  auto vmax = eve::range_min<T>(func)*v_t(0.5);
  if (vmin > vmax) std::swap(vmin, vmax);
  if (func(vmin) == 0 && func(vmax) > 0)
  {
    while(true)
    {
      auto v =  eve::average(vmax, vmin);
      if (func(v) == 0) vmin = v;  else vmax = v;
//         std::cout << "vmax " << vmax <<  std::endl;
//         std::cout << "vmin " << vmin <<  std::endl;
//         std::cout << "vmin > vmax   " << (vmin > vmax) <<  std::endl;
      if(vmax <=  eve::next(vmin))
      {
        std::cout << "n " << std::hexfloat << eve::next(v) << " -> " << func(eve::next(v)) << " -> " << std::defaultfloat << std::setprecision(16) << eve::next(v) << std::endl;
        std::cout << "v " << std::hexfloat << v << " -> " << func(v) <<                       " -> " << std::defaultfloat << std::setprecision(16) << v << std::endl;
        std::cout << "p " << std::hexfloat << eve::prev(v) << " -> " << func(eve::prev(v)) << " -> " << std::defaultfloat << std::setprecision(16) << eve::prev(v) << std::endl;
        break;
      }
    }
  }
  else
    std::cout << "zut" << std::endl;
}
