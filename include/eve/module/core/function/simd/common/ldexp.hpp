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
#include <eve/function/assert_utils.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_shl.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/multiplies.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/wide_cast.hpp>
#include <eve/constant/limitexponent.hpp>
#include <eve/constant/minexponent.hpp> 
#include <eve/constant/maxexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/tags.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(simd_),
                            wide<T, N, ABI> const &v0,
                            wide<U, N, ABI> const &v1) noexcept requires(wide<T, N, ABI>,
                                                           Floating_point<T>, Integral<U>)
  {
    if constexpr(std::is_integral<U>)
    {
      if constexpr(std::is_floating_point_v<T>())
      {
        using t_t = wide<T, N, ABI>;
        using i_t = as_integer_t<T>;
        auto ik =  v1+Maxexponent(as(T));
        ik = shift_left(ik, Nbmantissabits<T>());
        return a0*bitwise_cast<t_t>(ik);
      }
      else
      {
        return rshl(a0, a1);
      }
    }
    else
    {
      using wi_t = as_integer_t<wide<U, N, ABI>>;
      EVE_ASSERT_MSG(assert_all(is_flint(v1)), "[ ldexp ] : second parameter is not a flint");
      return ldexp(a0, wide_cast<wi_t>(v1));
    }
  }
  
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(simd_),
                              wide<T, N, ABI> const &v0,
                              U const &a1) noexcept requires(wide<T, N, ABI>,
                                                             Floating_point<T>, Integral<U>)
  {
    if constexpr(std::is_integral<U>)
    {
      if constexpr(std::is_floating_point_v<T>())
      {
        using i_t = as_integer_t<T>;
        auto ik =  a1+Maxexponent(as(T));
        ik = shift_left(ik, Nbmantissabits<T>());
        return a0*bitwise_cast<T>(ik);   
      }
      else
      {
        return rshl(a0, a1);
      }
    }
    else
    {
      using i_t = as_integer_t<U>;
      EVE_ASSERT_MSG(assert_all(is_flint(a1)), "[ ldexp ] : second parameter is not a flint");
      return ldexp(a0, static_cast<i_t>(a1));
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Support for mixed type with auto-splat
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(simd_),
                            wide<T, N, ABI> const &v0,
                            U const &              v1) noexcept requires(wide<T, N, ABI>,
                                                           detail::Convertible<U, T>)
  {
    return eve::ldexp(v0, wide<T, N, ABI>(static_cast<T>(v1)));
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(simd_),
                            U const &              v0,
                            wide<T, N, ABI> const &v1) noexcept requires(wide<T, N, ABI>,
                                                                         detail::Convertible<U, T>)
  {
    return eve::ldexp(wide<T, N, ABI>(static_cast<T>(v0)), v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, aggregated_> ldexp_(EVE_SUPPORTS(simd_),
                                               wide<T, N, aggregated_> const &v0,
                                               wide<T, N, aggregated_> const &v1) noexcept
  {
    return aggregate(eve::ldexp, v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation with auto-splat inside map for performance purpose
  template<typename T, typename N>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(simd_),
                            wide<T, N, emulated_> const &v0,
                            wide<T, N, emulated_> const &v1) noexcept
  {
    return map(eve::ldexp, v0, v1);
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(simd_),
                            wide<T, N, emulated_> const &v0,
                            U const &v1) noexcept requires(wide<T, N, emulated_>,
                                                           detail::Convertible<U, T>)
  {
    return map(eve::ldexp, v0, static_cast<T>(v1));
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto
  ldexp_(EVE_SUPPORTS(simd_),
       U const &                    v0,
       wide<T, N, emulated_> const &v1) noexcept requires(wide<T, N, emulated_>,
                                                          detail::Convertible<U, T>)
  {
    return map(eve::ldexp, static_cast<T>(v0), v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Pedantic
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(simd_),
                              pedantic_ const &, 
                              wide<T, N, ABI> const &v0,
                              wide<U, N, ABI> const &v1) noexcept requires(wide<T, N, ABI>,
                                                                           Floating_point<T>, Integral<U>)
  {
    if constexpr(std::is_integral<U>)
    {
      if constexpr(std::is_floating_point_v<T>())
      {
        using t_t = wide<T, N, ABI>;
        using i_t = as_integer_t<t_t>;
        i_t e = v1;  // ceci devrait être widecast<i_t>(a1); 
        t_t f = One<t_t>();
#ifndef EVE_NO_DENORMALS
        auto denormal =  is_less(e, Minexponent<t_t>());
        e = sub[denormal]( e, Minexponent<t_t>());
        f = if_else(denormal, Smallestposval<t_t>(), One<t_t>());
#endif
        auto test = is_equal(e, Limitexponent<t_t>());
        f = inc[test](f);
        e = dec[test](e);
        e += Maxexponent<t_t>();
        e = bitwise_shl(e, Nbmantissabits<T>());
        return a0*bitwise_cast<t_t>(e)*f;
      }
      else
      {
        return rshl(a0, a1);
      }
    }
    else
    {
      using i_t = as_integer_t<U>>;
      EVE_ASSERT_MSG(assert_all(is_flint(v1)), "[ ldexp ] : second parameter is not a flint");
      return ldexp[pedantic_](a0, wide_cast<wi_t>(v1, as<i_t>()));
    }
  }
  
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(simd_),
                              pedantic_ const &, 
                              wide<T, N, ABI> const &v0,
                              U const &a1) noexcept requires(wide<T, N, ABI>,
                                                             Floating_point<T>, Integral<U>)
  {
    if constexpr(std::is_integral<U>)
    {
      if constexpr(std::is_floating_point_v<T>())
      {
        using t_t = wide<T, N, ABI>;
        using i_t = as_integer_t<T>;
        i_t e = a1;
        t_t f = One<t_t>();
#ifndef BOOST_SIMD_NO_DENORMALS
        auto denormal =  is_less(e, Minexponent<T>());
        e = sub[denormal](e, Minexponent<T>());
        f = if_else(denormal, Smallestposval<t_t>(), One<t_t>());
#endif
        if (is_equal(e, Limitexponent<T>()))
        {
          f+= One<t_t>();
          e-= One<i_t>();
        }
        e += Maxexponent<T>();
        e = shift_left(e, Nbmantissabits<T>());
        return a0*(bitwise_cast<T>(e)*f);
      }
      else
      {
        return rshl(a0, a1);
      }
    }
    else
    {
      using i_t = as_integer_t<U>;
      EVE_ASSERT_MSG(assert_all(is_flint(v1)), "[ ldexp ] : second parameter is not a flint");
      return ldexp[pedantic_](a0, wide_cast(v1, as<i_t>()));
    }
  }
   
  // -----------------------------------------------------------------------------------------------
  // Support for mixed type with auto-splat
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(simd_),
                              pedantic_ const &, 
                              wide<T, N, ABI> const &v0,
                              U const &              v1) noexcept requires(wide<T, N, ABI>,
                                                                           detail::Convertible<U, T>)
  {
    return eve::ldexp(v0, wide<T, N, ABI>(static_cast<T>(v1)));
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(simd_),
                            pedantic_ const &, 
                            U const &              v0,
                            wide<T, N, ABI> const &v1) noexcept requires(wide<T, N, ABI>,
                                                                         detail::Convertible<U, T>)
  {
    return eve::ldexp(pedantic_, wide<T, N, ABI>(static_cast<T>(v0)), v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, aggregated_> ldexp_(EVE_SUPPORTS(simd_),
                                               wide<T, N, aggregated_> const &v0,
                                               wide<T, N, aggregated_> const &v1) noexcept
  {
    return aggregate(eve::ldexp, pedantic_, v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation with auto-splat inside map for performance purpose
  template<typename T, typename N>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(simd_),
                            pedantic_ const &, 
                            wide<T, N, emulated_> const &v0,
                            wide<T, N, emulated_> const &v1) noexcept
  {
    return map(eve::ldexp, pedantic_, v0, v1);
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(simd_),
                            pedantic_ const &, 
                            wide<T, N, emulated_> const &v0,
                            U const &v1) noexcept requires(wide<T, N, emulated_>,
                                                           detail::Convertible<U, T>)
  {
    return map(eve::ldexp, pedantic_, v0, static_cast<T>(v1));
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(simd_),
                            pedantic_ const &, 
       U const &                    v0,
       wide<T, N, emulated_> const &v1) noexcept requires(wide<T, N, emulated_>,
                                                          detail::Convertible<U, T>)
  {
    return map(eve::ldexp, pedantic_, static_cast<T>(v0), v1);
  }

  
}


#endif
