//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <cstdint>

namespace eve
{

//################################################################################################################################
//# Bits of the MXCSR register. Diagram was //# +----+--------+----+----+----+----+----+----+----+----+----+----+----+----+----+ #
//# converted to ASCII-art from Figure 10-3 //# | 15 | 14  13 | 12 | 11 | 10 |  9 |  8 |  7 |  6 |  5 |  4 |  3 |  2 |  1 |  0 | #
//# in the Intel 64 and IA-32 Architectures //# +----+--------+----+----+----+----+----+----+----+----+----+----+----+----+----+ #
//# Software Developer's Manual, Volume 1.  //#   FZ     RC     PM   UM   OM   ZM   DM   IM   DAZ  PE   UE   OE   ZE   DE   IE   #
//# ########################################//#    |      |      |    |    |    |    |    |    |    |    |    |    |    |    |   #
//# Flush to Zero -------------------------------'        |      |    |    |    |    |    |    |    |    |    |    |    |    |   #
//# Rounding Control -----------------------------------'        |    |    |    |    |    |    |    |    |    |    |    |    |   #
//# Precision Mask --------------------------------------------'      |    |    |    |    |    |    |    |    |    |    |    |   #
//# Underflow Mask -------------------------------------------------'      |    |    |    |    |    |    |    |    |    |    |   #
//# Overflow Mask -------------------------------------------------------'      |    |    |    |    |    |    |    |    |    |   #
//# Divide-by-Zero Mask ------------------------------------------------------'      |    |    |    |    |    |    |    |    |   #
//# Denormal Operation Mask -------------------------------------------------------'      |    |    |    |    |    |    |    |   #
//# Invalid Operation Mask -------------------------------------------------------------'      |    |    |    |    |    |    |   #
//# Denormals Are Zeros ---------------------------------------------------------------------'      |    |    |    |    |    |   #
//# Precision Flag -------------------------------------------------------------------------------'      |    |    |    |    |   #
//# Underflow Flag ------------------------------------------------------------------------------------'      |    |    |    |   #
//# Overflow Flag ------------------------------------------------------------------------------------------'      |    |    |   #
//# Divide-by-Zero Flag -----------------------------------------------------------------------------------------'      |    |   #
//# Denormal Flag ----------------------------------------------------------------------------------------------------'      |   #
//# Invalid Operation Flag ------------------------------------------------------------------------------------------------'     #
//################################################################################################################################


  inline constexpr std::uint32_t ie =  1;          // Flush to Zero
  inline constexpr std::uint32_t de =  2;          // Denormal Flag
  inline constexpr std::uint32_t ze =  4;          // Divide-by-Zero Flag
  inline constexpr std::uint32_t oe =  8;          // Overflow Flag
  inline constexpr std::uint32_t ue =  16;         // Underflow Flag
  inline constexpr std::uint32_t pe =  32;         // Precision Flag
  inline constexpr std::uint32_t daz=  64;         // Denormals Are Zeros
  inline constexpr std::uint32_t im =  128;        // Invalid Operation Mask
  inline constexpr std::uint32_t dm =  256;        // Denormal Operation Mask
  inline constexpr std::uint32_t zm =  512;        // Divide-by-Zero Mask
  inline constexpr std::uint32_t om =  1024;       // Overflow Mask
  inline constexpr std::uint32_t um =  2048;       // Underflow Mask
  inline constexpr std::uint32_t pm =  4096;       // Precision Mask
  inline constexpr std::uint32_t rc =  8192+16384;// Rounding Control
  inline constexpr std::uint32_t fz =  32768;      // Flush to Zero

  inline constexpr std::uint32_t round_to_nearest = FE_TONEAREST;  // Round to nearest (even)
  inline constexpr std::uint32_t round_down       = FE_DOWNWARD;   // Round down
  inline constexpr std::uint32_t round_up         = FE_UPWARD;     // Round up
  inline constexpr std::uint32_t round_toward_zero= FE_TOWARDZERO; // Round toward zero

  inline  std::uint32_t get_csr(){ return _mm_getcsr(); }
  inline  std::uint32_t get_csr_flags(uint32_t flags){return get_csr() & flags; }
  inline  void          set_csr(std::uint32_t a){ return _mm_setcsr(a & 0xfffful); }

  inline  bool get_ie() { return get_csr_flags(ie); }
  inline  bool get_de() { return get_csr_flags(de); }
  inline  bool get_ze() { return get_csr_flags(ze); }
  inline  bool get_oe() { return get_csr_flags(oe); }
  inline  bool get_ue() { return get_csr_flags(ue); }
  inline  bool get_pe() { return get_csr_flags(pe); }
  inline  bool get_daz(){ return get_csr_flags(daz);}
  inline  bool get_im() { return get_csr_flags(im); }
  inline  bool get_dm() { return get_csr_flags(dm); }
  inline  bool get_zm() { return get_csr_flags(zm); }
  inline  bool get_om() { return get_csr_flags(om); }
  inline  bool get_um() { return get_csr_flags(um); }
  inline  bool get_pm() { return get_csr_flags(pm); }
  inline  bool get_fz() { return get_csr_flags(fz); }
  inline  std::uint32_t get_rc() { return get_csr_flags(rc); }
  inline  std::uint32_t get_rounding() { return get_csr_flags(rc >>  3); }
  inline  setround_tonearest
}
