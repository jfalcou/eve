.. _function-add:

###
add
###

**Required header:** ``#include <eve/function/add.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ add = {};
   }

Function object computing the addition of two :ref:`Values <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T, typename U> auto operator()( T const& x, U const& y ) noexcept;

* Computes the element-wise addition of two :ref:`Values <concept-value>`.


Parameters
**********

* Each parameter must be an instance of :ref:`Value <concept-value>`.
* All  :ref:`concept-vectorized` parameters must share the same type
* If at least one parameter is  :ref:`concept-vectorized`, all  :ref:`concept-vectorizable` ones will be converted to 
  its base type prior any other computation.
* If all parameters are  :ref:`concept-vectorizable` they must share the same :ref:`Value <concept-value>` type.

Return value
**************

* If any parameter is  :ref:`concept-vectorized`, a value of this type else a value of  
  the common type of the  :ref:`concept-vectorizable` parameters.

Options
*******

  - With the :ref:`saturated_ <feature-decorator>` decorator the  operation is saturated for 
    :ref:`Integral Values <concept-integralvalue>` entries.
  
  - :ref:`masked call <feature-maskable>` is allowed: ``add[cond](x, y)`` is equivalent to ``if_else(cond, add(x, y), x)``, 
    but can be subject to optimization.

  - apart the preceding conditional case, infix notation can be used with operator ``+``. But be aware that if the two parameters 
    are standard scalar integers, ``+`` is the C++ operator and its result is subject to automatic promotions. 
    This **IS NOT** the case for  :ref:`concept-vectorized` entries.

Example
*******

.. include:: ../../../../test/doc/core/add.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/add.txt
  :literal:
