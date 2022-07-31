//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/traits/as_floating_point.hpp>

namespace eve
{
  //================================================================================================
  // Function decorator based on concrete type
  //================================================================================================
  template<scalar_value T> struct convert_to_
  {
    using value_type = element_type_t<T>;

    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;

    template<value Val>
    constexpr EVE_FORCEINLINE auto operator()(Val const & val) const noexcept
    {
      return convert(val, as<T>());
    }

    template<typename Function>
    EVE_FORCEINLINE constexpr  auto operator()(Function const & f) const noexcept
    {
      return  [f]<typename... Ts>(Ts&&... args)
      {
        if constexpr( supports_optimized_conversion<typename Function::tag_type>::value )
        {
          return f(decorated<convert_to_<T>()>(), EVE_FWD(args)...);
        }
        else
        {
          return convert(f(EVE_FWD(args)...), as<T>());
        }
      };
    }
  };

  //================================================================================================
  // Function decorator based on type transformation
  //================================================================================================
  template<template<class...> class Meta, bool isDirect = true> struct convert_by_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;

    template<value Val>
    constexpr EVE_FORCEINLINE auto operator()(Val const & val) const noexcept
    {
      using value_type = typename Meta<element_type_t<Val>>::type;
      return convert(val, as<value_type>());
    }

