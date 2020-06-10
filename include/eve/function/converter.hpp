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

namespace eve
{
  //================================================================================================
  // Function decorators mark-up used in function overloads
  template <typename T>
  struct converter_type : decorator_
  {
    using value_type = T;
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
          return f(std::forward<Ts>(args)..., as_<T>());
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
}
