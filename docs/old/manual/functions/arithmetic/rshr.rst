.. _function-rshr:

####
rshr
####

**Required header:** ``#include <eve/function/rshr.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ rshr = {};
   }

Function object performing a relative shift to the right or the left of an :ref:`IntegralValue <concept-integralvalue>`  by
another :ref:`IntegralValue <concept-value>`  with the same number of elements and same element size. The shift direction is left
(resp. right) if the shift is positive (resp. negative)

********
Synopsis
********

.. code-block:: c++

   template<typename V, typename Shift> auto operator()( V const& x, Shift const& y ) noexcept;

* Computes a bitwise right or left shift of each element of ``x`` by each element of ``y``.


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

*  shifts  greater or equal to zero are to the right, less or equal to zero to the left.
*  shifts absolute values must not be greater or equal to the size in bit of the element shifted or an assert is issued.

.. seealso::  :ref:`rshl <function-rshr>`,  :ref:`shl <function-rshr>`,  :ref:`shr <function-rshr>`,
        :ref:`bit_shl <function-bit_shl>`,  :ref:`bit_shr <function-bit_shr>`

*******
Example
*******

.. include:: ../../../../test/doc/core/rshr.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/rshr.txt
  :literal:
