//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/module/algo.hpp>

namespace eve::algo
{
  //================================================================================================
  // TTS renders an unknown range with `for(auto const& v : e)`, which a soa_vector cannot serve:
  // its iterator is a proxy and has no operator*. Read each element through the container instead.
  //
  // Declared here rather than in namespace tts: TTS finds to_text by ADL, so the hook has to live
  // in the namespace of its argument.
  //================================================================================================
  template<typename T, typename A> auto to_text(soa_vector<T,A> const& v)
  {
    ::tts::text that("{ ");
    for(std::size_t i = 0; i < v.size(); ++i) that += ::tts::as_text(v.get(i)) + " ";
    return that + "}";
  }
}
