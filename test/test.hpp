//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef TEST_TEST_HPP
#define TEST_TEST_HPP

#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/wide.hpp>
#include <algorithm>

namespace tts::ext
{
  template<typename T, typename N, typename ABI, typename EnableIf>
  struct equal<eve::wide<T, N, ABI>, eve::wide<T, N, ABI>, EnableIf>
  {
    using arg_t = eve::wide<T, N, ABI>;
    inline bool operator()(arg_t const &l, arg_t const &r) const
    {
      return std::equal(l.begin(), l.end(), r.begin());
    }
  };

  template<typename T, typename N, typename ABI, typename EnableIf>
  struct ulpdist<eve::wide<T, N, ABI>, eve::wide<T, N, ABI>, EnableIf>
  {
    inline double operator()(eve::wide<T, N, ABI> const &l, eve::wide<T, N, ABI> const &r) const
    {
      double max_ulp = 0;
      for(auto i = 0; i < l.size(); ++i)
        max_ulp = std::max(max_ulp, tts::ulpdist(T(l[ i ]), T(r[ i ])));

      return max_ulp;
    }
  };
}

#endif
