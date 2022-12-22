//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/algo/algo/concepts/detail.hpp>
#include <eve/module/algo/algo/concepts/relaxed.hpp>

#include <eve/module/algo/algo/views/zip.hpp>

#include <concepts>

namespace eve::algo
{
  template <typename ...Components>
  concept zip_to_range = requires (Components&& ... components) {
    { views::zip(EVE_FWD(components)...) } -> relaxed_range;
  };

  template <typename T>
  concept zipped_range = eve::detail::instance_of<std::remove_cvref_t<T>, views::zip_range>;

  template <typename T>
  concept zipped_range_pair = zipped_range<T> && (std::tuple_size_v<std::remove_cvref_t<T>> == 2);
}
