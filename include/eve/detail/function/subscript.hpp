//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>

namespace eve::detail
{
  template<typename Options>
  struct insert_t : callable<insert_t, Options>
  {
    template<typename Wide, typename Val>
    EVE_FORCEINLINE constexpr void operator()(Wide& w, std::size_t idx, Val v) const noexcept
    {
      return this->behavior(as<std::void_t<Wide>>{}, eve::current_api, this->options(), w, idx, v);
    }

    EVE_CALLABLE_OBJECT(insert_t, insert_);
  };

  inline constexpr auto insert = functor<insert_t>;

  template<typename Options>
  struct extract_t : callable<extract_t, Options>
  {
    template<typename Wide>
    EVE_FORCEINLINE constexpr element_type_t<Wide> operator()(Wide w, std::size_t idx) const noexcept
    {
      return this->behavior(as<element_type_t<Wide>>{}, eve::current_api, this->options(), w, idx);
    }

    EVE_CALLABLE_OBJECT(extract_t, extract_);
  };

  inline constexpr auto extract = functor<extract_t>;
}

#include <eve/detail/function/simd/common/subscript.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/subscript.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/detail/function/simd/arm/sve/subscript.hpp>
#endif

#if defined(EVE_INCLUDE_RISCV_HEADER)
#  include <eve/detail/function/simd/riscv/subscript.hpp>
#endif
