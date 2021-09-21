//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/concepts/detail.hpp>
#include <eve/algo/concepts/relaxed.hpp>

#include <eve/algo/zip.hpp>

#include <concepts>

namespace eve::algo
{
  template <typename ...Components>
  concept zip_to_range = requires (Components&& ... components) {
    { zip(std::forward<Components>(components)...) } -> relaxed_range;
  };

  template <typename T>
  concept zipped_range = detail::instance_of<std::remove_cvref_t<T>, zip_range>;

  template <typename T>
  concept zipped_range_pair = zipped_range<T> && (std::tuple_size_v<std::remove_cvref_t<T>> == 2);
}
