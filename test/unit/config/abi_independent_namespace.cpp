//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/soa_ptr.hpp>

namespace eve
{
  template<typename Type, width_type Lanes>
  requires (!std::same_as<Type, void>)
  struct aligned_ptr;

  template<typename... Ptrs> struct soa_ptr;
}

TTS_CASE("ABI independent types are declared directly in namespace eve")
{
  TTS_TYPE_IS((eve::aligned_ptr<int, 4>::value_type), int);
  TTS_TYPE_IS((eve::soa_ptr<int*, short*>::tuple_type), (kumi::tuple<int*, short*>));
};
