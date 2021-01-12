//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>

#include <bitset>
#include <cstring>
#include <iosfwd>

namespace eve
{
  template<typename T> struct logical
  {
    using value_type  = T;
    using mask_type   = T;
    using bits_type   = detail::as_integer_t<T, unsigned>;

    static constexpr bits_type true_mask  = ~bits_type{0};
    static constexpr bits_type false_mask = bits_type{0};

    template<typename U> using rebind = logical<U>;

    //==============================================================================================
    // Constructors
    //==============================================================================================
    EVE_FORCEINLINE constexpr logical() noexcept {}
    EVE_FORCEINLINE constexpr logical(bool v) noexcept : value_(v ? true_mask : false_mask) {}

    template<typename U>
    EVE_FORCEINLINE explicit constexpr logical(U const &v) noexcept
                  : value_((v != 0) ? true_mask : false_mask)
    {}

    //==============================================================================================
    // Assignment
    //==============================================================================================
    EVE_FORCEINLINE constexpr logical &operator=(logical v) & noexcept
    {
      value_ = v.value_;
      return *this;
    }

    EVE_FORCEINLINE constexpr logical &operator=(bool v) & noexcept
    {
      value_ = v ? true_mask : false_mask;
      return *this;
    }

    //==============================================================================================
    // Convertion from logical to other formats (mask, bits, bitmap)
    //==============================================================================================
    EVE_FORCEINLINE constexpr operator bool()   const noexcept { return !!value_; }
    EVE_FORCEINLINE constexpr bool value()      const noexcept { return !!value_; }
    EVE_FORCEINLINE constexpr bool not_value()  const noexcept { return !value_; }
    EVE_FORCEINLINE constexpr auto bitmap()     const noexcept { return std::bitset<1>(value_ & 1); }
    EVE_FORCEINLINE constexpr auto bits()       const noexcept { return value_; }

    EVE_FORCEINLINE constexpr auto mask() const noexcept
    {
      value_type that;
      std::memcpy(&that, &value_, sizeof(value_type));
      return that;
    }

    void swap( logical& other ) { std::swap(value_,other.value_); }

    //==============================================================================================
    // Stream insertion operator
    //==============================================================================================
    friend EVE_FORCEINLINE std::ostream &operator<<(std::ostream &os, logical const &v)
    {
      return os << (v.value_ ? "true" : "false");
    }

    private:
    bits_type value_;
  };

  template<typename T> EVE_FORCEINLINE void swap(logical<T> &lhs, logical<T> &rhs) noexcept
  {
    lhs.swap(rhs);
  }
}
