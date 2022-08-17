//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/assert.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/abs.hpp>

#include <type_traits>

namespace eve
{
namespace tag
{
  struct rotl_;
}

namespace detail
{
  template<typename T, typename S>
  EVE_FORCEINLINE void
  check(EVE_MATCH_CALL(regular_type, eve::tag::rotl_), T const&, [[maybe_unused]] S const& s)
  {
    constexpr int l [[maybe_unused]] = sizeof(element_type_t<T>) * 8;
    EVE_ASSERT(assert_good_shift<T>(eve::abs(s)),
               "[eve::rotl] Rotating by " << s << " is out of the range ]" << -l << ", " << l
                                          << "[.");
  }

  template<conditional_expr C, typename T, typename S>
  EVE_FORCEINLINE void
  check(EVE_MATCH_CALL(regular_type, eve::tag::rotl_), C const&, T const&,
        [[maybe_unused]] S const& s)
  {
    constexpr int l [[maybe_unused]] = sizeof(element_type_t<T>) * 8;
    EVE_ASSERT(assert_good_shift<T>(eve::abs(s)),
               "[eve::rotl] Rotating by " << s << " is out of the range ]" << -l << ", " << l
                                          << "[.");
  }
}

EVE_MAKE_CALLABLE(rotl_, rotl);
}

#include <eve/module/core/regular/impl/rotl.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/rotl.hpp>
#endif
