.. _function-max:

###
max
###

**Required header:** ``#include <eve/function/max.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ max = {};
   }

Function object computing the maximum of two :ref:`Values <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> auto operator()( T const& x, U const& y ) noexcept;

* Computes the element-wise maximum of two :ref:`Values <concept-value>`.

Parameters
**********

* Each parameter ``x`` and ``y`` must be an instance of a :ref:`Value <concept-value>`.
* All  :ref:`concept-vectorized` parameters must share the same type
* If at least one parameter is  :ref:`concept-vectorized`, all  :ref:`concept-vectorizable` ones will be converted to 
  its base type prior any other computation.
* If all parameters are  :ref:`concept-vectorizable` they must share the same :ref:`Value <concept-value>` type.

Return value
**************

* If any parameter is  :ref:`concept-vectorized`, a value of this type else a value of  
  the common type of the  :ref:`concept-vectorizable` parameters.

Note
*******

     With :ref:`concept-ieeevalue` parameters, there is three ways to call ``max``:

     * With a regular call,  in which case if an element of ``x`` or ``y`` is a nan, the result is system dependent as on various systems
       the existing intrinsics can act in different ways;

     * With the :ref:`pedantic_ <feature-decorator>` decorator, in which case the call is equivalent to ``if_else(x < y, y, x)``;

     * With the :ref:`numeric_ <feature-decorator>` decorator, in which case if an element of ``x`` or ``y`` is a Nan 
       the  result is always the other value element.

Example
*******

.. include:: ../../../../test/doc/core/max.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/max.txt
  :literal:
