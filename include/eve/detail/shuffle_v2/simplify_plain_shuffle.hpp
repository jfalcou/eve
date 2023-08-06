//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/pattern.hpp>
#include <eve/detail/shuffle_v2/idxm.hpp>
#include <eve/detail/shuffle_v2/shuffle_v2_helpers.hpp>

namespace eve
{

// Part of shuffle_v2 driver that takes a pattern and up to two registers
// and does some canonicalization.
//
// You can read which in shuffle_v2_driver comments.

EVE_REGISTER_CALLABLE(simplify_plain_shuffle_)
EVE_DECLARE_CALLABLE(simplify_plain_shuffle_, simplify_plain_shuffle)

namespace detail
{
  EVE_ALIAS_CALLABLE(simplify_plain_shuffle_, simplify_plain_shuffle);
}

EVE_CALLABLE_API(simplify_plain_shuffle_, simplify_plain_shuffle)

}

#include <eve/detail/shuffle_v2/simd/common/simplify_plain_shuffle.hpp>
