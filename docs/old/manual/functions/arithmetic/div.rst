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
   template<typename T,typename U, typename TAG> auto operator()( T const& x, U const& y, TAG const & tag = toward_zero_) noexcept;  

[1] * Computes the element-wise division of two :ref:`Values <concept-value>`.
[2] * Computes the element-wise division of two :ref:`Values <concept-value>` with rounding.


Parameters
**********

* Each of the two first parameters ``x`` and ``y`` must be an instance of a :ref:`Value <concept-value>`.
* All  :ref:`concept-vectorized` parameters must share the same type
* If at least one parameter is  :ref:`concept-vectorized`, all  :ref:`concept-vectorizable` ones will be converted to 
  its base type prior any other computation.
* If all parameters are  :ref:`concept-vectorizable` they must share the same :ref:`Value <concept-value>` type.
* The third parameter ``tag`` (if present) can be ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest_``, fixing the 
  rounding mode. For :ref:`Integral Values <concept-integralvalue>` the parameter  default to ``toward_zero_``.

Return value
**************

* If any of the two first parameters is  :ref:`concept-vectorized`, a value of this type else a value of  
  the common type of the  :ref:`concept-vectorizable` parameters.


Notes
*******
  
  - with a rounding option ``div(x, y, tag)`` the function behaves as computing the floating division with
    infinite precision then applying the rounding option to return a properly typed value.

  - With the :ref:`saturated_ <feature-decorator>` decorator provides  the saturated operation.
  
  - Masked call is allowed: ``div[cond](x, y)`` is equivalent to ``if_else(cond, div(x, y), x)``

  - apart the above cases, infix notation can be used with operator ``/``. But be aware that for scalars `/`` 
    is the **C++** operator and it result is subject to automatic promotions.

Example
*******

.. include:: ../../../../test/doc/core/div.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/div.txt
  :literal:
