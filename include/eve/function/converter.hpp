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

#include <eve/function/convert.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>

namespace eve
{
  //================================================================================================
  // Function decorators mark-up used in function overloads
  template <typename T>
  struct converter_type : decorator_
  {
    using value_type = element_type_t<T>;
    template<value Val>
    constexpr EVE_FORCEINLINE auto operator()(Val const & val) const noexcept
    {
      return convert(val, as<T>());
    }
    template<typename Function>
    EVE_FORCEINLINE constexpr  auto operator()(Function f) const noexcept
    {
      return  [f]<typename... Ts>(Ts&&... args)
      {
        if constexpr( supports_optimized_conversion<typename Function::tag_type>::value )
        {
          return f(converter_type<T>(), std::forward<Ts>(args)...);
        }
        else
        {
          return convert(f(std::forward<Ts>(args)...), as_<T>());
        }
      };
    }
  };

  //================================================================================================
  // Function decorators for all basic type
  inline constexpr converter_type<float>          const single_   = {};
  inline constexpr converter_type<double>         const double_   = {};
  inline constexpr converter_type<std::uint8_t >  const uint8_    = {};
  inline constexpr converter_type<std::uint16_t>  const uint16_   = {};
  inline constexpr converter_type<std::uint32_t>  const uint32_   = {};
  inline constexpr converter_type<std::uint64_t>  const uint64_   = {};
  inline constexpr converter_type<std::int8_t >   const int8_     = {};
  inline constexpr converter_type<std::int16_t>   const int16_    = {};
  inline constexpr converter_type<std::int32_t>   const int32_    = {};
  inline constexpr converter_type<std::int64_t>   const int64_    = {};

  //================================================================================================
  // Function decorator for template conversion
  template<typename T>
  inline constexpr converter_type<T> const to_ = {};

  template<typename T>
  inline constexpr converter_type<element_type_t<T>> const to_elt = {};

  template<typename T>
  inline constexpr converter_type<detail::as_integer_t<element_type_t<T>, signed>> const toint_ = {};

  template<typename T>
  inline constexpr converter_type<detail::as_integer_t<element_type_t<T>, unsigned>> const touint_ = {};

  template<typename T>
  inline constexpr converter_type<detail::as_floating_point_t<element_type_t<T>>> const tofloating_ = {};


  //================================================================================================
  // Function saturated decorators mark-up used in function overloads
  template <typename T>
  struct s_converter_type : decorator_
  {
    using value_type = element_type_t<T>;
    template<value Val>
    constexpr EVE_FORCEINLINE auto operator()(Val const & val) const noexcept
    {
      return saturated_(convert)(val, as<T>());
    }
    template<typename Function>
    EVE_FORCEINLINE constexpr  auto operator()(Function f) const noexcept
    {
      return  [f]<typename... Ts>(Ts&&... args)
      {
        if constexpr( supports_optimized_conversion<typename Function::tag_type>::value )
        {
          return f(s_converter_type<T>(), std::forward<Ts>(args)...);
        }
        else
        {
          return saturated_(convert)(f(std::forward<Ts>(args)...), as_<T>());
        }
      };
    }
  };


  //================================================================================================
  // Function saturated decorators for all basic type
  inline constexpr converter_type<float>          const s_single_   = {};
  inline constexpr converter_type<double>         const s_double_   = {};
  inline constexpr converter_type<std::uint8_t >  const s_uint8_    = {};
  inline constexpr converter_type<std::uint16_t>  const s_uint16_   = {};
  inline constexpr converter_type<std::uint32_t>  const s_uint32_   = {};
  inline constexpr converter_type<std::uint64_t>  const s_uint64_   = {};
  inline constexpr converter_type<std::int8_t >   const s_int8_     = {};
  inline constexpr converter_type<std::int16_t>   const s_int16_    = {};
  inline constexpr converter_type<std::int32_t>   const s_int32_    = {};
  inline constexpr converter_type<std::int64_t>   const s_int64_    = {};

  //================================================================================================
  // Function decorator for template conversion
  template<typename T>
  inline constexpr s_converter_type<T> const to_ = {};

  template<typename T>
  inline constexpr s_converter_type<element_type_t<T>> const to_elt = {};

  template<typename T>
  inline constexpr s_converter_type<detail::as_integer_t<element_type_t<T>, signed>> const s_toint_ = {};

  template<typename T>
  inline constexpr s_converter_type<detail::as_integer_t<element_type_t<T>, unsigned>> const s_touint_ = {};

  template<typename T>
  inline constexpr s_converter_type<detail::as_floating_point_t<element_type_t<T>>> const s_tofloating_ = {};


}
