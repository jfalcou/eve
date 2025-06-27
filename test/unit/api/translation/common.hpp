//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/concept/translation.hpp>
#include <eve/traits/as_translation.hpp>

template <typename E>
struct BaseStruct {
  E value;

  auto operator<=>(const BaseStruct&) const = default;
};

template<typename E>
struct eve::translation_of<BaseStruct<E>> { using type = E; };
