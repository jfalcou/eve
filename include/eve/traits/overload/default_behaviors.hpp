//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/as_element.hpp>
#include <eve/forward.hpp>
#include <eve/detail/overload.hpp>  // TEMPORARY

#include <eve/traits/overload/impl/callable.hpp>
#include <eve/traits/overload/impl/relative_conditional.hpp>
#include <eve/traits/overload/impl/conditional.hpp>
#include <eve/traits/overload/impl/strict_elementwise.hpp>
#include <eve/traits/overload/impl/elementwise.hpp>
#include <eve/traits/overload/impl/constant.hpp>
#include <eve/traits/overload/impl/tuple.hpp>
#include <eve/traits/overload/impl/strict_tuple.hpp>
