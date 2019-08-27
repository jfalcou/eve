//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IF_ELSE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IF_ELSE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Basic case
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_ ( EVE_SUPPORTS(cpu_),
                                            T const &cond, U const &t, U const &f
                                          ) noexcept
                  requires( U, Vectorizable<T> )
  {
    return static_cast<bool>(cond) ? t : f;
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,zero},{zero,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_ ( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            U const &t, eve::callable_zero_ const&
                                          ) noexcept
                  requires( U, Vectorizable<T>, Vectorizable<U> )
  {
    return static_cast<bool>(cond) ? t : U(0);
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_ ( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            eve::callable_zero_ const&, U const &t
                                          ) noexcept
                  requires( U, Vectorizable<T>, Vectorizable<U> )
  {
    return static_cast<bool>(cond) ?  U(0) : t;
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,allbits},{allbits,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_ ( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            U const &t, eve::callable_allbits_ const&
                                          ) noexcept
                  requires( U, Vectorizable<T>, Vectorizable<U> )
  {
    return static_cast<bool>(cond) ? t : Allbits(as(t));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_ ( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            eve::callable_allbits_ const&, U const &t
                                          ) noexcept
                  requires( U, Vectorizable<T>, Vectorizable<U> )
  {
    return static_cast<bool>(cond) ?  Allbits(as(t)) : t;
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,one},{one,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_ ( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            U const &t, eve::callable_one_ const&
                                          ) noexcept
                  requires( U, Vectorizable<T>, Vectorizable<U> )
  {
    return static_cast<bool>(cond) ? t : One(as(t));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_ ( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            eve::callable_one_ const&, U const &t
                                          ) noexcept
                  requires( U, Vectorizable<T>, Vectorizable<U> )
  {
    return static_cast<bool>(cond) ?  One(as(t)) : t;
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,mone},{mone,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_ ( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            U const &t, eve::callable_mone_ const&
                                          ) noexcept
                  requires( U, Vectorizable<T>, Vectorizable<U> )
  {
    return static_cast<bool>(cond) ? t : Mone(as(t));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_ ( EVE_SUPPORTS(cpu_),
                                            T const &cond,
                                            eve::callable_mone_ const&, U const &t
                                          ) noexcept
                  requires( U, Vectorizable<T>, Vectorizable<U> )
  {
    return static_cast<bool>(cond) ?  Mone(as(t)) : t;
  }
}

#endif
