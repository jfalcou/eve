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
#include <eve/function/saturated.hpp>
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
    EVE_FORCEINLINE constexpr  auto operator()(Function const & f) const noexcept
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
  inline constexpr converter_type<element_type_t<T>> const to_ = {};

  struct int_converter
  {
    template<value Val>
    constexpr EVE_FORCEINLINE auto operator()(Val const & val) const noexcept
    {
      using value_type = detail::as_integer_t<element_type_t<Val>>;
      return convert(val, as<value_type>());
    }

    template<typename Function>
    EVE_FORCEINLINE constexpr  auto operator()(Function const & f) const noexcept
    {
      return  [f]<typename T, typename... Ts>(T&& arg0, Ts&&... args)
      {
        using value_type = detail::as_integer_t<element_type_t<std::remove_cvref_t<T>>>;

        if constexpr( supports_optimized_conversion<typename Function::tag_type>::value )
        {
          return f(converter_type<value_type>(), std::forward<T>(arg0), std::forward<Ts>(args)...);
        }
        else
        {
          return convert(f(std::forward<T>(arg0), std::forward<Ts>(args)...), as_<value_type>());
        }
      };
    }
  };

  inline constexpr int_converter const int_ = {};

  struct uint_converter
  {
    template<value Val>
    constexpr EVE_FORCEINLINE auto operator()(Val const & val) const noexcept
    {
      using value_type = detail::as_integer_t<element_type_t<Val>, unsigned>;
      return convert(val, as<value_type>());
    }

    template<typename Function>
    EVE_FORCEINLINE constexpr  auto operator()(Function const & f) const noexcept
    {
      return  [f]<typename T, typename... Ts>(T&& arg0, Ts&&... args)
      {
        using value_type = detail::as_integer_t<element_type_t<std::remove_cvref_t<T>>, unsigned>;

        if constexpr( supports_optimized_conversion<typename Function::tag_type>::value )
        {
          return f(converter_type<value_type>(), std::forward<T>(arg0), std::forward<Ts>(args)...);
        }
        else
        {
          return convert(f(std::forward<T>(arg0), std::forward<Ts>(args)...), as_<value_type>());
        }
      };
    }
  };

  inline constexpr uint_converter const uint_ = {};

  struct floating_converter
  {
    template<value Val>
    constexpr EVE_FORCEINLINE auto operator()(Val const & val) const noexcept
    {
      using value_type = detail::as_floating_point_t<element_type_t<Val>>;
      return convert(val, as<value_type>());
    }

    template<typename Function>
    EVE_FORCEINLINE constexpr  auto operator()(Function const & f) const noexcept
    {
      return  [f]<typename T, typename... Ts>(T&& arg0, Ts&&... args)
      {
        using value_type = detail::as_floating_point_t<element_type_t<std::remove_cvref_t<T>>>;

        if constexpr( supports_optimized_conversion<typename Function::tag_type>::value )
        {
          return f(converter_type<value_type>(), std::forward<T>(arg0), std::forward<Ts>(args)...);
        }
        else
        {
          return convert(f(std::forward<T>(arg0), std::forward<Ts>(args)...), as_<value_type>());
        }
      };
    }
  };

  inline constexpr floating_converter const floating_ = {};

}
