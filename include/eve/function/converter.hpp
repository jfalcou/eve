//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/convert.hpp>
#include <eve/function/saturated.hpp>
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
          return f(decorated<convert_to_<T>()>(), std::forward<Ts>(args)...);
        }
        else
        {
          return convert(f(std::forward<Ts>(args)...), as<T>());
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
                    , std::forward<T>(arg0), std::forward<Ts>(args)...
                    );
          }
          else
          {
            return f( decorated<convert_by_<Meta,isDirect>()>()
                    , std::forward<T>(arg0), std::forward<Ts>(args)...
                    );
          }
        }
        else
        {
          return convert(f(std::forward<T>(arg0), std::forward<Ts>(args)...), as<value_type>());
        }
      };
    }
  };

  //================================================================================================
  // Function decorators for conversion
  //================================================================================================
  template<scalar_value T> using converter_type = decorated<convert_to_<T>()>;

  inline constexpr converter_type<float>              const float32  = {};
  inline constexpr converter_type<double>             const float64  = {};
  inline constexpr converter_type<std::uint8_t >      const uint8    = {};
  inline constexpr converter_type<std::uint16_t>      const uint16   = {};
  inline constexpr converter_type<std::uint32_t>      const uint32   = {};
  inline constexpr converter_type<std::uint64_t>      const uint64   = {};
  inline constexpr converter_type<std::int8_t >       const int8     = {};
  inline constexpr converter_type<std::int16_t>       const int16    = {};
  inline constexpr converter_type<std::int32_t>       const int32    = {};
  inline constexpr converter_type<std::int64_t>       const int64    = {};

  template<typename T>
  inline constexpr converter_type<element_type_t<T>>  const to_ = {};

  using int_converter       = decorated<convert_by_<as_integer>()>;
  using uint_converter      = decorated<convert_by_<as_uinteger>()>;
  using floating_converter  = decorated<convert_by_<as_floating_point>()>;
  using upgrade_converter   = decorated<convert_by_<detail::upgrade,false>()>;

  inline constexpr int_converter      const int_      = {};
  inline constexpr uint_converter     const uint_     = {};
  inline constexpr floating_converter const floating_ = {};
  inline constexpr upgrade_converter  const upgrade_  = {};
}
