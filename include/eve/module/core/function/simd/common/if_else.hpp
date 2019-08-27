//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ELSE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ELSE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/bitwise_select.hpp>
#include <eve/function/bitwise_andnot.hpp>
#include <eve/function/bitwise_ornot.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/bitwise_or.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/ext/as_wide.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Basic case
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE constexpr auto  if_else_( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            U const &t, V const &f
                                          ) noexcept
    requires( std::conditional_t<is_vectorized_v<U>, U, V>,
              Vectorized<T>,
              detail::Either<is_vectorized_v<U>, is_vectorized_v<V>>,
              HasCompatibleCardinal<typename T::cardinal_type,U,V>
            )
  {
    auto cond_mask = bitwise_mask(cond);
    return bitwise_select( cond_mask, t, f);
  }

  //------------------------------------------------------------------------------------------------
  // Logical case
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE constexpr auto  if_else_( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            logical<U> const &t, logical<V> const &f
                                          ) noexcept
    requires( std::conditional_t<is_vectorized_v<U>, logical<U>, logical<V>>,
              Vectorized<T>,
              detail::Either<is_vectorized_v<U>, is_vectorized_v<V>>,
              HasCompatibleCardinal<typename T::cardinal_type,U,V>
            )
  {
    using t_t = std::conditional_t<is_vectorized_v<U>, logical<U>, logical<V>>;
    auto cond_mask = bitwise_mask(cond);
    return bitwise_cast<t_t>(bitwise_select( cond_mask, t.mask(), f.mask()));
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,zero},{zero,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto  if_else_( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            U const& t,
                                            eve::callable_zero_ const&
                                          ) noexcept
    requires( U, Vectorized<T>, Vectorized<U>,
              HasCompatibleCardinal<typename T::cardinal_type,U>
            )
  {
    return bitwise_and(t, bitwise_mask(cond));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto  if_else_( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            eve::callable_zero_ const&,
                                            U const& t
                                          ) noexcept
    requires( U, Vectorized<T>, Vectorized<U>,
              HasCompatibleCardinal<typename T::cardinal_type,U>
            )
  {
    return bitwise_andnot(t, bitwise_mask(cond));
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,allbits},{allbits,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto  if_else_( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            U const& t,
                                            eve::callable_allbits_ const&
                                          ) noexcept
    requires( U, Vectorized<T>, Vectorized<U>,
              HasCompatibleCardinal<typename T::cardinal_type,U>
            )
  {
    return bitwise_ornot(t, bitwise_mask(cond));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto  if_else_( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            eve::callable_allbits_ const&,
                                            U const& t
                                          ) noexcept
    requires( U, Vectorized<T>, Vectorized<U>,
              HasCompatibleCardinal<typename T::cardinal_type,U>
            )
  {
    return bitwise_or(t, bitwise_mask(cond));
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,one},{one,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto  if_else_( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            U const& t,
                                            eve::callable_one_ const&
                                          ) noexcept
    requires( U, Vectorized<T>, Vectorized<U>,
              HasCompatibleCardinal<typename T::cardinal_type,U>
            )
  {
    if constexpr(std::is_integral_v<U>)
    {
      return  unary_minus(bitwise_ornot(unary_minus(t),bitwise_mask(cond)));
    }
    else
    {
      return  if_else(cond,t,eve::One<U>());
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto  if_else_( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            eve::callable_one_ const&,
                                            U const& t
                                          ) noexcept
    requires( U, Vectorized<T>, Vectorized<U>,
              HasCompatibleCardinal<typename T::cardinal_type,U>
            )
  {
    if constexpr(std::is_integral_v<U>)
    {
      return unary_minus(bitwise_or(unary_minus(t),bitwise_mask(cond)));
    }
    else
    {
      return if_else(cond,eve::One<U>(),t);
    }
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,mone},{mone,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto  if_else_( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            U const& t,
                                            eve::callable_mone_ const&
                                          ) noexcept
    requires( U, Vectorized<T>, Vectorized<U>,
              HasCompatibleCardinal<typename T::cardinal_type,U>
            )
  {
    if constexpr(std::is_integral_v<U>)
    {
      return bitwise_ornot(t,bitwise_mask(cond));
    }
    else
    {
      return  if_else(cond,t,eve::Mone<U>());
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto  if_else_( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            eve::callable_mone_ const&,
                                            U const& t
                                          ) noexcept
    requires( U, Vectorized<T>, Vectorized<U>,
              HasCompatibleCardinal<typename T::cardinal_type,U>
            )
  {
    if constexpr(std::is_integral_v<U>)
    {
      return bitwise_or(t,bitwise_mask(cond));
    }
    else
    {
      return if_else(cond,eve::Mone<U>(),t);
    }
  }
}

#endif
