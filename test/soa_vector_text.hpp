//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/concept/range.hpp>
#include <tts/tts.hpp>

namespace tts
{
  //================================================================================================
  // A soa_vector iterator is a proxy, so TTS's element-by-element rendering does not compile.
  //================================================================================================
  template<typename T> requires(eve::_::range<T> && eve::_::has_indexed_get<T>)
  struct display<T>
  {
    static text render(T const& v)
    {
      text that("{ ");
      for(std::size_t i = 0; i < v.size(); ++i) that += as_text(v.get(i)) + " ";
      return that + "}";
    }
  };
}
