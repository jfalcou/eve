//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup polynomial
  //! @{
  //! @var from_roots
  //!
  //! @brief Callable object computing the from_roots operation.
  //!
  //! **Required header:** `#include <eve/module/polynomial.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the from_roots operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(R const & roots) const noexcept;
  //!  auto operator()(floating_scalar_values rts...)
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! ---
  //!
  //! **Parameters**
  //!
  //!`roots`:  a range of floating scalar values (@ref eve::value).
  //!`rts`:  pack expansion of scalar values (@ref eve::value).
  //!
  //!
  //! **Return value**
  //!
  //! Returns a polynom<typename R::value_type> with leading coefficient 1, whose roots are given by the parameter(s) elements
  //!
  //! If the range is empty or the pack has no elements the polynomial is of degrree 0.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/polynomial/from_roots.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(from_roots_, from_roots);
}

#include <eve/module/polynomial/regular/impl/from_roots.hpp>
