.. _function-div:

###
div
###

**Required header:** ``#include <eve/function/div.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ div = {};
   }

Function object computing the division of two :ref:`Values <concept-value>`, optionally with rounding.

Synopsis
********

.. code-block:: c++

   template<typename T,typename U>               auto operator()( T const& x, U const& y ) noexcept;
   template<typename T,typename U, typename TAG> auto operator()( T const& x, U const& y, TAG const & ) noexcept;  

[1] * Computes the element-wise division of two :ref:`Values <concept-value>`.
[2] * Computes the element-wise division of two :ref:`Values <concept-value>` with rounding.


Parameters
**********

* Each of the two first parameters must be an instance of :ref:`Value <concept-value>`.
* All  :ref:`concept-vectorized` parameters must share the same type
* If at least one parameter is  :ref:`concept-vectorized`, all  :ref:`concept-vectorizable` ones will be converted to 
  its base type prior any other computation.
* If all parameters are  :ref:`concept-vectorizable` they must share the same :ref:`Value <concept-ieeevalue>` type.
* The third parameter type (if present) can be ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest_``, fixing the 
  rounding mode. For :ref:`Integral Values <concept-integralvalue>` the parameter rounding default to ``toward_zero_``.

Return value
**************

* If any of the two first parameters is  :ref:`concept-vectorized`, a value of this type else a value of  
  the common type of the  :ref:`concept-vectorizable` parameters.


Options
*******
  
  - with a rounding option ``div[cond](x, y, TAG())`` the function behaves as computing the floating division with
    infinite precision then applying the rounding option to return a properly typed value.

  - With :ref:`saturated_ <feature-decorator>` decorator provides  the saturated operation.
  
  - Masked call is allowed: ``div[cond](x, y)`` is equivalent to ``if_else(cond, div(x, y), x)``

  - apart the above cases, infix notation can be used with operator ``/``. But be aware that for scalars `/`` 
    is the C++ operator and it result is subject to automatic promotions.

Example
*******

.. include:: ../../../../test/doc/core/div.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/div.txt
  :literal:
