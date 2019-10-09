//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_LDEXP_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_LDEXP_HPP_INCLUDED

#include <eve/detail/overload.hpp>  
#include <eve/function/is_flint.hpp>
#include <eve/function/all.hpp> 

namespace eve
{
  namespace tag { struct ldexp_; }

  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_SUPPORTS(eve::tag::ldexp_), T const&, U const& b)
    {
      if constexpr(is_vectorized_v<U> && is_vectorized_v<T>)
        if constexpr (U::cardinal_type::value != T::cardinal_type::value)
          static_assert(U::cardinal_type::value != T::cardinal_type::value, "[eve::ldexp] - no support for current simd api"); 
      static_assert(std::is_floating_point_v<value_type_t<T>>, "[eve::ldexp] first parameter must be floating point");
      if constexpr(std::is_floating_point_v<value_type_t<U>>)
        EVE_ASSERT(all(is_flint(b)), "[eve::ldexp] argument 2 is floating but not a flint");
    }
    
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_SUPPORTS(eve::tag::ldexp_), pedantic_type const&, T const&, U const& b)
    {
      if constexpr(is_vectorized_v<U> && is_vectorized_v<T>)
        if constexpr (U::cardinal_type::value != T::cardinal_type::value)
          static_assert(U::cardinal_type::value != T::cardinal_type::value, "[eve::ldexp] - no support for current simd api"); 
      static_assert(std::is_floating_point_v<value_type_t<T>>, "ldexp first parameter must be floating point");
      if constexpr(std::is_floating_point_v<value_type_t<U>>)
        EVE_ASSERT(all(is_flint(b)), "ldexp argument 2 is floating but not a flint");
    }
  }

  EVE_MAKE_CALLABLE(ldexp_, ldexp);
}

#endif
