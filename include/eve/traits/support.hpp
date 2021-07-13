//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/product_type.hpp>
#include <eve/function/add.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/div.hpp>
#include <eve/function/rem.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/is_not_equal.hpp>
#include <eve/function/if_else.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup struct
  //! @{
  //================================================================================================

  //==============================================================================================
  //! @brief Add supports for equality operators to product type like structures
  //! @tparam Type Type to adapt
  //==============================================================================================
  template<typename Type>
  struct comparable : supports<Type, tag::is_equal_, tag::is_not_equal_>
  {};

  //==============================================================================================
  //! @brief Add supports for if_else operator to product type like structures
  //! @tparam Type Type to adapt
  //==============================================================================================
  template<typename Type>
  struct selectable : supports<Type, tag::if_else_>
  {};

  //==============================================================================================
  //! @brief Add supports for additive operators to product type like structures
  //! @tparam Type Type to adapt
  //==============================================================================================
  template<typename Type>
  struct additive : supports<Type, tag::add_, tag::sub_>
  {};

  //==============================================================================================
  //! @brief Add supports for multiplicative operators to product type like structures
  //! @tparam Type Type to adapt
  //==============================================================================================
  template<typename Type>
  struct multiplicative : supports<Type, tag::mul_, tag::div_>
  {};

  //==============================================================================================
  //! @brief Imbue product type like structures with Euclidian ring compatible operators
  //! @tparam Type  Type to adapt
  //==============================================================================================
  template<typename Type>
  struct euclidian_ring : additive<Type>, multiplicative<Type>, supports<Type, tag::rem_>
  {};

  //==============================================================================================
  //! @brief Imbue product type like structures with ring compatible operators
  //! @tparam Type Type to adapt
  //==============================================================================================
  template<typename Type>
  struct ring : additive<Type>, supports<Type, tag::mul_>
  {};

  //==============================================================================================
  //! @brief Imbue product type like structures with field compatible operators
  //! @tparam Type Type to adapt
  //==============================================================================================
  template<typename Type>
  struct field : additive<Type>, multiplicative<Type>
  {};

  //================================================================================================
  //! @}
  //================================================================================================
}
