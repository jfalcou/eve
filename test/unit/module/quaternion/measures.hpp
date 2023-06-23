//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/quaternion.hpp>

namespace tts
{

//   template<typename T> auto relative_distance(T const &l, T const &r) requires(eve::is_quaternion_v<T>)
//   {
//     auto [rl,il,jl,kl] = l;
//     auto [rr,ir,jr,kr] = r;

//     return eve::max(relative_distance(rl,rr), relative_distance(il,ir), relative_distance(jl,kr), relative_distance(kl,kr));
//   }

//   template<typename T, typename N>
//   auto relative_distance(eve::wide<T,N> const &l, eve::wide<T,N> const &r) requires(eve::is_quaternion_v<T>)
//   {
//     auto [rl,il,jl,kl] = l;
//     auto [rr,ir,jr,kr] = r;

//     return eve::max(relative_distance(rl,rr), relative_distance(il,ir), relative_distance(jl,kr), relative_distance(kl,kr));
//    }

  template<typename T> auto absolute_distance(T const &l, T const &r) requires(eve::is_quaternion_v<T>)
  {
     return eve::maximum(eve::dist(l, r));
  }

  template<typename T, typename N>
  auto absolute_distance(eve::wide<T,N> const &l, eve::wide<T,N> const &r) requires(eve::is_quaternion_v<T>)
  {
     return eve::maximum(eve::dist(l, r));
  }
}
