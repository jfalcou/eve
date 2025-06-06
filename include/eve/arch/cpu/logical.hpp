//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/traits/as_integer.hpp>
#include <eve/traits/common_value.hpp>

#include <bitset>
#include <cstring>
#include <ostream>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief Wrapper for SIMD compatible logical types
  //!
  //! **Required header:** `#include <eve/logical.hpp>`
  //!
  //! eve::logical is an architecture-agnostic representation of a boolean mask and provides
  //! standardized API to access informations, compute values and manipulate such mask. Contrary
  //! to `bool`, an instance of logical has the same sizeof as `T`, allowing seamless interaction
  //! with an instance eve::logical<eve::wide< T >>.
  //!
  //! @tparam T  Type of value to store a mask from
  //================================================================================================
  template<plain_scalar_value T> struct logical<T>
  {
    //! The type associated to the boolean mask.
    using value_type  = T;

    //! The type representing the numerical value of mask.
    using mask_type   = T;

    //! The type representing the bitwise representation of the mask
    using bits_type   = as_integer_t<T, unsigned>;

    static constexpr bits_type true_mask  = ~bits_type{0};
    static constexpr bits_type false_mask = bits_type{0};

    template<typename U> using rebind = logical<U>;

    //==============================================================================================
    //! @name Constructors
    //! @{
    //==============================================================================================
    //! Default constructor
    EVE_FORCEINLINE constexpr logical() noexcept {}

    //! Construct from a `bool`
    EVE_FORCEINLINE constexpr logical(bool v) noexcept : value_(v ? true_mask : false_mask) {}

    //! Construct from a plain_scalar_value
    template<plain_scalar_value U>
    EVE_FORCEINLINE explicit constexpr logical(U const &v) noexcept
                  : value_((v != 0) ? true_mask : false_mask)
    {}
    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Assignment operators
    //! @{
    //==============================================================================================
    //! Assign a `bool`
    EVE_FORCEINLINE constexpr logical &operator=(bool v) & noexcept
    {
      value_ = v ? true_mask : false_mask;
      return *this;
    }
    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    // Logical operators
    //==============================================================================================
    EVE_FORCEINLINE constexpr logical operator!() const noexcept { return {!value_}; }

    template<arithmetic_scalar_value U>
    friend EVE_FORCEINLINE common_logical_t<T, U> operator&&(logical const& v, logical<U> const& w) noexcept
    {
      return common_logical_t<T, U>{v.value() && w.value()};
    }

    friend EVE_FORCEINLINE logical operator&&(logical const& v, bool const& w) noexcept
    {
      return w ? v : logical{false};
    }

    friend EVE_FORCEINLINE logical operator&&(bool const& v, logical const& w) noexcept
    {
      return v ? w : logical{false};
    }

    template<arithmetic_scalar_value U>
    friend EVE_FORCEINLINE common_logical_t<T, U> operator||(logical const& v, logical<U> const& w) noexcept
    {
      return common_logical_t<T, U>{v.value() || w.value()};
    }

    friend EVE_FORCEINLINE logical operator||(logical const& v, bool const& w) noexcept
    {
      return w ? logical{true} : v;
    }

    friend EVE_FORCEINLINE logical operator||(bool const& v, logical const& w) noexcept
    {
      return v ? logical{true} : w;
    }

    //==============================================================================================
    // Conversion from logical to other formats (mask, bits, bitmap)
    //==============================================================================================
    EVE_FORCEINLINE constexpr operator bool()   const noexcept { return !!value_; }
    EVE_FORCEINLINE constexpr bool value()      const noexcept { return !!value_; }
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
    // Comparison operators
    //==============================================================================================
    template<scalar_value U>
    friend EVE_FORCEINLINE common_logical_t<T, U> operator==(logical const& v, logical<U> const& w) noexcept
    {
      return common_logical_t<T, U>{v.value() == w.value()};
    }

    friend EVE_FORCEINLINE logical operator==(logical const& v, bool w) noexcept
    {
      return v.value() == w;
    }

    friend EVE_FORCEINLINE logical operator==(bool v, logical const& w) noexcept
    {
      return w.value() == v;
    }

    template<scalar_value U>
    friend EVE_FORCEINLINE common_logical_t<T, U> operator!=(logical const& v, logical<U> const& w) noexcept
    {
      return common_logical_t<T, U>{v.value() != w.value()};
    }

    friend EVE_FORCEINLINE logical operator!=(logical const& v, bool w) noexcept
    {
      return v.value() != w;
    }

    friend EVE_FORCEINLINE logical operator!=(bool v, logical const& w) noexcept
    {
      return w.value() != v;
    }

    friend EVE_FORCEINLINE void swap(logical &lhs, logical &rhs) noexcept
    {
      lhs.swap(rhs);
    }

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
  //================================================================================================
  //! @}
  //================================================================================================
}
