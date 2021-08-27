//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <bitset>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <type_traits>
#include <cmath>
#include <cassert>
#include <bit>
#include <eve/function/lohi.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd
  //! @{
  //================================================================================================
  //! @brief int128 type
  //!
  //! **Required header:** `#include <eve/int128.hpp>`
  //!
  //! eve::int128
  //!
  //!This header file defines 128-bit integer types, `uint128` and `int128`.
  //!
  //================================================================================================
//  struct int128;
  struct uint128 //little endian
  {
    std::uint64_t lo_;
    std::uint64_t hi_;
 //    using endianess =  std::endian::native; //== std::endian::little;
    //==============================================================================================
    //! @name Constructors
    //! @{
    //==============================================================================================
    //! Default constructor
    EVE_FORCEINLINE constexpr uint128() noexcept {}

    //! from smaller size ints

    EVE_FORCEINLINE  constexpr  uint128(integral_scalar_value auto v) noexcept
    requires (sizeof(v) <= 8)
      : lo_{static_cast<std::uint64_t>(v)}, hi_{0} {}
    EVE_FORCEINLINE constexpr  uint128( integral_scalar_value auto hi
                                      , integral_scalar_value auto lo) noexcept
    requires (sizeof(lo_) <= 8)&&(sizeof(hi_) <= 8)
      : lo_{static_cast<std::uint64_t>(lo)}, hi_{static_cast<std::uint64_t>(hi)} {}

// #ifdef ABSL_HAVE_INTRINSIC_INT128
//     constexpr uint128(__int128 v) noexcept
//     : lo_{static_cast<uint64_t>(v & ~uint64_t{0})},
//       hi_{static_cast<uint64_t>(static_cast<unsigned __int128>(v) >> 64)} {};

//     constexpr uint128(unsigned __int128 v) noexcept;
//     : lo_{static_cast<uint64_t>(v & ~uint64_t{0})},
//         hi_{static_cast<uint64_t>(v >> 64)} {}
// #endif

 //   constexpr uint128(int128 v) noexcept
//    : lo_{v.lo_}, hi_{static_cast<uint64_t>(v.hi_)} {}


    explicit constexpr uint128(float v) noexcept;
    explicit constexpr uint128(double v) noexcept;
    explicit constexpr uint128(long double v) noexcept;

    //! Copy constructor
    EVE_FORCEINLINE constexpr uint128(uint128 const&) noexcept = default;

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Assignment operators
    //! @{
    //==============================================================================================
    //! Assign another uint128
    EVE_FORCEINLINE constexpr uint128 &operator=(uint128 const& v)  noexcept =  default;


    //==============================================================================================
    //! @}
    //==============================================================================================
    //==============================================================================================
    //! @name lo,  hi
    //! @{
    //==============================================================================================
    EVE_FORCEINLINE constexpr std::uint64_t & lo()  {return lo_; };
    EVE_FORCEINLINE constexpr std::uint64_t & hi()  {return hi_; };
    EVE_FORCEINLINE constexpr std::uint64_t lo() const {return lo_; };
    EVE_FORCEINLINE constexpr std::uint64_t hi() const {return hi_; };


    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name conversion operators
    //! @{
    //==============================================================================================
    EVE_FORCEINLINE constexpr operator bool()          const noexcept { return lo_ || hi_; }
    EVE_FORCEINLINE constexpr operator std::uint64_t() const noexcept { return lo_;  }
    EVE_FORCEINLINE constexpr operator std::uint32_t() const noexcept { return static_cast<std::uint32_t>(lo_);}
    EVE_FORCEINLINE constexpr operator std::uint16_t() const noexcept { return static_cast<std::uint16_t>(lo_);}
    EVE_FORCEINLINE constexpr operator std::uint8_t()  const noexcept { return static_cast<std::uint8_t>(lo_); }
    EVE_FORCEINLINE constexpr operator std::int64_t()  const noexcept { return static_cast<std::int64_t>(lo_); }
    EVE_FORCEINLINE constexpr operator std::int32_t()  const noexcept { return static_cast<std::uint32_t>(lo_);}
    EVE_FORCEINLINE constexpr operator std::int16_t()  const noexcept { return static_cast<std::uint16_t>(lo_);}
    EVE_FORCEINLINE constexpr operator std::int8_t()   const noexcept { return static_cast<std::uint8_t>(lo_); }
// #ifdef ABSL_HAVE_INTRINSIC_INT128
//     EVE_FORCEINLINE constexpr explicit operator __int128() const noexcept {
//       return (static_cast<__int128>(hi_) << 64) + lo_;
//     }

//     EVE_FORCEINLINE constexpr explicit operator unsigned __int128() noexcept const {
//       return (static_cast<unsigned __int128>(hi_) << 64) + lo_;
//     }
// #endif
    EVE_FORCEINLINE operator float() const noexcept {
      return static_cast<float>(lo_) + std::ldexp(static_cast<float>(hi_), 64);
    }

    EVE_FORCEINLINE operator double() const noexcept {
      return static_cast<double>(lo_) + std::ldexp(static_cast<double>(hi_), 64);
    }
//    EVE_FORCEINLINE constexpr auto bits()       const noexcept { return value_; }

//     EVE_FORCEINLINE constexpr auto mask() const noexcept
//     {
//       value_type that;
//       std::memcpy(&that, &value_, sizeof(value_type));
//       return that;
//     }
    void swap( uint128& other )
    {
      std::swap(lo_,other.lo_);
      std::swap(hi_,other.hi_);
    }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    // Comparison operators
    //==============================================================================================
    constexpr friend bool operator==(uint128 lhs, eve::integral_scalar_value auto rhs) {
      return uint128(rhs) == lhs;
    }
    constexpr friend bool operator==(eve::integral_scalar_value auto lhs, uint128 rhs) {
      return uint128(lhs) == rhs;
    }
    constexpr friend bool operator==(uint128 lhs, uint128 rhs) {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//       return static_cast<unsigned __int128>(lhs) ==
//         static_cast<unsigned __int128>(rhs);
// #else
      return (lhs.lo_ == rhs.lo_) && (lhs.hi_ == rhs.hi_);
//#endif
      }

    constexpr friend bool operator!=(uint128 lhs, eve::integral_scalar_value auto rhs) {
      return uint128(rhs) != lhs;
    }
    constexpr friend bool operator!=(eve::integral_scalar_value auto lhs, uint128 rhs) {
      return uint128(lhs) != rhs;
    }
    constexpr friend bool operator!=(uint128 lhs, uint128 rhs) {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//         return static_cast<unsigned __int128>(lhs) !=
//           static_cast<unsigned __int128>(rhs);
// #else
      return (lhs.lo_ != rhs.lo_) || (lhs.hi_ != rhs.hi_);
//#endif
      }

    constexpr friend bool operator!(uint128 val) {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//       return !static_cast<unsigned __int128>(val);
// #else
      return !val.lo_ && !val.hi_;
// #endif
    }

    constexpr  friend bool operator<(uint128 lhs, uint128 rhs) {
// #ifdef ABSL_HAVE_INTRINSIC_INT128
//   return static_cast<unsigned __int128>(lhs) <
//          static_cast<unsigned __int128>(rhs);
// #else
      return (lhs.hi_ == rhs.hi_)
        ? (lhs.lo_ < rhs.lo_)
        : (lhs.hi_ < rhs.hi_);
//#endif
        }

    constexpr friend bool operator>(uint128 lhs, uint128 rhs) { return rhs < lhs; }

    constexpr friend bool operator<=(uint128 lhs, uint128 rhs)
    {
      return !(lhs > rhs);
    }

     constexpr friend bool operator>=(uint128 lhs, uint128 rhs) {
      return !(lhs < rhs);
    }

    //arithmetic operations
    friend uint128 operator/(uint128 lhs, eve::integral_scalar_value auto rhs) {
      return lhs/uint128(rhs);
    }
    friend uint128 operator/(eve::integral_scalar_value auto lhs, uint128 rhs ) {
      return uint128(lhs)/rhs;
    }

//#if !defined(ABSL_HAVE_INTRINSIC_INT128)
    friend uint128 operator/(uint128 lhs, uint128 rhs) {
      uint128 quotient = 0;
      uint128 remainder = 0;
      DivModImpl(lhs, rhs, &quotient, &remainder);
      return quotient;
    }

    friend uint128 operator%(uint128 lhs, uint128 rhs) {
      uint128 quotient = 0;
      uint128 remainder = 0;
      DivModImpl(lhs, rhs, &quotient, &remainder);
      return remainder;
    }
//#endif  // !defined(ABSL_HAVE_INTRINSIC_INT128)

    EVE_FORCEINLINE uint128& operator<<=(int amount) {
      *this = *this << amount;
      return *this;
    }

    EVE_FORCEINLINE uint128& operator>>=(int amount) {
      *this = *this >> amount;
      return *this;
    }

    EVE_FORCEINLINE uint128& operator+=(uint128 other) {
      *this = *this + other;
      return *this;
    }

    EVE_FORCEINLINE uint128& operator-=(uint128 other) {
      *this = *this - other;
      return *this;
    }

    EVE_FORCEINLINE uint128& operator*=(uint128 other) {
      *this = *this * other;
      return *this;
    }

    EVE_FORCEINLINE uint128& operator/=(uint128 other) {
      *this = *this / other;
      return *this;
    }

    EVE_FORCEINLINE uint128& operator%=(uint128 other) {
      *this = *this % other;
      return *this;
    }

     EVE_FORCEINLINE uint128& operator+=(eve::unsigned_value auto other) {
      *this = *this + other;
      return *this;
    }

    EVE_FORCEINLINE uint128& operator-=(eve::unsigned_value auto other) {
      *this = *this - other;
      return *this;
    }

    EVE_FORCEINLINE uint128& operator*=(eve::unsigned_value auto other) {
      *this = *this * other;
      return *this;
    }

    EVE_FORCEINLINE uint128& operator/=(eve::unsigned_value auto other) {
      *this = *this / other;
      return *this;
    }

    EVE_FORCEINLINE uint128& operator%=(eve::unsigned_value auto other) {
      *this = *this % other;
      return *this;
    }

    EVE_FORCEINLINE uint128 operator++(int) {
      uint128 tmp(*this);
      *this += 1;
      return tmp;
    }

    EVE_FORCEINLINE uint128 operator--(int) {
      uint128 tmp(*this);
      *this -= 1;
      return tmp;
    }

    EVE_FORCEINLINE uint128& operator++() {
      *this += 1;
      return *this;
    }

    EVE_FORCEINLINE uint128& operator--() {
      *this -= 1;
      return *this;
    }

    EVE_FORCEINLINE uint128& operator|=(uint128 other) {
      *this = *this | other;
      return *this;
    }

    EVE_FORCEINLINE uint128& operator&=(uint128 other) {
      *this = *this & other;
      return *this;
    }

    EVE_FORCEINLINE uint128& operator^=(uint128 other) {
      *this = *this ^ other;
      return *this;
}

    friend EVE_FORCEINLINE void swap(uint128 &lhs, uint128 &rhs) noexcept
    {
      lhs.swap(rhs);
    }

    friend EVE_FORCEINLINE constexpr uint128 operator+(uint128 val) {
      return val;
    }

    friend EVE_FORCEINLINE constexpr uint128 operator-(uint128 val) {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//       return -static_cast<unsigned __int128>(val);
// #else
      return uint128(
        ~val.hi_ + static_cast<std::uint64_t>(val.lo_ == 0),
        ~val.lo_ + 1);
//#endif
    }

    friend EVE_FORCEINLINE uint128 operator+(uint128 lhs, eve::integral_scalar_value auto rhs) { return lhs+uint128(rhs); }
    friend EVE_FORCEINLINE uint128 operator+(eve::integral_scalar_value auto lhs, uint128 rhs) { return rhs+lhs; }

    friend EVE_FORCEINLINE uint128 operator+(uint128 lhs, uint128 rhs) {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//   return static_cast<unsigned __int128>(lhs) +
//          static_cast<unsigned __int128>(rhs);
// #else
      return AddResult(
        uint128(lhs.hi_ + rhs.hi_, lhs.lo_ + rhs.lo_)
        , lhs);
//#endif
    }

    friend EVE_FORCEINLINE uint128 operator-(uint128 lhs, eve::integral_scalar_value auto rhs) { return lhs-uint128(rhs); }
    friend EVE_FORCEINLINE uint128 operator-(eve::integral_scalar_value auto lhs, uint128 rhs) { return uint128(lhs)-rhs; }
    friend EVE_FORCEINLINE constexpr uint128 operator-(uint128 lhs, uint128 rhs) {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//   return static_cast<unsigned __int128>(lhs) -
//          static_cast<unsigned __int128>(rhs);
// #else
      return SubResult(
        uint128(lhs.hi_ - rhs.hi_, lhs.lo_ - rhs.lo_),
        lhs, rhs);
//#endif
    }

    friend EVE_FORCEINLINE uint128 operator*(uint128 lhs, unsigned_scalar_value auto rhs)
    {
      return uint128(rhs)*lhs;
    }
     friend EVE_FORCEINLINE uint128 operator*(unsigned_scalar_value auto lhs, uint128 rhs)
    {
      return rhs*lhs;
    }

    friend EVE_FORCEINLINE uint128 operator*(uint128 lhs, uint128 rhs)
    {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//       // TODO(strel) Remove once alignment issues are resolved and unsigned __int128
//       // can be used for uint128 storage.
//       return static_cast<unsigned __int128>(lhs) *
//         static_cast<unsigned __int128>(rhs);
// #elif defined(_MSC_VER) && defined(_M_X64)
//   uint64_t carry;
//   uint64_t low = _umul128(Uint128Low64(lhs), Uint128Low64(rhs), &carry);
//   return MakeUint128(Uint128Low64(lhs) * Uint128High64(rhs) +
//                          Uint128High64(lhs) * Uint128Low64(rhs) + carry,
//                      low);
// #else   // ABSL_HAVE_INTRINSIC128
      uint64_t a32 = lhs.lo_ >> 32;
      uint64_t a00 = lhs.lo_ & 0xffffffff;
      uint64_t b32 = rhs.lo_ >> 32;
      uint64_t b00 = rhs.lo_ & 0xffffffff;
      uint128 result(lhs.hi_ * rhs.lo_ + lhs.lo_ * rhs.hi_ + a32 * b32, a00 * b00);
      result += uint128(a32 * b00) << 32;
      result += uint128(a00 * b32) << 32;
     return result;
//#endif  // ABSL_HAVE_INTRINSIC128
        }

     //==============================================================================================
    //shift operators
    //==============================================================================================
    friend EVE_FORCEINLINE constexpr uint128 operator<<(uint128 lhs, int amount) {
// #ifdef ABSL_HAVE_INTRINSIC_INT128
//       return static_cast<unsigned __int128>(lhs) << amount;
// #else
      // uint64_t shifts of >= 64 are undefined, so we will need some
      // special-casing.
      return amount >= 64 ? uint128(lhs.lo_ << (amount - 64), 0)
        : amount == 0 ? lhs
        : uint128((lhs.hi_ << amount) | (lhs.lo_ >> (64 - amount)),
                      lhs.lo_ << amount);
//#endif
        }

    friend EVE_FORCEINLINE constexpr uint128 operator>>(uint128 lhs, int amount) {
// #ifdef ABSL_HAVE_INTRINSIC_INT128
//       return static_cast<unsigned __int128>(lhs) >> amount;
// #else
      // uint64_t shifts of >= 64 are undefined, so we will need some
      // special-casing.
      return amount >= 64 ? uint128(0, lhs.hi_ >> (amount - 64))
        : amount == 0 ? lhs
        : uint128(lhs.hi_ >> amount,
                      (lhs.lo_ >> amount) | (lhs.hi_ << (64 - amount)));
//#endif
        }

   // bitwise operators.

    friend EVE_FORCEINLINE  uint128 operator~(uint128 val) {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//       return ~static_cast<unsigned __int128>(val);
// #else
      return uint128(~val.hi_, ~val.lo_);
//#endif
    }

    friend EVE_FORCEINLINE  uint128 operator|(uint128 lhs, uint128 rhs) {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//       return static_cast<unsigned __int128>(lhs) |
//         static_cast<unsigned __int128>(rhs);
// #else
      return uint128(lhs.hi_ | rhs.hi_, lhs.lo_ | rhs.lo_);
//#endif
    }

    friend EVE_FORCEINLINE  uint128 operator&(uint128 lhs, uint128 rhs) {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//       return static_cast<unsigned __int128>(lhs) &
//         static_cast<unsigned __int128>(rhs);
// #else
      return uint128(lhs.hi_ & rhs.hi_, lhs.lo_ & rhs.lo_);
//#endif
    }

    friend EVE_FORCEINLINE  uint128 operator^(uint128 lhs, uint128 rhs) {
// #if defined(ABSL_HAVE_INTRINSIC_INT128)
//       return static_cast<unsigned __int128>(lhs) ^
//         static_cast<unsigned __int128>(rhs);
// #else
      return uint128(lhs.hi_ ^ rhs.hi_, lhs.lo_ ^ rhs.lo_);
//#endif
    }

    //==============================================================================================
    // Stream insertion operator
    //==============================================================================================
    friend EVE_FORCEINLINE std::ostream& operator<<(std::ostream& os, uint128 v) {
      std::ios_base::fmtflags flags = os.flags();
      std::string rep = Uint128ToFormattedString(v, flags);

      // Add the requisite padding.
      std::streamsize width = os.width(0);
      if (static_cast<size_t>(width) > rep.size()) {
        std::ios::fmtflags adjustfield = flags & std::ios::adjustfield;
        if (adjustfield == std::ios::left) {
          rep.append(width - rep.size(), os.fill());
        } else if (adjustfield == std::ios::internal &&
                   (flags & std::ios::showbase) &&
                   (flags & std::ios::basefield) == std::ios::hex && (v.lo_  || v.hi_) ) //TODO
        {
          rep.insert(2, width - rep.size(), os.fill());
        } else {
          rep.insert(0, width - rep.size(), os.fill());
        }
      }

      return os << rep;
    }

   private:

    static EVE_FORCEINLINE uint128 AddResult(uint128 result, uint128 lhs)
    {
      // check for carry
      return (result.lo_ < lhs.lo_)
             ? uint128(result.hi_ + 1, result.lo_)
             : result;
    }

    static EVE_FORCEINLINE uint128 SubResult(uint128 result, uint128 lhs, uint128 rhs) {
      // check for augment
      return (lhs.lo_ < rhs.lo_)
             ? uint128(result.hi_ - 1, result.lo_)
             : result;
    }

  public:

    // Long division/modulo for uint128 implemented using the shift-subtract
    // division algorithm adapted from:
    // https://stackoverflow.com/questions/5386377/division-without-using
    static EVE_FORCEINLINE void DivModImpl(uint128 dividend, uint128 divisor, uint128* quotient_ret,
                                  uint128* remainder_ret) {
      assert(divisor.lo_ != 0 || divisor.hi_ != 0);

      if (divisor > dividend) {
        *quotient_ret = 0;
        *remainder_ret = dividend;
        return;
      }

      if (divisor == dividend) {
        *quotient_ret = 1;
        *remainder_ret = 0;
        return;
      }

      uint128 denominator = divisor;
      uint128 quotient = 0;

      auto Fls128 = [](uint128 n){
        // Returns the 0-based position of the last set bit (i.e., most significant bit)
        // in the given uint128. The argument is not 0.
        //
        // For example:
        //   Given: 5 (decimal) == 101 (binary)
        //   Returns: 2
        return (n.hi_) ? 127 - std::countl_zero(n.hi_): 63 - std::countl_zero(n.lo_);
      };
      // Left aligns the MSB of the denominator and the dividend.
      const int shift = Fls128(dividend) - Fls128(denominator);
      denominator <<= shift;

      // Uses shift-subtract algorithm to divide dividend by denominator. The
      // remainder will be left in dividend.
      for (int i = 0; i <= shift; ++i) {
        quotient <<= 1;
        if (dividend >= denominator) {
          dividend -= denominator;
          quotient |= 1;
        }
        denominator >>= 1;
      }

      *quotient_ret = quotient;
      *remainder_ret = dividend;
    }


    static std::string Uint128ToFormattedString(uint128 v, std::ios_base::fmtflags flags)
    {
//       std::cout << std::endl << " === " << std::endl;
//       std::cout << "v " << v.hi_ <<  " -- " << v.lo_ << std::endl;
//       std::cout  << " --- " << std::endl;
      // Select a divisor which is the largest power of the base < 2^64.
      uint128 div;
      int div_base_log;
      switch (flags & std::ios::basefield) {
      case std::ios::hex:
        div = 0x1000000000000000;  // 16^15
        div_base_log = 15;
        break;
      case std::ios::oct:
        div = 01000000000000000000000;  // 8^21
        div_base_log = 21; //21;
        break;
      default:  // std::ios::dec
        div = 10000000000000000000u;  // 10^19
        div_base_log = 19;
        break;
      }
//       if (div_base_log == 15)
//       {
//         std::ostringstream os;
//         std::ios_base::fmtflags copy_mask =
//           std::ios::basefield | std::ios::showbase | std::ios::uppercase;
//         os.setf(flags & copy_mask, copy_mask);
//         if(v.hi_) os << v.hi_;
//         os <<  std::noshowbase << std::setfill('0') << std::setw(div_base_log)<< v.lo_;
//         return os.str();
//       }
//       else if (div_base_log == 31)
//       {
//         std::ostringstream os;
//         std::ios_base::fmtflags copy_mask =
//           std::ios::basefield | std::ios::showbase | std::ios::uppercase;
//         os.setf(flags & copy_mask, copy_mask);
//         if(v.hi_) os << v.hi_;
//         os <<  std::noshowbase << std::setfill('0') << std::setw(div_base_log)<< v.lo_;
//         return os.str();
//       }
      // Now piece together the uint128 representation from three chunks of the
      // original value, each less than "div" and therefore representable as a
      // uint64_t.
      std::ostringstream os;
      std::ios_base::fmtflags copy_mask =
        std::ios::basefield | std::ios::showbase | std::ios::uppercase;
      os.setf(flags & copy_mask, copy_mask);
      uint128 high = v;
      uint128 low;
      DivModImpl(high, div, &high, &low);
      uint128 mid;
      DivModImpl(high, div, &high, &mid);
      if (high.lo_ != 0)
      {
        os << (high.lo_);
        os << std::noshowbase << std::setfill('0') << std::setw(div_base_log);
        os << (mid.lo_);
        os << std::setw(div_base_log);
      }
      else if (mid.lo_ != 0)
      {
        os << (mid.lo_);
        os << std::noshowbase << std::setfill('0') << std::setw(div_base_log);
      }
      os << (low.lo_);
      return os.str();
    }

  };
  //================================================================================================
  //! @}
  //================================================================================================

  class hl
  {
  public:
    hl(uint128 n) : n_ (n) {}
    std::ostream &operator()(std::ostream & out) const
    {
      std::ios_base::fmtflags flags = out.flags();
      std::string m;
      switch (flags & std::ios::basefield) {
      case std::ios::hex:
        m = "0x";
        break;
      case std::ios::oct:
        m = "0";
        break;
      default:  // std::ios::dec
        m = "";
        break;
      }
      out << '(' << m << n_.hi() << ", " << m << n_.lo() << ')';
      return out;
    }
  private:
    uint128 n_;
  };

  std::ostream &operator <<(std::ostream &out, hl n)
  {
    return n(out);
  }

}
// Specialized numeric_limits for uint128.
namespace std {
  template <>
  class numeric_limits<eve::uint128> {
  public:
    static constexpr bool is_specialized = true;
    static constexpr bool is_signed = false;
    static constexpr bool is_integer = true;
    static constexpr bool is_exact = true;
    static constexpr bool has_infinity = false;
    static constexpr bool has_quiet_NaN = false;
    static constexpr bool has_signaling_NaN = false;
    static constexpr float_denorm_style has_denorm = denorm_absent;
    static constexpr bool has_denorm_loss = false;
    static constexpr float_round_style round_style = round_toward_zero;
    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = true;
    static constexpr int digits = 128;
    static constexpr int digits10 = 38;
    static constexpr int max_digits10 = 0;
    static constexpr int radix = 2;
    static constexpr int min_exponent = 0;
    static constexpr int min_exponent10 = 0;
    static constexpr int max_exponent = 0;
    static constexpr int max_exponent10 = 0;
#ifdef ABSL_HAVE_INTRINSIC_INT128
    static constexpr bool traps = numeric_limits<unsigned __int128>::traps;
#else   // ABSL_HAVE_INTRINSIC_INT128
    static constexpr bool traps = numeric_limits<uint64_t>::traps;
#endif  // ABSL_HAVE_INTRINSIC_INT128
    static constexpr bool tinyness_before = false;

    static constexpr eve::uint128 (min)() { return 0; }
    static constexpr eve::uint128 lowest() { return 0; }
    static constexpr eve::uint128 (max)() {
      return eve::uint128(std::numeric_limits<uint64_t>::max(),std::numeric_limits<uint64_t>::max()); }
    static constexpr eve::uint128 epsilon() { return 0; }
    static constexpr eve::uint128 round_error() { return 0; }
    static constexpr eve::uint128 infinity() { return 0; }
    static constexpr eve::uint128 quiet_NaN() { return 0; }
    static constexpr eve::uint128 signaling_NaN() { return 0; }
    static constexpr eve::uint128 denorm_min() { return 0; }
  };
}  // namespace std
