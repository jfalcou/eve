//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/mzero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>
#include <limits>

#if defined(EVE_COMP_IS_MSVC)
#  pragma warning(push)
#  pragma warning(disable : 4723) // 1/0 is OK for this test
#endif

TTS_CASE_TPL("Check mzero return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::Mzero<T>(), T);
}

TTS_CASE_TPL("Check mzero behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(T(1) / eve::Mzero<T>(), T(-std::numeric_limits<v_t>::infinity()) );
}

#if defined(EVE_COMP_IS_MSVC)
#  pragma warning(pop)
#endif
