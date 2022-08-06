//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/detail/wide_forward.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core
  //! @{
  //================================================================================================

  //================================================================================================
  //! @concept conditional_expr
  //! @brief Specifies that a type is a Conditional Expression
  //!
  //! Types modeling eve::conditional_expr supports optimisation when evaluated where a logical
  //! value was expected.
  //!
  //! @groupheader{Examples}
  //!   - eve::if_
  //!   - eve::ignore_all
  //================================================================================================
  template<typename T> concept conditional_expr = requires(T a)
  {
    { T::has_alternative  };
    { T::is_inverted      };
    { T::is_complete      };
  };

  //================================================================================================
  //! @concept relative_conditional_expr
  //! @brief Specifies that a type is a Conditional Expression using relative mask
  //!
  //! Types modeling relative_conditional_expr are eve::conditional_expr that represents masks
  //! based on relative position of lanes. They provide an API to query the layout of lanes to
  //! ignore.
  //!
  //! @groupheader{Examples}
  //!   - eve::ignore_first
  //!   - eve::keep_between
  //================================================================================================
  template<typename T> concept relative_conditional_expr = conditional_expr<T> && requires(T a)
  {
    { a.count(eve::as<eve::wide<int>>())  };
    { a.offset(eve::as<eve::wide<int>>()) };
    { a.roffset(eve::as<eve::wide<int>>()) };
  };

  //================================================================================================
  //! @}
  //================================================================================================
}
