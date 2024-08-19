//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
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

  enum class bit_tern : std::uint8_t
  {
  False                                                             =  0x00 // 0
   , LPLPa_or_LPb_or_cRPRP_xor_1RP                                     =  0x01 // ((a or (b or c)) xor 1)
   , LPLPb_or_aRP_notand_cRP                                           =  0x02 // ((b or a) notand c)
   , LPLPb_or_aRP_xor_1RP                                              =  0x03 // ((b or a) xor 1)
   , LPLPa_or_cRP_notand_bRP                                           =  0x04 // ((a or c) notand b)
   , LPLPc_or_aRP_xor_1RP                                              =  0x05 // ((c or a) xor 1)
   , LPa_notand_LPb_xor_cRPRP                                          =  0x06 // (a notand (b xor c))
   , LPLPa_or_LPb_and_cRPRP_xor_1RP                                    =  0x07 // ((a or (b and c)) xor 1)
   , LPLPa_notand_bRP_and_cRP                                          =  0x08 // ((a notand b) and c)
   , LPLPa_or_LPb_xor_cRPRP_xor_1RP                                    =  0x09 // ((a or (b xor c)) xor 1)
   , LPa_notand_cRP                                                    =  0x0a // (a notand c)
   , LPa_notand_LPLPb_xor_1RP_or_cRPRP                                 =  0x0b // (a notand ((b xor 1) or c))
   , LPa_notand_bRP                                                    =  0x0c // (a notand b)
   , LPa_notand_LPb_or_LPc_xor_1RPRPRP                                 =  0x0d // (a notand (b or (c xor 1)))
   , LPa_notand_LPb_or_cRPRP                                           =  0x0e // (a notand (b or c))
   , LPa_xor_1RP                                                       =  0x0f // (a xor 1)
   , LPLPb_or_cRP_notand_aRP                                           =  0x10 // ((b or c) notand a)
   , LPLPc_or_bRP_xor_1RP                                              =  0x11 // ((c or b) xor 1)
   , LPb_notand_LPa_xor_cRPRP                                          =  0x12 // (b notand (a xor c))
   , LPLPb_or_LPa_and_cRPRP_xor_1RP                                    =  0x13 // ((b or (a and c)) xor 1)
   , LPc_notand_LPa_xor_bRPRP                                          =  0x14 // (c notand (a xor b))
   , LPLPc_or_LPb_and_aRPRP_xor_1RP                                    =  0x15 // ((c or (b and a)) xor 1)
   , LPLPLPb_or_cRP_notand_aRP_or_LPa_notand_LPb_xor_cRPRPRP           =  0x16 // (((b or c) notand a) or (a notand (b xor c)))
   , LPLPLPb_or_cRP_xor_1RP_or_LPa_notand_LPb_xor_cRPRPRP              =  0x17 // (((b or c) xor 1) or (a notand (b xor c)))
   , LPLPa_xor_bRP_and_LPa_xor_cRPRP                                   =  0x18 // ((a xor b) and (a xor c))
   , LPLPa_and_bRP_notand_LPb_xor_LPc_xor_1RPRPRP                      =  0x19 // ((a and b) notand (b xor (c xor 1)))
   , LPLPa_and_bRP_notand_LPa_xor_cRPRP                                =  0x1a // ((a and b) notand (a xor c))
   , LPLPa_notand_cRP_or_LPc_notand_LPb_xor_1RPRPRP                    =  0x1b // ((a notand c) or (c notand (b xor 1)))
   , LPLPa_and_cRP_notand_LPa_xor_bRPRP                                =  0x1c // ((a and c) notand (a xor b))
   , LPLPa_notand_bRP_or_LPb_notand_LPc_xor_1RPRPRP                    =  0x1d // ((a notand b) or (b notand (c xor 1)))
   , LPa_xor_LPb_or_cRPRP                                              =  0x1e // (a xor (b or c))
   , LPLPa_and_LPb_or_cRPRP_xor_1RP                                    =  0x1f // ((a and (b or c)) xor 1)
   , LPLPb_notand_aRP_and_cRP                                          =  0x20 // ((b notand a) and c)
   , LPLPb_or_LPa_xor_cRPRP_xor_1RP                                    =  0x21 // ((b or (a xor c)) xor 1)
   , LPb_notand_cRP                                                    =  0x22 // (b notand c)
   , LPb_notand_LPLPa_xor_1RP_or_cRPRP                                 =  0x23 // (b notand ((a xor 1) or c))
   , LPLPa_xor_bRP_and_LPb_xor_cRPRP                                   =  0x24 // ((a xor b) and (b xor c))
   , LPLPa_and_bRP_notand_LPa_xor_LPc_xor_1RPRPRP                      =  0x25 // ((a and b) notand (a xor (c xor 1)))
   , LPLPa_and_bRP_notand_LPb_xor_cRPRP                                =  0x26 // ((a and b) notand (b xor c))
   , LPLPb_notand_cRP_or_LPc_notand_LPa_xor_1RPRPRP                    =  0x27 // ((b notand c) or (c notand (a xor 1)))
   , LPc_and_LPb_xor_aRPRP                                             =  0x28 // (c and (b xor a))
   , LPLPc_and_LPb_xor_aRPRP_or_LPc_notand_LPLPb_or_aRP_xor_1RPRPRP    =  0x29 // ((c and (b xor a)) or (c notand ((b or a) xor 1)))
   , LPLPb_and_aRP_notand_cRP                                          =  0x2a // ((b and a) notand c)
   , LPLPLPb_and_aRP_notand_cRP_or_LPc_notand_LPLPb_or_aRP_xor_1RPRPRP =  0x2b // (((b and a) notand c) or (c notand ((b or a) xor 1)))
   , LPLPb_or_cRP_and_LPa_xor_bRPRP                                    =  0x2c // ((b or c) and (a xor b))
   , LPa_xor_LPb_or_LPc_xor_1RPRPRP                                    =  0x2d // (a xor (b or (c xor 1)))
   , LPLPb_or_cRP_xor_LPa_and_bRPRP                                    =  0x2e // ((b or c) xor (a and b))
   , LPLPb_notand_cRP_or_LPa_xor_1RPRP                                 =  0x2f // ((b notand c) or (a xor 1))
   , LPb_notand_aRP                                                    =  0x30 // (b notand a)
   , LPb_notand_LPa_or_LPc_xor_1RPRPRP                                 =  0x31 // (b notand (a or (c xor 1)))
   , LPb_notand_LPa_or_cRPRP                                           =  0x32 // (b notand (a or c))
   , LPb_xor_1RP                                                       =  0x33 // (b xor 1)
   , LPLPb_and_cRP_notand_LPa_xor_bRPRP                                =  0x34 // ((b and c) notand (a xor b))
   , LPLPb_notand_aRP_or_LPa_notand_LPc_xor_1RPRPRP                    =  0x35 // ((b notand a) or (a notand (c xor 1)))
   , LPb_xor_LPa_or_cRPRP                                              =  0x36 // (b xor (a or c))
   , LPLPb_and_LPa_or_cRPRP_xor_1RP                                    =  0x37 // ((b and (a or c)) xor 1)
   , LPLPa_or_cRP_and_LPa_xor_bRPRP                                    =  0x38 // ((a or c) and (a xor b))
   , LPb_xor_LPa_or_LPc_xor_1RPRPRP                                    =  0x39 // (b xor (a or (c xor 1)))
   , LPLPb_notand_aRP_or_LPa_notand_cRPRP                              =  0x3a // ((b notand a) or (a notand c))
   , LPLPa_notand_cRP_or_LPb_xor_1RPRP                                 =  0x3b // ((a notand c) or (b xor 1))
   , LPb_xor_aRP                                                       =  0x3c // (b xor a)
   , LPLPa_xor_bRP_or_LPLPa_or_cRP_xor_1RPRP                           =  0x3d // ((a xor b) or ((a or c) xor 1))
   , LPLPa_notand_cRP_or_LPa_xor_bRPRP                                 =  0x3e // ((a notand c) or (a xor b))
   , LPLPb_and_aRP_xor_1RP                                             =  0x3f // ((b and a) xor 1)
   , LPLPc_notand_aRP_and_bRP                                          =  0x40 // ((c notand a) and b)
   , LPLPc_or_LPb_xor_aRPRP_xor_1RP                                    =  0x41 // ((c or (b xor a)) xor 1)
   , LPLPa_xor_cRP_and_LPb_xor_cRPRP                                   =  0x42 // ((a xor c) and (b xor c))
   , LPLPa_and_cRP_notand_LPa_xor_LPb_xor_1RPRPRP                      =  0x43 // ((a and c) notand (a xor (b xor 1)))
   , LPc_notand_bRP                                                    =  0x44 // (c notand b)
   , LPc_notand_LPLPa_xor_1RP_or_bRPRP                                 =  0x45 // (c notand ((a xor 1) or b))
   , LPLPa_and_cRP_notand_LPb_xor_cRPRP                                =  0x46 // ((a and c) notand (b xor c))
   , LPLPc_notand_bRP_or_LPb_notand_LPa_xor_1RPRPRP                    =  0x47 // ((c notand b) or (b notand (a xor 1)))
   , LPb_and_LPa_xor_cRPRP                                             =  0x48 // (b and (a xor c))
   , LPLPb_and_LPa_xor_cRPRP_or_LPb_notand_LPLPa_or_cRP_xor_1RPRPRP    =  0x49 // ((b and (a xor c)) or (b notand ((a or c) xor 1)))
   , LPLPb_or_cRP_and_LPa_xor_cRPRP                                    =  0x4a // ((b or c) and (a xor c))
   , LPa_xor_LPLPb_xor_1RP_or_cRPRP                                    =  0x4b // (a xor ((b xor 1) or c))
   , LPLPa_and_cRP_notand_bRP                                          =  0x4c // ((a and c) notand b)
   , LPLPLPa_and_cRP_notand_bRP_or_LPb_notand_LPLPa_or_cRP_xor_1RPRPRP =  0x4d // (((a and c) notand b) or (b notand ((a or c) xor 1)))
   , LPLPa_notand_cRP_or_LPc_notand_bRPRP                              =  0x4e // ((a notand c) or (c notand b))
   , LPLPc_notand_bRP_or_LPa_xor_1RPRP                                 =  0x4f // ((c notand b) or (a xor 1))
   , LPc_notand_aRP                                                    =  0x50 // (c notand a)
   , LPc_notand_LPa_or_LPb_xor_1RPRPRP                                 =  0x51 // (c notand (a or (b xor 1)))
   , LPLPb_and_cRP_notand_LPa_xor_cRPRP                                =  0x52 // ((b and c) notand (a xor c))
   , LPLPc_notand_aRP_or_LPa_notand_LPb_xor_1RPRPRP                    =  0x53 // ((c notand a) or (a notand (b xor 1)))
   , LPc_notand_LPa_or_bRPRP                                           =  0x54 // (c notand (a or b))
   , LPc_xor_1RP                                                       =  0x55 // (c xor 1)
   , LPc_xor_LPb_or_aRPRP                                              =  0x56 // (c xor (b or a))
   , LPLPc_and_LPb_or_aRPRP_xor_1RP                                    =  0x57 // ((c and (b or a)) xor 1)
   , LPLPa_or_bRP_and_LPa_xor_cRPRP                                    =  0x58 // ((a or b) and (a xor c))
   , LPc_xor_LPa_or_LPb_xor_1RPRPRP                                    =  0x59 // (c xor (a or (b xor 1)))
   , LPc_xor_aRP                                                       =  0x5a // (c xor a)
   , LPLPa_xor_cRP_or_LPLPa_or_bRP_xor_1RPRP                           =  0x5b // ((a xor c) or ((a or b) xor 1))
   , LPLPc_notand_aRP_or_LPa_notand_bRPRP                              =  0x5c // ((c notand a) or (a notand b))
   , LPLPa_notand_bRP_or_LPc_xor_1RPRP                                 =  0x5d // ((a notand b) or (c xor 1))
   , LPLPc_notand_bRP_or_LPa_xor_cRPRP                                 =  0x5e // ((c notand b) or (a xor c))
   , LPLPc_and_aRP_xor_1RP                                             =  0x5f // ((c and a) xor 1)
   , LPa_and_LPb_xor_cRPRP                                             =  0x60 // (a and (b xor c))
   , LPLPa_and_LPb_xor_cRPRP_or_LPa_notand_LPLPb_or_cRP_xor_1RPRPRP    =  0x61 // ((a and (b xor c)) or (a notand ((b or c) xor 1)))
   , LPLPa_or_cRP_and_LPb_xor_cRPRP                                    =  0x62 // ((a or c) and (b xor c))
   , LPb_xor_LPLPa_xor_1RP_or_cRPRP                                    =  0x63 // (b xor ((a xor 1) or c))
   , LPLPa_or_bRP_and_LPb_xor_cRPRP                                    =  0x64 // ((a or b) and (b xor c))
   , LPc_xor_LPLPa_xor_1RP_or_bRPRP                                    =  0x65 // (c xor ((a xor 1) or b))
   , LPc_xor_bRP                                                       =  0x66 // (c xor b)
   , LPLPb_xor_cRP_or_LPLPa_or_bRP_xor_1RPRP                           =  0x67 // ((b xor c) or ((a or b) xor 1))
   , LPLPa_and_LPb_xor_cRPRP_or_LPa_notand_LPb_and_cRPRPRP             =  0x68 // ((a and (b xor c)) or (a notand (b and c)))
   , LPLPa_xor_LPb_xor_cRPRP_xor_1RP                                   =  0x69 // ((a xor (b xor c)) xor 1)
   , LPc_xor_LPb_and_aRPRP                                             =  0x6a // (c xor (b and a))
   , LPLPa_notand_cRP_or_LPLPa_xor_1RP_xor_LPb_xor_cRPRPRP             =  0x6b // ((a notand c) or ((a xor 1) xor (b xor c)))
   , LPb_xor_LPa_and_cRPRP                                             =  0x6c // (b xor (a and c))
   , LPLPa_notand_bRP_or_LPLPa_xor_1RP_xor_LPb_xor_cRPRPRP             =  0x6d // ((a notand b) or ((a xor 1) xor (b xor c)))
   , LPLPa_notand_bRP_or_LPb_xor_cRPRP                                 =  0x6e // ((a notand b) or (b xor c))
   , LPLPb_xor_cRP_or_LPa_xor_1RPRP                                    =  0x6f // ((b xor c) or (a xor 1))
   , LPLPb_and_cRP_notand_aRP                                          =  0x70 // ((b and c) notand a)
   , LPLPLPb_or_cRP_xor_1RP_or_LPa_and_LPb_xor_cRPRPRP                 =  0x71 // (((b or c) xor 1) or (a and (b xor c)))
   , LPLPb_notand_cRP_or_LPc_notand_aRPRP                              =  0x72 // ((b notand c) or (c notand a))
   , LPLPc_notand_aRP_or_LPb_xor_1RPRP                                 =  0x73 // ((c notand a) or (b xor 1))
   , LPLPc_notand_bRP_or_LPb_notand_aRPRP                              =  0x74 // ((c notand b) or (b notand a))
   , LPLPb_notand_aRP_or_LPc_xor_1RPRP                                 =  0x75 // ((b notand a) or (c xor 1))
   , LPLPb_notand_aRP_or_LPb_xor_cRPRP                                 =  0x76 // ((b notand a) or (b xor c))
   , LPLPc_and_bRP_xor_1RP                                             =  0x77 // ((c and b) xor 1)
   , LPa_xor_LPb_and_cRPRP                                             =  0x78 // (a xor (b and c))
   , LPLPb_notand_aRP_or_LPLPb_xor_1RP_xor_LPa_xor_cRPRPRP             =  0x79 // ((b notand a) or ((b xor 1) xor (a xor c)))
   , LPLPb_notand_aRP_or_LPa_xor_cRPRP                                 =  0x7a // ((b notand a) or (a xor c))
   , LPLPa_xor_cRP_or_LPb_xor_1RPRP                                    =  0x7b // ((a xor c) or (b xor 1))
   , LPLPc_notand_aRP_or_LPa_xor_bRPRP                                 =  0x7c // ((c notand a) or (a xor b))
   , LPLPa_xor_bRP_or_LPc_xor_1RPRP                                    =  0x7d // ((a xor b) or (c xor 1))
   , LPLPa_xor_bRP_or_LPa_xor_cRPRP                                    =  0x7e // ((a xor b) or (a xor c))
   , LPLPLPa_and_bRP_and_cRP_xor_1RP                                   =  0x7f // (((a and b) and c) xor 1)
   , LPa_and_LPb_and_cRPRP                                             =  0x80 // (a and (b and c))
   , LPLPa_xor_cRP_notand_LPa_xor_LPb_xor_1RPRPRP                      =  0x81 // ((a xor c) notand (a xor (b xor 1)))
   , LPLPb_xor_aRP_notand_cRP                                          =  0x82 // ((b xor a) notand c)
   , LPLPa_xor_bRP_notand_LPLPa_xor_1RP_or_cRPRP                       =  0x83 // ((a xor b) notand ((a xor 1) or c))
   , LPLPa_xor_cRP_notand_bRP                                          =  0x84 // ((a xor c) notand b)
   , LPLPa_xor_cRP_notand_LPb_or_LPc_xor_1RPRPRP                       =  0x85 // ((a xor c) notand (b or (c xor 1)))
   , LPLPb_or_cRP_and_LPc_xor_LPa_xor_bRPRPRP                          =  0x86 // ((b or c) and (c xor (a xor b)))
   , LPLPa_xor_LPb_and_cRPRP_xor_1RP                                   =  0x87 // ((a xor (b and c)) xor 1)
   , LPc_and_bRP                                                       =  0x88 // (c and b)
   , LPLPb_xor_cRP_notand_LPLPa_xor_1RP_or_bRPRP                       =  0x89 // ((b xor c) notand ((a xor 1) or b))
   , LPLPb_notand_aRP_notand_cRP                                       =  0x8a // ((b notand a) notand c)
   , LPLPb_and_cRP_or_LPb_notand_LPa_xor_1RPRPRP                       =  0x8b // ((b and c) or (b notand (a xor 1)))
   , LPLPc_notand_aRP_notand_bRP                                       =  0x8c // ((c notand a) notand b)
   , LPLPc_and_bRP_or_LPc_notand_LPa_xor_1RPRPRP                       =  0x8d // ((c and b) or (c notand (a xor 1)))
   , LPLPb_and_cRP_or_LPa_notand_LPb_xor_cRPRPRP                       =  0x8e // ((b and c) or (a notand (b xor c)))
   , LPLPb_and_cRP_or_LPa_xor_1RPRP                                    =  0x8f // ((b and c) or (a xor 1))
   , LPLPb_xor_cRP_notand_aRP                                          =  0x90 // ((b xor c) notand a)
   , LPLPb_xor_cRP_notand_LPa_or_LPb_xor_1RPRPRP                       =  0x91 // ((b xor c) notand (a or (b xor 1)))
   , LPLPa_or_cRP_and_LPc_xor_LPa_xor_bRPRPRP                          =  0x92 // ((a or c) and (c xor (a xor b)))
   , LPLPb_xor_LPa_and_cRPRP_xor_1RP                                   =  0x93 // ((b xor (a and c)) xor 1)
   , LPLPa_or_bRP_and_LPb_xor_LPa_xor_cRPRPRP                          =  0x94 // ((a or b) and (b xor (a xor c)))
   , LPLPc_xor_LPb_and_aRPRP_xor_1RP                                   =  0x95 // ((c xor (b and a)) xor 1)
   , LPa_xor_LPb_xor_cRPRP                                             =  0x96 // (a xor (b xor c))
   , LPLPLPb_xor_cRP_notand_aRP_or_LPa_notand_LPLPb_and_cRP_xor_1RPRPRP =  0x97 // (((b xor c) notand a) or (a notand ((b and c) xor 1)))
   , LPLPb_xor_cRP_notand_LPa_or_bRPRP                                 =  0x98 // ((b xor c) notand (a or b))
   , LPLPc_xor_bRP_xor_1RP                                             =  0x99 // ((c xor b) xor 1)
   , LPLPb_notand_aRP_xor_cRP                                          =  0x9a // ((b notand a) xor c)
   , LPLPa_notand_cRP_or_LPb_xor_LPc_xor_1RPRPRP                       =  0x9b // ((a notand c) or (b xor (c xor 1)))
   , LPLPc_notand_aRP_xor_bRP                                          =  0x9c // ((c notand a) xor b)
   , LPLPa_notand_bRP_or_LPb_xor_LPc_xor_1RPRPRP                       =  0x9d // ((a notand b) or (b xor (c xor 1)))
   , LPLPb_and_cRP_or_LPc_xor_LPa_xor_bRPRPRP                          =  0x9e // ((b and c) or (c xor (a xor b)))
   , LPLPa_and_LPb_xor_cRPRP_xor_1RP                                   =  0x9f // ((a and (b xor c)) xor 1)
   , LPc_and_aRP                                                       =  0xa0 // (c and a)
   , LPLPa_xor_cRP_notand_LPa_or_LPb_xor_1RPRPRP                       =  0xa1 // ((a xor c) notand (a or (b xor 1)))
   , LPLPa_notand_bRP_notand_cRP                                       =  0xa2 // ((a notand b) notand c)
   , LPLPa_and_cRP_or_LPa_notand_LPb_xor_1RPRPRP                       =  0xa3 // ((a and c) or (a notand (b xor 1)))
   , LPLPa_xor_cRP_notand_LPa_or_bRPRP                                 =  0xa4 // ((a xor c) notand (a or b))
   , LPLPc_xor_aRP_xor_1RP                                             =  0xa5 // ((c xor a) xor 1)
   , LPLPa_notand_bRP_xor_cRP                                          =  0xa6 // ((a notand b) xor c)
   , LPLPb_notand_cRP_or_LPa_xor_LPc_xor_1RPRPRP                       =  0xa7 // ((b notand c) or (a xor (c xor 1)))
   , LPc_and_LPa_or_bRPRP                                              =  0xa8 // (c and (a or b))
   , LPLPc_xor_LPb_or_aRPRP_xor_1RP                                    =  0xa9 // ((c xor (b or a)) xor 1)
   , C                                                                 =  0xaa // c
   , LPc_or_LPLPb_or_aRP_xor_1RPRP                                     =  0xab // (c or ((b or a) xor 1))
   , LPLPa_and_cRP_or_LPa_notand_bRPRP                                 =  0xac // ((a and c) or (a notand b))
   , LPLPb_and_cRP_or_LPa_xor_LPc_xor_1RPRPRP                          =  0xad // ((b and c) or (a xor (c xor 1)))
   , LPLPa_notand_bRP_or_cRP                                           =  0xae // ((a notand b) or c)
   , LPc_or_LPa_xor_1RPRP                                              =  0xaf // (c or (a xor 1))
   , LPLPc_notand_bRP_notand_aRP                                       =  0xb0 // ((c notand b) notand a)
   , LPLPc_and_aRP_or_LPc_notand_LPb_xor_1RPRPRP                       =  0xb1 // ((c and a) or (c notand (b xor 1)))
   , LPLPb_and_LPa_and_cRPRP_or_LPb_notand_LPa_or_cRPRPRP              =  0xb2 // ((b and (a and c)) or (b notand (a or c)))
   , LPLPa_and_cRP_or_LPb_xor_1RPRP                                    =  0xb3 // ((a and c) or (b xor 1))
   , LPLPc_notand_bRP_xor_aRP                                          =  0xb4 // ((c notand b) xor a)
   , LPLPb_notand_aRP_or_LPa_xor_LPc_xor_1RPRPRP                       =  0xb5 // ((b notand a) or (a xor (c xor 1)))
   , LPLPa_and_cRP_or_LPc_xor_LPa_xor_bRPRPRP                          =  0xb6 // ((a and c) or (c xor (a xor b)))
   , LPLPb_and_LPa_xor_cRPRP_xor_1RP                                   =  0xb7 // ((b and (a xor c)) xor 1)
   , LPLPb_and_cRP_or_LPb_notand_aRPRP                                 =  0xb8 // ((b and c) or (b notand a))
   , LPLPa_and_cRP_or_LPb_xor_LPc_xor_1RPRPRP                          =  0xb9 // ((a and c) or (b xor (c xor 1)))
   , LPLPb_notand_aRP_or_cRP                                           =  0xba // ((b notand a) or c)
   , LPc_or_LPb_xor_1RPRP                                              =  0xbb // (c or (b xor 1))
   , LPLPa_and_cRP_or_LPa_xor_bRPRP                                    =  0xbc // ((a and c) or (a xor b))
   , LPLPa_xor_bRP_or_LPa_xor_LPc_xor_1RPRPRP                          =  0xbd // ((a xor b) or (a xor (c xor 1)))
   , LPc_or_LPb_xor_aRPRP                                              =  0xbe // (c or (b xor a))
   , LPc_or_LPLPb_and_aRP_xor_1RPRP                                    =  0xbf // (c or ((b and a) xor 1))
   , LPb_and_aRP                                                       =  0xc0 // (b and a)
   , LPLPa_xor_bRP_notand_LPa_or_LPc_xor_1RPRPRP                       =  0xc1 // ((a xor b) notand (a or (c xor 1)))
   , LPLPa_xor_bRP_notand_LPa_or_cRPRP                                 =  0xc2 // ((a xor b) notand (a or c))
   , LPLPb_xor_aRP_xor_1RP                                             =  0xc3 // ((b xor a) xor 1)
   , LPLPa_notand_cRP_notand_bRP                                       =  0xc4 // ((a notand c) notand b)
   , LPLPa_and_bRP_or_LPa_notand_LPc_xor_1RPRPRP                       =  0xc5 // ((a and b) or (a notand (c xor 1)))
   , LPLPa_notand_cRP_xor_bRP                                          =  0xc6 // ((a notand c) xor b)
   , LPLPc_notand_bRP_or_LPa_xor_LPb_xor_1RPRPRP                       =  0xc7 // ((c notand b) or (a xor (b xor 1)))
   , LPb_and_LPa_or_cRPRP                                              =  0xc8 // (b and (a or c))
   , LPLPb_xor_LPa_or_cRPRP_xor_1RP                                    =  0xc9 // ((b xor (a or c)) xor 1)
   , LPLPa_and_bRP_or_LPa_notand_cRPRP                                 =  0xca // ((a and b) or (a notand c))
   , LPLPb_and_cRP_or_LPa_xor_LPb_xor_1RPRPRP                          =  0xcb // ((b and c) or (a xor (b xor 1)))
   , B                                                                 =  0xcc // b
   , LPb_or_LPLPa_or_cRP_xor_1RPRP                                     =  0xcd // (b or ((a or c) xor 1))
   , LPLPa_notand_cRP_or_bRP                                           =  0xce // ((a notand c) or b)
   , LPb_or_LPa_xor_1RPRP                                              =  0xcf // (b or (a xor 1))
   , LPLPb_notand_cRP_notand_aRP                                       =  0xd0 // ((b notand c) notand a)
   , LPLPLPb_or_cRP_xor_1RP_or_LPa_and_bRPRP                           =  0xd1 // (((b or c) xor 1) or (a and b))
   , LPLPb_notand_cRP_xor_aRP                                          =  0xd2 // ((b notand c) xor a)
   , LPLPc_notand_aRP_or_LPa_xor_LPb_xor_1RPRPRP                       =  0xd3 // ((c notand a) or (a xor (b xor 1)))
   , LPLPc_notand_bRP_or_LPLPb_xor_cRP_notand_aRPRP                    =  0xd4 // ((c notand b) or ((b xor c) notand a))
   , LPLPa_and_bRP_or_LPc_xor_1RPRP                                    =  0xd5 // ((a and b) or (c xor 1))
   , LPLPa_and_bRP_or_LPb_xor_LPa_xor_cRPRPRP                          =  0xd6 // ((a and b) or (b xor (a xor c)))
   , LPLPc_and_LPb_xor_aRPRP_xor_1RP                                   =  0xd7 // ((c and (b xor a)) xor 1)
   , LPLPc_and_bRP_or_LPc_notand_aRPRP                                 =  0xd8 // ((c and b) or (c notand a))
   , LPLPa_and_bRP_or_LPb_xor_LPc_xor_1RPRPRP                          =  0xd9 // ((a and b) or (b xor (c xor 1)))
   , LPLPa_and_bRP_or_LPa_xor_cRPRP                                    =  0xda // ((a and b) or (a xor c))
   , LPLPa_xor_cRP_or_LPa_xor_LPb_xor_1RPRPRP                          =  0xdb // ((a xor c) or (a xor (b xor 1)))
   , LPLPc_notand_aRP_or_bRP                                           =  0xdc // ((c notand a) or b)
   , LPb_or_LPc_xor_1RPRP                                              =  0xdd // (b or (c xor 1))
   , LPb_or_LPa_xor_cRPRP                                              =  0xde // (b or (a xor c))
   , LPb_or_LPLPa_and_cRP_xor_1RPRP                                    =  0xdf // (b or ((a and c) xor 1))
   , LPa_and_LPb_or_cRPRP                                              =  0xe0 // (a and (b or c))
   , LPLPa_xor_LPb_or_cRPRP_xor_1RP                                    =  0xe1 // ((a xor (b or c)) xor 1)
   , LPLPb_and_aRP_or_LPb_notand_cRPRP                                 =  0xe2 // ((b and a) or (b notand c))
   , LPLPa_and_cRP_or_LPa_xor_LPb_xor_1RPRPRP                          =  0xe3 // ((a and c) or (a xor (b xor 1)))
   , LPLPc_and_aRP_or_LPc_notand_bRPRP                                 =  0xe4 // ((c and a) or (c notand b))
   , LPLPa_and_bRP_or_LPa_xor_LPc_xor_1RPRPRP                          =  0xe5 // ((a and b) or (a xor (c xor 1)))
   , LPLPa_and_bRP_or_LPb_xor_cRPRP                                    =  0xe6 // ((a and b) or (b xor c))
   , LPLPb_xor_cRP_or_LPa_xor_LPb_xor_1RPRPRP                          =  0xe7 // ((b xor c) or (a xor (b xor 1)))
   , LPLPb_and_cRP_or_LPa_and_LPb_xor_cRPRPRP                          =  0xe8 // ((b and c) or (a and (b xor c)))
   , LPLPa_and_bRP_or_LPb_xor_LPa_xor_LPc_xor_1RPRPRPRP                =  0xe9 // ((a and b) or (b xor (a xor (c xor 1))))
   , LPc_or_LPb_and_aRPRP                                              =  0xea // (c or (b and a))
   , LPc_or_LPLPb_xor_aRP_xor_1RPRP                                    =  0xeb // (c or ((b xor a) xor 1))
   , LPb_or_LPa_and_cRPRP                                              =  0xec // (b or (a and c))
   , LPb_or_LPLPa_xor_cRP_xor_1RPRP                                    =  0xed // (b or ((a xor c) xor 1))
   , LPc_or_bRP                                                        =  0xee // (c or b)
   , LPb_or_LPLPa_xor_1RP_or_cRPRP                                     =  0xef // (b or ((a xor 1) or c))
   , A                                                                 =  0xf0 //  a
   , LPa_or_LPLPb_or_cRP_xor_1RPRP                                     =  0xf1 // (a or ((b or c) xor 1))
   , LPLPb_notand_cRP_or_aRP                                           =  0xf2 // ((b notand c) or a)
   , LPa_or_LPb_xor_1RPRP                                              =  0xf3 // (a or (b xor 1))
   , LPLPc_notand_bRP_or_aRP                                           =  0xf4 // ((c notand b) or a)
   , LPa_or_LPc_xor_1RPRP                                              =  0xf5 // (a or (c xor 1))
   , LPa_or_LPb_xor_cRPRP                                              =  0xf6 // (a or (b xor c))
   , LPa_or_LPLPb_and_cRP_xor_1RPRP                                    =  0xf7 // (a or ((b and c) xor 1))
   , LPa_or_LPb_and_cRPRP                                              =  0xf8 // (a or (b and c))
   , LPa_or_LPLPb_xor_cRP_xor_1RPRP                                    =  0xf9 // (a or ((b xor c) xor 1))
   , LPc_or_aRP                                                        =  0xfa // (c or a)
   , LPa_or_LPLPb_xor_1RP_or_cRPRP                                     =  0xfb // (a or ((b xor 1) or c))
   , LPb_or_aRP                                                        =  0xfc // (b or a)
   , LPa_or_LPb_or_LPc_xor_1RPRPRP                                     =  0xfd // (a or (b or (c xor 1)))
   , LPa_or_LPb_or_cRPRP                                               =  0xfe // (a or (b or c))
   , TRUE                                                              =  0xff // 1
   };

  EVE_FORCEINLINE constexpr std::int32_t to_integer(bit_tern a) noexcept
  {
    return static_cast<std::int32_t>(a);
  }

}
