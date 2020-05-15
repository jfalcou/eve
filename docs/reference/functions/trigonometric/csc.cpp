<!--
  EVE -  Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 -->
<meta charset="utf-8" lang="en">
                       **Expressive Vector Engine**
                           `eve::cot`
<br>

  (insert ../../../crumbs.html here)

Synopsis
====================================================================================================
**Required header:** <script type="preformatted">`#include <eve/function/cot.hpp>`</script>

<script type="preformatted">
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
namespace eve
{
  inline constexpr /*unspecified*/ cot = /*unspecified*/;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
</script>
Function object representing the  computation of cot.

Member functions
====================================================================================================
<script type="preformatted">
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
template< floating_real_value T> auto operator()( T x ) const noexcept;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
</script>
Performs cosecant computation.

Parameters
----------------------------------------------------------------------------------------------------
`x`
:   [floating real value](../../concepts.html#value).

Return value
----------------------------------------------------------------------------------------------------
<span class="smallskip"></span>
Returns the [element-wise](../../../glossary.html#elment-wise) cosecant of the input.

In particular:

   * If the element is $\pm0$, $\pm\infty$ is returned.
   * If the element is $\pm\infty$, Nan is returned.
   * If the element is a `Nan`, `NaN` is returned.


Supported Decorators
====================================================================================================
As all direct trigonometric functions, `cot` supports the restricted_, small_, medium_ and big_ decorators. Click
to see the [properties and rationale](../trigonometric.html)

  (insert ../../src/cot.src.html here)

  (insert ../../out/cot.out.html here)

See Also
====================================================================================================
[eve::sin](sin.html), [eve::sincos](sincos.html), [eve::tan](tan.html), [eve::cot](cot.html),
[eve::cos](cos.html), [eve::sec](sec.html).

<!-- End of Document -->
<link rel="stylesheet" href="../../../eve.css">
<!-- Markdeep: -->
<script>markdeepOptions={tocStyle:'medium'};</script>
<script src="../../../markdeep.min.js"></script>
<script src="https://casual-effects.com/markdeep/latest/markdeep.min.js?"></script>
