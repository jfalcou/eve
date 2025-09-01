//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/traits/as_wide.hpp>
#include <algorithm>

namespace eve
{
  namespace detail
  {
    // SIMD/* drive case
    // Equality of sizeof of type/element_type is enough
    template<typename T0, typename T1>
    static constexpr inline bool bit_compatibility = false;

    template<simd_value T0, simd_value T1>
    static constexpr inline bool
    bit_compatibility<T0,T1>  = T0::size() * sizeof(element_type_t<T0>) == T1::size() * sizeof(element_type_t<T1>);

    template<simd_value T0, scalar_value T1>
    static constexpr inline bool bit_compatibility<T0,T1> = sizeof(T1) == sizeof(element_type_t<T0>);

    // SIMD/* case
    // Finding the proper size of the proper wide able to represent all the values
    // in a bitwise call without losing bits requires a global analysis of all Type x Cardinal
    // combination. This is an helper function to handle this logic.
    template<typename T0, typename... Ts>
    constexpr auto adequate_size()
    {
      struct result
      {
        std::ptrdiff_t size;
        bool is_scalar;
      };

      // We compare to at least one SIMD
      if constexpr((simd_value<Ts> || ... ))
      {
        // We compute the list of actual size of Ts...
        // 0 means it's a scalar and will be skipped
        // anything else is the # of bytes the wide logically represents
        auto size_of = []<typename T>(eve::as<T>) -> std::ptrdiff_t
        {
            if constexpr(simd_value<T>) return T::alignment();
            else                        return sizeof(T0) == sizeof(T) ? 0 : -1;
        };

        std::ptrdiff_t size[] = { size_of(eve::as<Ts>{})... };

        // Find first non-scalar wide if possible
        auto first_wide = [&]()
        {
            for(auto s : size) { if(s>0) return s; }
            return std::ptrdiff_t{0};
        }();

        // Verify all wides give a compatible type as bitwise mask
        // Return -1 if not the case
        for(auto s : size)
        {
            if(s==-1 ||(s!=0 && s!=first_wide))
                return result{-1,false};
        }

        // Everything is OK, get the proper size
        return result{first_wide,false};
      }
      else
      {
        // All scalar sizeof must be equal or we signify a mistake
        return ((sizeof(T0) == sizeof(Ts)) && ... ) ? result{static_cast<std::ptrdiff_t>(sizeof(T0)),true}
                                                    : result{-1,true};
      }
    }
  }

  template<typename... Ts>
  struct bit_value;

  template<scalar_value T0, value... Ts>
  requires( detail::adequate_size<T0,Ts...>().size != -1 )
  struct bit_value<T0,Ts...>
  {
    static constexpr auto sz = detail::adequate_size<T0,Ts...>();
    using type  = detail::conditional_t< sz.is_scalar
                                    , T0
                                    , as_wide_t<T0, fixed<sz.size / sizeof(T0)>>
                                    >;
  };

  template<simd_value T0, value... Ts>
  requires( (detail::bit_compatibility<T0,Ts>) && ... )
  struct bit_value<T0,Ts...>
  {
    using type = T0;
  };

  template<typename... Ts>
  using bit_value_t = typename bit_value<Ts...>::type;

  template<typename... Ts>
  concept supports_bitwise_call = requires { typename bit_value<Ts...>::type; };
}
