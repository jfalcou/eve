.. _function-shr:

###
shr
###

**Required header:** ``#include <eve/function/shr.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ shr = {};
   }

Function object performing an arithmetic  shift to the right of an :ref:`IntegralValue <concept-integralvalue>`  by
another :ref:`IntegralValue <concept-value>`  with the same number of elements and same element size.

Synopsis
********

.. code-block:: c++

   template<typename V, typename Shift> auto operator()( V const& x, Shift const& y ) noexcept;

* Computes an element-wise arithmetic left shift of each element of ``x`` by each element of ``y``.


Parameters
**********

* Each parameter ``x`` and ``y`` must be an instance of :ref:`Value <concept-integralvalue>`.
* All  :ref:`concept-vectorized` parameters must share the same cardinal
* If the first parameter is  :ref:`concept-vectorizable`, so must be the second

Return value
**************

* a value of the type of the first parameter.

Notes
*****

* ``shr`` is a 'arithmetical' shift that does preserve the sign of the input:the input element
  is divided by 2 to the shift element.
* All shift are to be greater or equal to zero and not greater or equal to the size in bit of the element shifted
  or an assert is issued.

.. seealso::  :ref:`shl <function-shl>`


Example
*******

.. include:: ../../../../test/doc/core/shr.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/shr.txt
  :literal:
