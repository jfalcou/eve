//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <cstdint>
#include <eve/detail/abi.hpp>

namespace eve::detail
{
  // AVX512 FPCLASS intrinsic enum class builder
  enum class fpclass  { qnan    = 1   // quiet nan
                      , poszero = 2   // positive zero
                      , negzero = 4   // negative zero
                      , posinf  = 8   // positive infinity
                      , neginf  = 16  // negative infinity
                      , denorm  = 32  // denormal
                      , neg     = 64  // finite negative
                      , snan    = 128 // signaling nan
                      };

  template<typename I> EVE_FORCEINLINE constexpr std::int32_t operator|(I a,  fpclass b) noexcept
  {
    return static_cast<std::int32_t>(a) | static_cast<std::int32_t>(b);
  }

  enum class range_ctrl { min = 0b00
                        , max = 0b01
                        , absolute_min= 0b10
                        , absolute_max= 0b11
                        , sign_from_first = 0b0000
                        , sign_from_cmp = 0b0100
                        , sign_clear= 0b1000
                        , sign_set= 0b1100
                        };

  EVE_FORCEINLINE constexpr int operator|(range_ctrl a,  range_ctrl b) noexcept
  {
    return static_cast<int>(a) | static_cast<int>(b);
  }


  // X86 Flags for FP comparisons
  enum class cmp_flt
  { eq_oq     = 0x00 // equal (ordered, non-signaling)
  , lt_os     = 0x01 // less-than (ordered, signaling)
  , le_os     = 0x02 // less-than-or-equal (ordered, signaling)
  , unord_q   = 0x03 // unordered (non-signaling)
  , neq_uq    = 0x04 // not-equal (unordered, non-signaling)
  , nlt_us    = 0x05 // not-less-than (unordered, signaling)
  , nle_us    = 0x06 // not-less-than-or-equal (unordered, signaling)
  , ord_q     = 0x07 // ordered (nonsignaling)
  , eq_uq     = 0x08 // equal (unordered, non-signaling)
  , nge_us    = 0x09 // not-greater-than-or-equal (unord, signaling)
  , ngt_us    = 0x0a // not-greater-than (unordered, signaling)
  , false_oq  = 0x0b // false (ordered, non-signaling)
  , neq_oq    = 0x0c // not-equal (ordered, non-signaling)
  , ge_os     = 0x0d // greater-than-or-equal (ordered, signaling)
  , gt_os     = 0x0e // greater-than (ordered, signaling)
  , true_uq   = 0x0f // true (unordered, non-signaling)
  , eq_os     = 0x10 // equal (ordered, signaling)
  , lt_oq     = 0x11 // less-than (ordered, non-signaling)
  , le_oq     = 0x12 // less-than-or-equal (ordered, non-signaling)
  , unord_s   = 0x13 // unordered (signaling)
  , neq_us    = 0x14 // not-equal (unordered, signaling)
  , nlt_uq    = 0x15 // not-less-than (unordered, non-signaling)
  , nle_uq    = 0x16 // not-less-than-or-equal (unord, non-signaling)
  , ord_s     = 0x17 // ordered (signaling)
  , eq_us     = 0x18 // equal (unordered, signaling)
  , nge_uq    = 0x19 // not-greater-than-or-equal (unord, non-sign)
  , ngt_uq    = 0x1a // not-greater-than (unordered, non-signaling)
  , false_os  = 0x1b // false (ordered, signaling)
  , neq_os    = 0x1c // not-equal (ordered, signaling)
  , ge_oq     = 0x1d // greater-than-or-equal (ordered, non-signaling)
  , gt_oq     = 0x1e // greater-than (ordered, non-signaling)
  , true_us   = 0x1f // true (unordered, signaling)
  };

  EVE_FORCEINLINE constexpr std::int32_t to_integer(cmp_flt a) noexcept
  {
    return static_cast<std::int32_t>(a);
  }
}
