//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/pointer.hpp>

namespace eve::detail
{
  template <typename Ptr>
  EVE_FORCEINLINE auto arm_ptr_downcast(Ptr ptr) noexcept
  {
#ifdef SPY_SUPPORTS_FP16_TYPE
    if constexpr (std::same_as<std::remove_cvref_t<std::remove_pointer_t<Ptr>>, eve::float16_t>)
      return reinterpret_cast<copy_qualifiers_t<__fp16, Ptr>*>(ptr);
    else
      return ptr;
#else
    return ptr;
#endif
  }
}
