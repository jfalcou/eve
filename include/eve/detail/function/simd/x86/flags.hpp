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
  False                                                          =  0x00 // 0
   , $$a_or_$b_or_c$$_xor_1$                                     =  0x01 // ((a or (b or c)) xor 1)
   , $$b_or_a$_notand_c$                                           =  0x02 // ((b or a) notand c)
   , $$b_or_a$_xor_1$                                              =  0x03 // ((b or a) xor 1)
   , $$a_or_c$_notand_b$                                           =  0x04 // ((a or c) notand b)
   , $$c_or_a$_xor_1$                                              =  0x05 // ((c or a) xor 1)
   , $a_notand_$b_xor_c$$                                          =  0x06 // (a notand (b xor c))
   , $$a_or_$b_and_c$$_xor_1$                                    =  0x07 // ((a or (b and c)) xor 1)
   , $$a_notand_b$_and_c$                                          =  0x08 // ((a notand b) and c)
   , $$a_or_$b_xor_c$$_xor_1$                                    =  0x09 // ((a or (b xor c)) xor 1)
   , $a_notand_c$                                                    =  0x0a // (a notand c)
   , $a_notand_$$b_xor_1$_or_c$$                                 =  0x0b // (a notand ((b xor 1) or c))
   , $a_notand_b$                                                    =  0x0c // (a notand b)
   , $a_notand_$b_or_$c_xor_1$$$                                 =  0x0d // (a notand (b or (c xor 1)))
   , $a_notand_$b_or_c$$                                           =  0x0e // (a notand (b or c))
   , $a_xor_1$                                                       =  0x0f // (a xor 1)
   , $$b_or_c$_notand_a$                                           =  0x10 // ((b or c) notand a)
   , $$c_or_b$_xor_1$                                              =  0x11 // ((c or b) xor 1)
   , $b_notand_$a_xor_c$$                                          =  0x12 // (b notand (a xor c))
   , $$b_or_$a_and_c$$_xor_1$                                    =  0x13 // ((b or (a and c)) xor 1)
   , $c_notand_$a_xor_b$$                                          =  0x14 // (c notand (a xor b))
   , $$c_or_$b_and_a$$_xor_1$                                    =  0x15 // ((c or (b and a)) xor 1)
   , $$$b_or_c$_notand_a$_or_$a_notand_$b_xor_c$$$           =  0x16 // (((b or c) notand a) or (a notand (b xor c)))
   , $$$b_or_c$_xor_1$_or_$a_notand_$b_xor_c$$$              =  0x17 // (((b or c) xor 1) or (a notand (b xor c)))
   , $$a_xor_b$_and_$a_xor_c$$                                   =  0x18 // ((a xor b) and (a xor c))
   , $$a_and_b$_notand_$b_xor_$c_xor_1$$$                      =  0x19 // ((a and b) notand (b xor (c xor 1)))
   , $$a_and_b$_notand_$a_xor_c$$                                =  0x1a // ((a and b) notand (a xor c))
   , $$a_notand_c$_or_$c_notand_$b_xor_1$$$                    =  0x1b // ((a notand c) or (c notand (b xor 1)))
   , $$a_and_c$_notand_$a_xor_b$$                                =  0x1c // ((a and c) notand (a xor b))
   , $$a_notand_b$_or_$b_notand_$c_xor_1$$$                    =  0x1d // ((a notand b) or (b notand (c xor 1)))
   , $a_xor_$b_or_c$$                                              =  0x1e // (a xor (b or c))
   , $$a_and_$b_or_c$$_xor_1$                                    =  0x1f // ((a and (b or c)) xor 1)
   , $$b_notand_a$_and_c$                                          =  0x20 // ((b notand a) and c)
   , $$b_or_$a_xor_c$$_xor_1$                                    =  0x21 // ((b or (a xor c)) xor 1)
   , $b_notand_c$                                                    =  0x22 // (b notand c)
   , $b_notand_$$a_xor_1$_or_c$$                                 =  0x23 // (b notand ((a xor 1) or c))
   , $$a_xor_b$_and_$b_xor_c$$                                   =  0x24 // ((a xor b) and (b xor c))
   , $$a_and_b$_notand_$a_xor_$c_xor_1$$$                      =  0x25 // ((a and b) notand (a xor (c xor 1)))
   , $$a_and_b$_notand_$b_xor_c$$                                =  0x26 // ((a and b) notand (b xor c))
   , $$b_notand_c$_or_$c_notand_$a_xor_1$$$                    =  0x27 // ((b notand c) or (c notand (a xor 1)))
   , $c_and_$b_xor_a$$                                             =  0x28 // (c and (b xor a))
   , $$c_and_$b_xor_a$$_or_$c_notand_$$b_or_a$_xor_1$$$    =  0x29 // ((c and (b xor a)) or (c notand ((b or a) xor 1)))
   , $$b_and_a$_notand_c$                                          =  0x2a // ((b and a) notand c)
   , $$$b_and_a$_notand_c$_or_$c_notand_$$b_or_a$_xor_1$$$ =  0x2b // (((b and a) notand c) or (c notand ((b or a) xor 1)))
   , $$b_or_c$_and_$a_xor_b$$                                    =  0x2c // ((b or c) and (a xor b))
   , $a_xor_$b_or_$c_xor_1$$$                                    =  0x2d // (a xor (b or (c xor 1)))
   , $$b_or_c$_xor_$a_and_b$$                                    =  0x2e // ((b or c) xor (a and b))
   , $$b_notand_c$_or_$a_xor_1$$                                 =  0x2f // ((b notand c) or (a xor 1))
   , $b_notand_a$                                                    =  0x30 // (b notand a)
   , $b_notand_$a_or_$c_xor_1$$$                                 =  0x31 // (b notand (a or (c xor 1)))
   , $b_notand_$a_or_c$$                                           =  0x32 // (b notand (a or c))
   , $b_xor_1$                                                       =  0x33 // (b xor 1)
   , $$b_and_c$_notand_$a_xor_b$$                                =  0x34 // ((b and c) notand (a xor b))
   , $$b_notand_a$_or_$a_notand_$c_xor_1$$$                    =  0x35 // ((b notand a) or (a notand (c xor 1)))
   , $b_xor_$a_or_c$$                                              =  0x36 // (b xor (a or c))
   , $$b_and_$a_or_c$$_xor_1$                                    =  0x37 // ((b and (a or c)) xor 1)
   , $$a_or_c$_and_$a_xor_b$$                                    =  0x38 // ((a or c) and (a xor b))
   , $b_xor_$a_or_$c_xor_1$$$                                    =  0x39 // (b xor (a or (c xor 1)))
   , $$b_notand_a$_or_$a_notand_c$$                              =  0x3a // ((b notand a) or (a notand c))
   , $$a_notand_c$_or_$b_xor_1$$                                 =  0x3b // ((a notand c) or (b xor 1))
   , $b_xor_a$                                                       =  0x3c // (b xor a)
   , $$a_xor_b$_or_$$a_or_c$_xor_1$$                           =  0x3d // ((a xor b) or ((a or c) xor 1))
   , $$a_notand_c$_or_$a_xor_b$$                                 =  0x3e // ((a notand c) or (a xor b))
   , $$b_and_a$_xor_1$                                             =  0x3f // ((b and a) xor 1)
   , $$c_notand_a$_and_b$                                          =  0x40 // ((c notand a) and b)
   , $$c_or_$b_xor_a$$_xor_1$                                    =  0x41 // ((c or (b xor a)) xor 1)
   , $$a_xor_c$_and_$b_xor_c$$                                   =  0x42 // ((a xor c) and (b xor c))
   , $$a_and_c$_notand_$a_xor_$b_xor_1$$$                      =  0x43 // ((a and c) notand (a xor (b xor 1)))
   , $c_notand_b$                                                    =  0x44 // (c notand b)
   , $c_notand_$$a_xor_1$_or_b$$                                 =  0x45 // (c notand ((a xor 1) or b))
   , $$a_and_c$_notand_$b_xor_c$$                                =  0x46 // ((a and c) notand (b xor c))
   , $$c_notand_b$_or_$b_notand_$a_xor_1$$$                    =  0x47 // ((c notand b) or (b notand (a xor 1)))
   , $b_and_$a_xor_c$$                                             =  0x48 // (b and (a xor c))
   , $$b_and_$a_xor_c$$_or_$b_notand_$$a_or_c$_xor_1$$$    =  0x49 // ((b and (a xor c)) or (b notand ((a or c) xor 1)))
   , $$b_or_c$_and_$a_xor_c$$                                    =  0x4a // ((b or c) and (a xor c))
   , $a_xor_$$b_xor_1$_or_c$$                                    =  0x4b // (a xor ((b xor 1) or c))
   , $$a_and_c$_notand_b$                                          =  0x4c // ((a and c) notand b)
   , $$$a_and_c$_notand_b$_or_$b_notand_$$a_or_c$_xor_1$$$ =  0x4d // (((a and c) notand b) or (b notand ((a or c) xor 1)))
   , $$a_notand_c$_or_$c_notand_b$$                              =  0x4e // ((a notand c) or (c notand b))
   , $$c_notand_b$_or_$a_xor_1$$                                 =  0x4f // ((c notand b) or (a xor 1))
   , $c_notand_a$                                                    =  0x50 // (c notand a)
   , $c_notand_$a_or_$b_xor_1$$$                                 =  0x51 // (c notand (a or (b xor 1)))
   , $$b_and_c$_notand_$a_xor_c$$                                =  0x52 // ((b and c) notand (a xor c))
   , $$c_notand_a$_or_$a_notand_$b_xor_1$$$                    =  0x53 // ((c notand a) or (a notand (b xor 1)))
   , $c_notand_$a_or_b$$                                           =  0x54 // (c notand (a or b))
   , $c_xor_1$                                                       =  0x55 // (c xor 1)
   , $c_xor_$b_or_a$$                                              =  0x56 // (c xor (b or a))
   , $$c_and_$b_or_a$$_xor_1$                                    =  0x57 // ((c and (b or a)) xor 1)
   , $$a_or_b$_and_$a_xor_c$$                                    =  0x58 // ((a or b) and (a xor c))
   , $c_xor_$a_or_$b_xor_1$$$                                    =  0x59 // (c xor (a or (b xor 1)))
   , $c_xor_a$                                                       =  0x5a // (c xor a)
   , $$a_xor_c$_or_$$a_or_b$_xor_1$$                           =  0x5b // ((a xor c) or ((a or b) xor 1))
   , $$c_notand_a$_or_$a_notand_b$$                              =  0x5c // ((c notand a) or (a notand b))
   , $$a_notand_b$_or_$c_xor_1$$                                 =  0x5d // ((a notand b) or (c xor 1))
   , $$c_notand_b$_or_$a_xor_c$$                                 =  0x5e // ((c notand b) or (a xor c))
   , $$c_and_a$_xor_1$                                             =  0x5f // ((c and a) xor 1)
   , $a_and_$b_xor_c$$                                             =  0x60 // (a and (b xor c))
   , $$a_and_$b_xor_c$$_or_$a_notand_$$b_or_c$_xor_1$$$    =  0x61 // ((a and (b xor c)) or (a notand ((b or c) xor 1)))
   , $$a_or_c$_and_$b_xor_c$$                                    =  0x62 // ((a or c) and (b xor c))
   , $b_xor_$$a_xor_1$_or_c$$                                    =  0x63 // (b xor ((a xor 1) or c))
   , $$a_or_b$_and_$b_xor_c$$                                    =  0x64 // ((a or b) and (b xor c))
   , $c_xor_$$a_xor_1$_or_b$$                                    =  0x65 // (c xor ((a xor 1) or b))
   , $c_xor_b$                                                       =  0x66 // (c xor b)
   , $$b_xor_c$_or_$$a_or_b$_xor_1$$                           =  0x67 // ((b xor c) or ((a or b) xor 1))
   , $$a_and_$b_xor_c$$_or_$a_notand_$b_and_c$$$             =  0x68 // ((a and (b xor c)) or (a notand (b and c)))
   , $$a_xor_$b_xor_c$$_xor_1$                                   =  0x69 // ((a xor (b xor c)) xor 1)
   , $c_xor_$b_and_a$$                                             =  0x6a // (c xor (b and a))
   , $$a_notand_c$_or_$$a_xor_1$_xor_$b_xor_c$$$             =  0x6b // ((a notand c) or ((a xor 1) xor (b xor c)))
   , $b_xor_$a_and_c$$                                             =  0x6c // (b xor (a and c))
   , $$a_notand_b$_or_$$a_xor_1$_xor_$b_xor_c$$$             =  0x6d // ((a notand b) or ((a xor 1) xor (b xor c)))
   , $$a_notand_b$_or_$b_xor_c$$                                 =  0x6e // ((a notand b) or (b xor c))
   , $$b_xor_c$_or_$a_xor_1$$                                    =  0x6f // ((b xor c) or (a xor 1))
   , $$b_and_c$_notand_a$                                          =  0x70 // ((b and c) notand a)
   , $$$b_or_c$_xor_1$_or_$a_and_$b_xor_c$$$                 =  0x71 // (((b or c) xor 1) or (a and (b xor c)))
   , $$b_notand_c$_or_$c_notand_a$$                              =  0x72 // ((b notand c) or (c notand a))
   , $$c_notand_a$_or_$b_xor_1$$                                 =  0x73 // ((c notand a) or (b xor 1))
   , $$c_notand_b$_or_$b_notand_a$$                              =  0x74 // ((c notand b) or (b notand a))
   , $$b_notand_a$_or_$c_xor_1$$                                 =  0x75 // ((b notand a) or (c xor 1))
   , $$b_notand_a$_or_$b_xor_c$$                                 =  0x76 // ((b notand a) or (b xor c))
   , $$c_and_b$_xor_1$                                             =  0x77 // ((c and b) xor 1)
   , $a_xor_$b_and_c$$                                             =  0x78 // (a xor (b and c))
   , $$b_notand_a$_or_$$b_xor_1$_xor_$a_xor_c$$$             =  0x79 // ((b notand a) or ((b xor 1) xor (a xor c)))
   , $$b_notand_a$_or_$a_xor_c$$                                 =  0x7a // ((b notand a) or (a xor c))
   , $$a_xor_c$_or_$b_xor_1$$                                    =  0x7b // ((a xor c) or (b xor 1))
   , $$c_notand_a$_or_$a_xor_b$$                                 =  0x7c // ((c notand a) or (a xor b))
   , $$a_xor_b$_or_$c_xor_1$$                                    =  0x7d // ((a xor b) or (c xor 1))
   , $$a_xor_b$_or_$a_xor_c$$                                    =  0x7e // ((a xor b) or (a xor c))
   , $$$a_and_b$_and_c$_xor_1$                                   =  0x7f // (((a and b) and c) xor 1)
   , $a_and_$b_and_c$$                                             =  0x80 // (a and (b and c))
   , $$a_xor_c$_notand_$a_xor_$b_xor_1$$$                      =  0x81 // ((a xor c) notand (a xor (b xor 1)))
   , $$b_xor_a$_notand_c$                                          =  0x82 // ((b xor a) notand c)
   , $$a_xor_b$_notand_$$a_xor_1$_or_c$$                       =  0x83 // ((a xor b) notand ((a xor 1) or c))
   , $$a_xor_c$_notand_b$                                          =  0x84 // ((a xor c) notand b)
   , $$a_xor_c$_notand_$b_or_$c_xor_1$$$                       =  0x85 // ((a xor c) notand (b or (c xor 1)))
   , $$b_or_c$_and_$c_xor_$a_xor_b$$$                          =  0x86 // ((b or c) and (c xor (a xor b)))
   , $$a_xor_$b_and_c$$_xor_1$                                   =  0x87 // ((a xor (b and c)) xor 1)
   , $c_and_b$                                                       =  0x88 // (c and b)
   , $$b_xor_c$_notand_$$a_xor_1$_or_b$$                       =  0x89 // ((b xor c) notand ((a xor 1) or b))
   , $$b_notand_a$_notand_c$                                       =  0x8a // ((b notand a) notand c)
   , $$b_and_c$_or_$b_notand_$a_xor_1$$$                       =  0x8b // ((b and c) or (b notand (a xor 1)))
   , $$c_notand_a$_notand_b$                                       =  0x8c // ((c notand a) notand b)
   , $$c_and_b$_or_$c_notand_$a_xor_1$$$                       =  0x8d // ((c and b) or (c notand (a xor 1)))
   , $$b_and_c$_or_$a_notand_$b_xor_c$$$                       =  0x8e // ((b and c) or (a notand (b xor c)))
   , $$b_and_c$_or_$a_xor_1$$                                    =  0x8f // ((b and c) or (a xor 1))
   , $$b_xor_c$_notand_a$                                          =  0x90 // ((b xor c) notand a)
   , $$b_xor_c$_notand_$a_or_$b_xor_1$$$                       =  0x91 // ((b xor c) notand (a or (b xor 1)))
   , $$a_or_c$_and_$c_xor_$a_xor_b$$$                          =  0x92 // ((a or c) and (c xor (a xor b)))
   , $$b_xor_$a_and_c$$_xor_1$                                   =  0x93 // ((b xor (a and c)) xor 1)
   , $$a_or_b$_and_$b_xor_$a_xor_c$$$                          =  0x94 // ((a or b) and (b xor (a xor c)))
   , $$c_xor_$b_and_a$$_xor_1$                                   =  0x95 // ((c xor (b and a)) xor 1)
   , $a_xor_$b_xor_c$$                                             =  0x96 // (a xor (b xor c))
   , $$$b_xor_c$_notand_a$_or_$a_notand_$$b_and_c$_xor_1$$$ =  0x97 // (((b xor c) notand a) or (a notand ((b and c) xor 1)))
   , $$b_xor_c$_notand_$a_or_b$$                                 =  0x98 // ((b xor c) notand (a or b))
   , $$c_xor_b$_xor_1$                                             =  0x99 // ((c xor b) xor 1)
   , $$b_notand_a$_xor_c$                                          =  0x9a // ((b notand a) xor c)
   , $$a_notand_c$_or_$b_xor_$c_xor_1$$$                       =  0x9b // ((a notand c) or (b xor (c xor 1)))
   , $$c_notand_a$_xor_b$                                          =  0x9c // ((c notand a) xor b)
   , $$a_notand_b$_or_$b_xor_$c_xor_1$$$                       =  0x9d // ((a notand b) or (b xor (c xor 1)))
   , $$b_and_c$_or_$c_xor_$a_xor_b$$$                          =  0x9e // ((b and c) or (c xor (a xor b)))
   , $$a_and_$b_xor_c$$_xor_1$                                   =  0x9f // ((a and (b xor c)) xor 1)
   , $c_and_a$                                                       =  0xa0 // (c and a)
   , $$a_xor_c$_notand_$a_or_$b_xor_1$$$                       =  0xa1 // ((a xor c) notand (a or (b xor 1)))
   , $$a_notand_b$_notand_c$                                       =  0xa2 // ((a notand b) notand c)
   , $$a_and_c$_or_$a_notand_$b_xor_1$$$                       =  0xa3 // ((a and c) or (a notand (b xor 1)))
   , $$a_xor_c$_notand_$a_or_b$$                                 =  0xa4 // ((a xor c) notand (a or b))
   , $$c_xor_a$_xor_1$                                             =  0xa5 // ((c xor a) xor 1)
   , $$a_notand_b$_xor_c$                                          =  0xa6 // ((a notand b) xor c)
   , $$b_notand_c$_or_$a_xor_$c_xor_1$$$                       =  0xa7 // ((b notand c) or (a xor (c xor 1)))
   , $c_and_$a_or_b$$                                              =  0xa8 // (c and (a or b))
   , $$c_xor_$b_or_a$$_xor_1$                                    =  0xa9 // ((c xor (b or a)) xor 1)
   , C                                                                 =  0xaa // c
   , $c_or_$$b_or_a$_xor_1$$                                     =  0xab // (c or ((b or a) xor 1))
   , $$a_and_c$_or_$a_notand_b$$                                 =  0xac // ((a and c) or (a notand b))
   , $$b_and_c$_or_$a_xor_$c_xor_1$$$                          =  0xad // ((b and c) or (a xor (c xor 1)))
   , $$a_notand_b$_or_c$                                           =  0xae // ((a notand b) or c)
   , $c_or_$a_xor_1$$                                              =  0xaf // (c or (a xor 1))
   , $$c_notand_b$_notand_a$                                       =  0xb0 // ((c notand b) notand a)
   , $$c_and_a$_or_$c_notand_$b_xor_1$$$                       =  0xb1 // ((c and a) or (c notand (b xor 1)))
   , $$b_and_$a_and_c$$_or_$b_notand_$a_or_c$$$              =  0xb2 // ((b and (a and c)) or (b notand (a or c)))
   , $$a_and_c$_or_$b_xor_1$$                                    =  0xb3 // ((a and c) or (b xor 1))
   , $$c_notand_b$_xor_a$                                          =  0xb4 // ((c notand b) xor a)
   , $$b_notand_a$_or_$a_xor_$c_xor_1$$$                       =  0xb5 // ((b notand a) or (a xor (c xor 1)))
   , $$a_and_c$_or_$c_xor_$a_xor_b$$$                          =  0xb6 // ((a and c) or (c xor (a xor b)))
   , $$b_and_$a_xor_c$$_xor_1$                                   =  0xb7 // ((b and (a xor c)) xor 1)
   , $$b_and_c$_or_$b_notand_a$$                                 =  0xb8 // ((b and c) or (b notand a))
   , $$a_and_c$_or_$b_xor_$c_xor_1$$$                          =  0xb9 // ((a and c) or (b xor (c xor 1)))
   , $$b_notand_a$_or_c$                                           =  0xba // ((b notand a) or c)
   , $c_or_$b_xor_1$$                                              =  0xbb // (c or (b xor 1))
   , $$a_and_c$_or_$a_xor_b$$                                    =  0xbc // ((a and c) or (a xor b))
   , $$a_xor_b$_or_$a_xor_$c_xor_1$$$                          =  0xbd // ((a xor b) or (a xor (c xor 1)))
   , $c_or_$b_xor_a$$                                              =  0xbe // (c or (b xor a))
   , $c_or_$$b_and_a$_xor_1$$                                    =  0xbf // (c or ((b and a) xor 1))
   , $b_and_a$                                                       =  0xc0 // (b and a)
   , $$a_xor_b$_notand_$a_or_$c_xor_1$$$                       =  0xc1 // ((a xor b) notand (a or (c xor 1)))
   , $$a_xor_b$_notand_$a_or_c$$                                 =  0xc2 // ((a xor b) notand (a or c))
   , $$b_xor_a$_xor_1$                                             =  0xc3 // ((b xor a) xor 1)
   , $$a_notand_c$_notand_b$                                       =  0xc4 // ((a notand c) notand b)
   , $$a_and_b$_or_$a_notand_$c_xor_1$$$                       =  0xc5 // ((a and b) or (a notand (c xor 1)))
   , $$a_notand_c$_xor_b$                                          =  0xc6 // ((a notand c) xor b)
   , $$c_notand_b$_or_$a_xor_$b_xor_1$$$                       =  0xc7 // ((c notand b) or (a xor (b xor 1)))
   , $b_and_$a_or_c$$                                              =  0xc8 // (b and (a or c))
   , $$b_xor_$a_or_c$$_xor_1$                                    =  0xc9 // ((b xor (a or c)) xor 1)
   , $$a_and_b$_or_$a_notand_c$$                                 =  0xca // ((a and b) or (a notand c))
   , $$b_and_c$_or_$a_xor_$b_xor_1$$$                          =  0xcb // ((b and c) or (a xor (b xor 1)))
   , B                                                                 =  0xcc // b
   , $b_or_$$a_or_c$_xor_1$$                                     =  0xcd // (b or ((a or c) xor 1))
   , $$a_notand_c$_or_b$                                           =  0xce // ((a notand c) or b)
   , $b_or_$a_xor_1$$                                              =  0xcf // (b or (a xor 1))
   , $$b_notand_c$_notand_a$                                       =  0xd0 // ((b notand c) notand a)
   , $$$b_or_c$_xor_1$_or_$a_and_b$$                           =  0xd1 // (((b or c) xor 1) or (a and b))
   , $$b_notand_c$_xor_a$                                          =  0xd2 // ((b notand c) xor a)
   , $$c_notand_a$_or_$a_xor_$b_xor_1$$$                       =  0xd3 // ((c notand a) or (a xor (b xor 1)))
   , $$c_notand_b$_or_$$b_xor_c$_notand_a$$                    =  0xd4 // ((c notand b) or ((b xor c) notand a))
   , $$a_and_b$_or_$c_xor_1$$                                    =  0xd5 // ((a and b) or (c xor 1))
   , $$a_and_b$_or_$b_xor_$a_xor_c$$$                          =  0xd6 // ((a and b) or (b xor (a xor c)))
   , $$c_and_$b_xor_a$$_xor_1$                                   =  0xd7 // ((c and (b xor a)) xor 1)
   , $$c_and_b$_or_$c_notand_a$$                                 =  0xd8 // ((c and b) or (c notand a))
   , $$a_and_b$_or_$b_xor_$c_xor_1$$$                          =  0xd9 // ((a and b) or (b xor (c xor 1)))
   , $$a_and_b$_or_$a_xor_c$$                                    =  0xda // ((a and b) or (a xor c))
   , $$a_xor_c$_or_$a_xor_$b_xor_1$$$                          =  0xdb // ((a xor c) or (a xor (b xor 1)))
   , $$c_notand_a$_or_b$                                           =  0xdc // ((c notand a) or b)
   , $b_or_$c_xor_1$$                                              =  0xdd // (b or (c xor 1))
   , $b_or_$a_xor_c$$                                              =  0xde // (b or (a xor c))
   , $b_or_$$a_and_c$_xor_1$$                                    =  0xdf // (b or ((a and c) xor 1))
   , $a_and_$b_or_c$$                                              =  0xe0 // (a and (b or c))
   , $$a_xor_$b_or_c$$_xor_1$                                    =  0xe1 // ((a xor (b or c)) xor 1)
   , $$b_and_a$_or_$b_notand_c$$                                 =  0xe2 // ((b and a) or (b notand c))
   , $$a_and_c$_or_$a_xor_$b_xor_1$$$                          =  0xe3 // ((a and c) or (a xor (b xor 1)))
   , $$c_and_a$_or_$c_notand_b$$                                 =  0xe4 // ((c and a) or (c notand b))
   , $$a_and_b$_or_$a_xor_$c_xor_1$$$                          =  0xe5 // ((a and b) or (a xor (c xor 1)))
   , $$a_and_b$_or_$b_xor_c$$                                    =  0xe6 // ((a and b) or (b xor c))
   , $$b_xor_c$_or_$a_xor_$b_xor_1$$$                          =  0xe7 // ((b xor c) or (a xor (b xor 1)))
   , $$b_and_c$_or_$a_and_$b_xor_c$$$                          =  0xe8 // ((b and c) or (a and (b xor c)))
   , $$a_and_b$_or_$b_xor_$a_xor_$c_xor_1$$$$                =  0xe9 // ((a and b) or (b xor (a xor (c xor 1))))
   , $c_or_$b_and_a$$                                              =  0xea // (c or (b and a))
   , $c_or_$$b_xor_a$_xor_1$$                                    =  0xeb // (c or ((b xor a) xor 1))
   , $b_or_$a_and_c$$                                              =  0xec // (b or (a and c))
   , $b_or_$$a_xor_c$_xor_1$$                                    =  0xed // (b or ((a xor c) xor 1))
   , $c_or_b$                                                        =  0xee // (c or b)
   , $b_or_$$a_xor_1$_or_c$$                                     =  0xef // (b or ((a xor 1) or c))
   , A                                                                 =  0xf0 //  a
   , $a_or_$$b_or_c$_xor_1$$                                     =  0xf1 // (a or ((b or c) xor 1))
   , $$b_notand_c$_or_a$                                           =  0xf2 // ((b notand c) or a)
   , $a_or_$b_xor_1$$                                              =  0xf3 // (a or (b xor 1))
   , $$c_notand_b$_or_a$                                           =  0xf4 // ((c notand b) or a)
   , $a_or_$c_xor_1$$                                              =  0xf5 // (a or (c xor 1))
   , $a_or_$b_xor_c$$                                              =  0xf6 // (a or (b xor c))
   , $a_or_$$b_and_c$_xor_1$$                                    =  0xf7 // (a or ((b and c) xor 1))
   , $a_or_$b_and_c$$                                              =  0xf8 // (a or (b and c))
   , $a_or_$$b_xor_c$_xor_1$$                                    =  0xf9 // (a or ((b xor c) xor 1))
   , $c_or_a$                                                        =  0xfa // (c or a)
   , $a_or_$$b_xor_1$_or_c$$                                     =  0xfb // (a or ((b xor 1) or c))
   , $b_or_a$                                                        =  0xfc // (b or a)
   , $a_or_$b_or_$c_xor_1$$$                                     =  0xfd // (a or (b or (c xor 1)))
   , $a_or_$b_or_c$$                                               =  0xfe // (a or (b or c))
   , TRUE                                                              =  0xff // 1
   };

  EVE_FORCEINLINE constexpr std::int32_t to_integer(bit_tern a) noexcept
  {
    return static_cast<std::int32_t>(a);
  }

}
