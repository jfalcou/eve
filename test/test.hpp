//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef TEST_TEST_HPP
#define TEST_TEST_HPP

#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <eve/wide.hpp>
#include <algorithm>

namespace tts::ext
{
  template<typename T, typename N, typename ABI, typename EnableIf>
  struct equal<eve::wide<T,N,ABI>,eve::wide<T,N,ABI>,EnableIf>
  {
    using arg_t = eve::wide<T,N,ABI>;
    inline bool operator()(arg_t const& l, arg_t const& r) const
    {
      return std::equal(l.begin(),l.end(),r.begin());
    }
  };
}

#endif
