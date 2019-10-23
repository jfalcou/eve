//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2019 Jean-Thierry LAPRESTE
   Copyright 2019 Joel FALCOU
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LDEXP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LDEXP_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/function/all.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_shl.hpp>
#include <eve/function/all.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/rshl.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/convert.hpp>
#include <eve/constant/limitexponent.hpp>
#include <eve/constant/minexponent.hpp> 
#include <eve/constant/maxexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/forward.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve::detail
{

  // -----------------------------------------------------------------------------------------------
  // regular case
  template<typename T, typename U>
  EVE_FORCEINLINE  auto ldexp_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires( T, vectorized<T>, behave_as<floating_point, T>, compatible<T, U>)
  {
    using t_abi = abi_type_t<T>;

    if constexpr( is_vectorizable_v<U>) // U is scalar
    {
      if constexpr( is_emulated_v<t_abi>)
      {
        return map( eve::ldexp, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
      }
      else if constexpr( is_aggregated_v<t_abi>)
      {
        return aggregate( eve::ldexp, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
      }
      else
      {
        if constexpr(std::is_integral_v<U>)
        {
          using t_t = value_type_t<T>;
          using i_t = detail::as_integer_t<t_t, signed>; 
          i_t ik =  b+Maxexponent<t_t>();
          ik = shl(ik, Nbmantissabits<t_t>());
          return a*bitwise_cast(ik, as<t_t>());
        } 
        else  // U is floating point
        {
          using t_t = value_type_t<T>;
          using i_t =  detail::as_integer_t<t_t, signed>; 
          return ldexp(a, i_t(trunc(b)));
        }
      }
    }
    else // constexpr( is_vectorized_v<U>)
    {
      using u_abi = abi_type_t<U>;
      if constexpr( is_emulated_v<t_abi> || is_emulated_v<u_abi> )
      {
        return map( eve::ldexp, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
      }
      else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
      {
        return aggregate( eve::ldexp, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
      }
      else 
      {
        if constexpr(std::is_integral_v<value_type_t<U>>)
        {
          using t_t = value_type_t<T>; 
          using i_t = as_integer_t<t_t, signed>;
          auto ik =  convert(b, as<i_t>())+Maxexponent<t_t>();
          ik = shl(ik, Nbmantissabits<t_t>());
          return a*bitwise_cast(ik, as<T>());
        }
        else // U is vector of floating
        {
          using t_t = value_type_t<T>; 
          using i_t = as_integer_t<t_t, signed>;
          return ldexp(a, convert(trunc(b), as<i_t>())); 
        }
      }
    }
  }
  
  // -----------------------------------------------------------------------------------------------
  // pedantic case
  template<typename T, typename U>
  EVE_FORCEINLINE  auto ldexp_(EVE_SUPPORTS(cpu_)
                            , pedantic_type const & pdt 
                            , T const &a
                            , U const &b) noexcept
  requires( T, vectorized<T>, behave_as<floating_point, T>, compatible<T, U>)
  {
    using t_abi = abi_type_t<T>;

    if constexpr( is_vectorizable_v<U>) // U is scalar
    {
      if constexpr( is_emulated_v<t_abi>)
      {
        return map( eve::ldexp, pdt, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
      }
      else if constexpr( is_aggregated_v<t_abi>)
      {
        return aggregate( eve::ldexp, pdt, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
      }
      else
      {
        if constexpr(std::is_integral_v<U>)
        {
          using t_t = value_type_t<T>; 
          using i_t = detail::as_integer_t<t_t, signed>; 
          i_t ik =  b+Maxexponent<t_t>();
          i_t e = b;  
          auto f = One<T>();
          if constexpr( eve::platform::supports_denormals)
          {
            auto denormal =  is_less(e, Minexponent<t_t>());
            e = sub[denormal]( e, Minexponent<t_t>());
            f = if_else(denormal, Smallestposval<t_t>(), One<t_t>());
          }
          auto test = is_equal(e, Limitexponent<t_t>());
          f = inc[test](f);
          e = dec[test](e);
          e += Maxexponent<t_t>();
          e = bitwise_shl(e, Nbmantissabits<T>());
          return b*bitwise_cast(e, as(t_t()))*f;
        }
        else  // U is floating point
        {
          using i_t =  detail::as_integer_t<U, signed>; 
          return pedantic_(ldexp)(a, convert(trunc(b), as<i_t>())); 
        }
      }
    }
    else // constexpr( is_vectorized_v<U>)
    {
      using u_abi = abi_type_t<U>;
      if constexpr( is_emulated_v<t_abi> || is_emulated_v<u_abi> )
      {
        return map( eve::ldexp, pdt, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
      }
      else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
      {
        return aggregate( eve::ldexp, pdt, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
      }
      else 
      {
        if constexpr(std::is_integral_v<value_type_t<U>>)
        {
          using t_t = value_type_t<T>; 
          using i_t = as_integer_t<t_t, signed>;
          auto e = convert(b, as<i_t>()); 
          auto f = One<T>();
          if constexpr( eve::platform::supports_denormals)
          {
            auto denormal =  is_less(e, Minexponent<t_t>());
            e = sub[denormal]( e, Minexponent<t_t>());
            f = if_else(denormal, Smallestposval<t_t>(), One<t_t>());
          }
          auto test = is_equal(e, Limitexponent<t_t>());
          f = inc[test](f);
          e = dec[test](e);
          e += Maxexponent<t_t>();
          e = bitwise_shl(e, Nbmantissabits<t_t>());
          return b*bitwise_cast(e, as(t_t()))*f;
          
          auto ik =  convert(b, as<i_t>())+Maxexponent<t_t>();
          ik = shl(ik, Nbmantissabits<t_t>());
          return b*bitwise_cast(ik, as<T>());
        }
        else // U is vector of floating
        {
          using t_t = value_type_t<T>; 
          using i_t = as_integer_t<t_t, signed>;
          return pedantic_(ldexp)(a, convert(trunc(b), as<i_t>())); 
        }
      }
    }
  }
}


#endif
