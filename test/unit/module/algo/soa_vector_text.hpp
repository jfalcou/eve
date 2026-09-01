//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/module/algo.hpp>

namespace tts
{
  //==================================================================================================
  // TTS renders an unknown range with `for(auto const& v : e)`, which a soa_vector cannot serve:
  // its iterator is a proxy and has no operator*. Read each element through the container instead.
  //
  // A specialization rather than a to_text overload: the trait is keyed on the type, so the hook no
  // longer has to be written in the namespace of its argument to be found.
  //==================================================================================================
  template<typename T, typename A> struct display<eve::algo::soa_vector<T, A>>
  {
    static text render(eve::algo::soa_vector<T, A> const& v)
    {
      text that("{ ");
      for(std::size_t i = 0; i < v.size(); ++i) that += as_text(v.get(i)) + " ";
      return that + "}";
    }
  };
}
