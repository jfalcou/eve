//==================================================================================================
/*
	EVE - Expressive Vector Engine
	Copyright : EVE Project Contributors
	SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <type_traits>

namespace eve
{
	// Default case: normal types do not have specific storage type
	template <typename T>
	struct translation_of {
		using type = T;
	};

	template <typename T>
	using translate_t = typename translation_of<T>::type;

	// Covers every enum
	template <typename T>
	requires (std::is_enum_v<T>)
	struct translation_of<T>: std::underlying_type<T>
	{ };
}
