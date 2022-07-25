//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "find_backward_generic_test.hpp"

#include <eve/algo.hpp>

#include <algorithm>

TTS_CASE_TPL("Check find_if_backward", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::find_generic_backward_test(eve::as<T> {},
                                        eve::algo::find_if_backward,
                                        [](auto f, auto l, auto expected, auto actual)
                                        {
                                          TTS_EQUAL(actual - f, expected - f);
                                          if( actual != expected )
                                          {
                                            std::cout << tts::as_string(std::vector(f, l))
                                                      << std::endl;
                                            std::terminate();
                                          }
                                        });
};