    template<typename Function>
    EVE_FORCEINLINE constexpr  auto operator()(Function const & f) const noexcept
    {
      return  [f]<typename T, typename... Ts>(T&& arg0, Ts&&... args)
      {
        using value_type = typename Meta<element_type_t<std::remove_cvref_t<T>>>::type;

        if constexpr( supports_optimized_conversion<typename Function::tag_type>::value )
        {
          if constexpr(isDirect)
          {
            return f( decorated<convert_to_<value_type>()>()
                    , EVE_FWD(arg0), EVE_FWD(args)...
                    );
          }
          else
          {
            return f( decorated<convert_by_<Meta,isDirect>()>()
                    , EVE_FWD(arg0), EVE_FWD(args)...
                    );
          }
        }
        else
        {
          return convert(f(EVE_FWD(arg0), EVE_FWD(args)...), as<value_type>());
        }
      };
    }
  };

  //================================================================================================
  // Function decorators for conversion
  //================================================================================================
  template<scalar_value T> using converter_type = decorated<convert_to_<T>()>;

  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //! @var float32
  //!
  //! @brief  convert a eve::value to a float32 based eve::floating_value.
  //!
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      as_wide_as<T, float> float32(T x) noexcept; //1
  //!
  //!      template< eve::callable C >
  //!      as_wide_as<T, float> float32(C x) noexcept; //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!   **Return value**
  //!
  //!     * if x is an eve::simd_value, returns a value, of type wide <float, cardinal_t<T>>,
  //!     * if x is an eve::scalar_value, returns a  value of type float,
  //!     * if x is a supported callable a call to float32(x)(...)
  //!     is semantically equivalent to float32(x(...)).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/float32.cpp}
  //!  @}
  //================================================================================================
  inline constexpr converter_type<float>              const float32  = {};

  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //! @var float64
  //!
  //! @brief  convert a eve::value to a double based eve::floating_value.
  //!
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      as_wide_as<T, double> float64(T x) noexcept; //1
  //!
  //!      template< eve::callable C >
  //!      as_wide_as<T, double> float64(C x) noexcept; //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!   **Return value**
  //!
  //!     * if x is an eve::simd_value, returns a value, of type wide <double, cardinal_t<T>>,
  //!     * if x is an eve::scalar_value, returns a  value of type double,
  //!     * if x is a supported callable a call to float64(x)(...)
  //!     is semantically equivalent to float64(x(...)).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/float64.cpp}
  //!  @}
  //================================================================================================
  inline constexpr converter_type<double>             const float64  = {};

  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //! @var uint8
  //!
  //! @brief  convert a eve::value to a std::uint8_t based eve::value.
  //!
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      as_wide_as<T, std::uint8_t> uint8(T x) noexcept; //1
  //!
  //!      template< eve::callable C >
  //!      as_wide_as<T, std::uint8_t> uint8(C x) noexcept; //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!   **Return value**
  //!
  //!     * if x is an eve::simd_value, returns a value, of type
  //!     wide <std::uint8_t, cardinal_t<T>>,
  //!     * if x is an eve::scalar_value, returns a  value of type std::uint8_t,
  //!     * if x is a supported callable a call to uint8(x)(...)
  //!     is semantically equivalent to uint8(x(...)).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/uint8.cpp}
  //!  @}
  //================================================================================================
  inline constexpr converter_type<std::uint8_t >      const uint8    = {};

  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //! @var uint16
  //!
  //! @brief  convert a eve::value to a std::uint16_t based eve::value.
  //!
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      as_wide_as<T, std::uint16_t> uint16(T x) noexcept; //1
  //!
  //!      template< eve::callable C >
  //!      as_wide_as<T, std::uint16_t> uint16(C x) noexcept; //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!   **Return value**
  //!
  //!     * if x is an eve::simd_value, returns a value,
  //!     of type wide <std::uint16_t, cardinal_t<T>>,
  //!     * if x is an eve::scalar_value, returns a  value of type std::uint16_t,
  //!     * if x is a supported callable a call to uint16(x)(...)
  //!     is semantically equivalent to uint16(x(...)).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/uint16.cpp}
  //!  @}
  //================================================================================================
  inline constexpr converter_type<std::uint16_t>      const uint16   = {};

  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //! @var uint32
  //!
  //! @brief  convert a eve::value to a std::uint32_t based eve::value.
  //!
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      as_wide_as<T, std::uint32_t> uint32(T x) noexcept; //1
  //!
  //!      template< eve::callable C >
  //!      as_wide_as<T, std::uint32_t> uint32(C x) noexcept; //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!   **Return value**
  //!
  //!     * if x is an eve::simd_value, returns a value,
  //!     of type wide <std::uint32_t, cardinal_t<T>>,
  //!     * if x is an eve::scalar_value, returns a  value of type std::uint32_t,
  //!     * if x is a supported callable a call to uint32(x)(...)
  //!     is semantically equivalent to uint32(x(...)).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/uint32.cpp}
  //!  @}
  //================================================================================================
  inline constexpr converter_type<std::uint32_t>      const uint32   = {};

  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //! @var uint64
  //!
  //! @brief  convert a eve::value to a std::uint64_t based eve::value.
  //!
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      as_wide_as<T, std::uint64_t> uint64(T x) noexcept; //1
  //!
  //!      template< eve::callable C >
  //!      as_wide_as<T, std::uint64_t> uint64(C x) noexcept; //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!   **Return value**
  //!
  //!     * if x is an eve::simd_value, returns a value,
  //!     of type wide <std::uint64_t, cardinal_t<T>>,
  //!     * if x is an eve::scalar_value, returns a  value of type std::uint64_t,
  //!     * if x is a supported callable a call to uint64(x)(...)
  //!     is semantically equivalent to uint64(x(...)).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/uint64.cpp}
  //!  @}
  //================================================================================================
  inline constexpr converter_type<std::uint64_t>      const uint64   = {};



  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //! @var int8
  //!
  //! @brief  convert a eve::value to a std::int8_t based eve::value.
  //!
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      as_wide_as<T, std::int8_t> int8(T x) noexcept; //1
  //!
  //!      template< eve::callable C >
  //!      as_wide_as<T, std::int8_t> int8(C x) noexcept; //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!   **Return value**
  //!
  //!     * if x is an eve::simd_value, returns a value, of type
  //!     wide <std::int8_t, cardinal_t<T>>,
  //!     * if x is an eve::scalar_value, returns a  value of type std::int8_t,
  //!     * if x is a supported callable a call to int8(x)(...)
  //!     is semantically equivalent to int8(x(...)).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/int8.cpp}
  //!  @}
  //================================================================================================
  inline constexpr converter_type<std::int8_t >      const int8    = {};

  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //! @var int16
  //!
  //! @brief  convert a eve::value to a std;::int16_t based eve::value.
  //!
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      as_wide_as<T, std::int16_t> int16(T x) noexcept; //1
  //!
  //!      template< eve::callable C >
  //!      as_wide_as<T, std::int16_t> int16(C x) noexcept; //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!   **Return value**
  //!
  //!     * if x is an eve::simd_value, returns a value,
  //!     of type wide <std::int16_t, cardinal_t<T>>,
  //!     * if x is an eve::scalar_value, returns a  value of type std::int16_t,
  //!     * if x is a supported callable a call to int16(x)(...)
  //!     is semantically equivalent to int16(x(...)).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/int16.cpp}
  //!  @}
  //================================================================================================
  inline constexpr converter_type<std::int16_t>      const int16   = {};

  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //! @var int32
  //!
  //! @brief  convert a eve::value to a std::int32_t based eve::value.
  //!
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      as_wide_as<T, std::int32_t> int32(T x) noexcept; //1
  //!
  //!      template< eve::callable C >
  //!      as_wide_as<T, std::int32_t> int32(C x) noexcept; //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!   **Return value**
  //!
  //!     * if x is an eve::simd_value, returns a value,
  //!     of type wide <std::int32_t, cardinal_t<T>>,
  //!     * if x is an eve::scalar_value, returns a  value of type std::int32_t,
  //!     * if x is a supported callable a call to int32(x)(...)
  //!     is semantically equivalent to int32(x(...)).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/int32.cpp}
  //!  @}
  //================================================================================================
  inline constexpr converter_type<std::int32_t>      const int32   = {};

  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //! @var int64
  //!
  //! @brief  convert a eve::value to a std::int64_t based eve::value.
  //!
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      as_wide_as<T, std::int64_t> int64(T x) noexcept; //1
  //!
  //!      template< eve::callable C >
  //!      as_wide_as<T, std::int64_t> int64(C x) noexcept; //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!   **Return value**
  //!
  //!     * if x is an eve::simd_value, returns a value,
  //!     of type wide <std::int64_t, cardinal_t<T>>,
  //!     * if x is an eve::scalar_value, returns a  value of type std::int64_t,
  //!     * if x is a supported callable a call to int64(x)(...)
  //!     is semantically equivalent to int64(x(...)).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/int64.cpp}
  //!  @}
  //================================================================================================
  inline constexpr converter_type<std::int64_t>      const int64   = {};

  template<typename T>
  inline constexpr converter_type<element_type_t<T>>  const to_ = {};

  using int_converter       = decorated<convert_by_<as_integer>()>;

  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //! @var int_
  //!
  //! @brief  convert a eve::value to a integral based eve::value.
  //!
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      as_wide_as<T, eve::as_integer_t<T>> int_(T x) noexcept; //1
  //!
  //!      template< eve::callable C >
  //!      as_wide_as<T, , eve::as_integer_t<T>> int_(C x) noexcept; //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!   **Return value**
  //!
  //!     * if x is an eve::simd_value, returns a value,
  //!       of type wide <std::i_t, cardinal_t<T>>,
  //!     * if x is an eve::scalar_value, returns a  value of type std::i_t,
  //!     * if x is a supported callable a call to int_(x)(...)
  //!       is semantically equivalent to int_(x(...)).
  //!
  //!     where i_t is eve::as_integral_t<eve::element_type_t<T>>
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/int_.cpp}
  //!  @}
  //================================================================================================
  inline constexpr int_converter      const int_      = {};

  using uint_converter      = decorated<convert_by_<as_uinteger>()>;
  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //! @var uint_
  //!
  //! @brief  convert a eve::value to a unsigned integral based eve::value.
  //!
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      as_wide_as<T, eve::as_integer_t<T, unsigned>> uint_(T x) noexcept; //1
  //!
  //!      template< eve::callable C >
  //!      as_wide_as<T, , eve::as_integer_t<T, unsigned>> uint_(C x) noexcept; //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!   **Return value**
  //!
  //!     * if x is an eve::simd_value, returns a value,
  //!       of type wide <std::i_t, cardinal_t<T>>,
  //!     * if x is an eve::scalar_value, returns a  value of type std::i_t,
  //!     * if x is a supported callable a call to uint_(x)(...)
  //!       is semantically equivalent to uint_(x(...)).
  //!
  //!     where i_t is eve::as_integral_t<eve::element_type_t<T, unsigned>>
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/int_.cpp}
  //!  @}
  //================================================================================================
  inline constexpr uint_converter     const uint_     = {};

  using floating_converter  = decorated<convert_by_<as_floating_point>()>;
  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //! @var floating_
  //!
  //! @brief  convert a eve::value to an eve::floating_value.
  //!
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      as_wide_as<T, eve::as_floating_point_t<T>> floating_(T x) noexcept; //1
  //!
  //!      template< eve::callable C >
  //!      as_wide_as<T, , eve::as_floating_point_t<T>> floating_(C x) noexcept; //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!   **Return value**
  //!
  //!     * if x is an eve::simd_value, returns a value,
  //!       of type wide <std::i_t, cardinal_t<T>>,
  //!     * if x is an eve::scalar_value, returns a  value of type std::i_t,
  //!     * if x is a supported callable a call to floating_(x)(...)
  //!       is semantically equivalent to floating_(x(...)).
  //!
  //!     where i_t is eve::as_floating_point_t<eve::element_type_t<T>>
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/floating_.cpp}
  //!  @}
  //================================================================================================
  inline constexpr floating_converter const floating_ = {};

  using upgrade_converter   = decorated<convert_by_<detail::upgrade,false>()>;
  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //! @var upgrade_
  //!
  //! @brief  convert a eve::value to the upgraded base type.
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      as_wide_as<T, eve::upgrade_t<T>> upgrade_(T x) noexcept; //1
  //!
  //!      template< eve::callable C >
  //!      as_wide_as<T, , eve::upgrade_t<T>> upgrade_(C x) noexcept; //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!   **Return value**
  //!
  //!     * if x is an eve::simd_value, returns a value of type wide <i_t, cardinal_t<T>>,
  //!     * if x is an eve::scalar_value, returns a value of type i_t
  //!     * if x is a supported callable a call to upgrade_(x)(...) is
  //!       semantically equivalent to upgrade__(x(...))
  //!
  //!     where u_t is eve::upgrade_t<eve::element_type_t<T>>
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/upgrade_.cpp}
  //!  @}
  //================================================================================================
  inline constexpr upgrade_converter  const upgrade_  = {};
}
