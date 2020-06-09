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
  // Function decorator - single mode
  template<typename Function> EVE_FORCEINLINE constexpr  auto single_(Function f) noexcept
  {
    return converter_type<float>{}(f);
  }
  //================================================================================================
  // Function decorator - double mode
  template<typename Function> EVE_FORCEINLINE constexpr  auto double_(Function f) noexcept
  {
    return converter_type<double>{}(f);
  }
  //================================================================================================
  // Function decorator - uint8 mode
  template<typename Function> EVE_FORCEINLINE constexpr  auto uint8_(Function f) noexcept
  {
    return converter_type<std::uint8_t>{}(f);
  }
  //================================================================================================
  // Function decorator - int8 mode
  template<typename Function> EVE_FORCEINLINE constexpr  auto int8_(Function f) noexcept
  {
    return converter_type<std::int8_t>{}(f);
  }
 //================================================================================================
  // Function decorator - uint16 mode
  template<typename Function> EVE_FORCEINLINE constexpr  auto uint16_(Function f) noexcept
  {
    return converter_type<std::uint16_t>{}(f);
  }
  //================================================================================================
  // Function decorator - int16 mode
  template<typename Function> EVE_FORCEINLINE constexpr  auto int16_(Function f) noexcept
  {
    return converter_type<std::int16_t>{}(f);
  }
 //================================================================================================
  // Function decorator - uint32 mode
  template<typename Function> EVE_FORCEINLINE constexpr  auto uint32_(Function f) noexcept
  {
    return converter_type<std::uint32_t>{}(f);
  }
  //================================================================================================
  // Function decorator - int32 mode
  template<typename Function> EVE_FORCEINLINE constexpr  auto int32_(Function f) noexcept
  {
    return converter_type<std::int32_t>{}(f);
  }
 //================================================================================================
  // Function decorator - uint64 mode
  template<typename Function> EVE_FORCEINLINE constexpr  auto uint64_(Function f) noexcept
  {
    return converter_type<std::uint64_t>{}(f);
  }
  //================================================================================================
  // Function decorator - int64 mode
  template<typename Function> EVE_FORCEINLINE constexpr  auto int64_(Function f) noexcept
  {
    return converter_type<std::int64_t>{}(f);
  }
}
