//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE_TPL( "Check enumerating constructor for arithmetic wide", EVE_TYPE )
{
  T ref;
  for(int i=0;i<EVE_CARDINAL;++i)
    ref.set(i, EVE_VALUE(i + 1) );

  T simd  = [&]<std::size_t... N>(std::index_sequence<N...>)
            {
              return T{(1+N)...};
            }( std::make_index_sequence<EVE_CARDINAL>());

  TTS_EQUAL(simd, ref);
}

TTS_CASE_TPL("Check enumerating constructor for wide of logical", EVE_TYPE)
{
  eve::logical<T> ref{false};
  for(int i=0;i<EVE_CARDINAL;++i)
    ref.set(i,i % 3 == 0);

  eve::logical<T> simd  = [&]<std::size_t... N>(std::index_sequence<N...>)
                          {
                            return eve::logical<T>{(N%3 == 0)...};
                          }( std::make_index_sequence<EVE_CARDINAL>());

  TTS_EQUAL(simd, ref);
}
