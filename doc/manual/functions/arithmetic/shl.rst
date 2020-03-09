.. _function-shl:

###
shl
###

**Required header:** ``#include <eve/function/shl.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ shl = {};
   }

Function object performing a shift to the left of an :ref:`IntegralValue <concept-integralvalue>`  by
another :ref:`IntegralValue <concept-value>`  with the same number of elements and same element size.

********
Synopsis
********

.. code-block:: c++

   template<typename I, typename J> auto operator()( I const& x, J const& y ) noexcept;

* Computes a bitwise left shift of each element of ``x`` by each element of ``y``.


Parameters
**********

* Each parameter must be an instance of :ref:`Value <concept-integralvalue>`.
* All  :ref:`concept-vectorized` parameters must share the same cardinal
* If the first parameter is  :ref:`concept-vectorizable`, so must be the second

Return value
**************

* a value of the type of the first parameter.

Notes
*****

* ``shl`` is a shift that multiplies the input value elements by 2 to the shift element.
* All shift are to be greater or equal to zero and not greater or equal to the size in bit of the element shifted or an assert is issued.

.. seealso::  :ref:`shr <function-shr>`

*******
Example
*******

.. include:: ../../../../test/doc/core/shl.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/shl.txt
  :literal:
