.. _function-bit_shl:

##############
bit_shl
##############

**Required header:** ``#include <eve/function/bit_shl.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bit_shl = {};
   }

Function object performing a logical shift  to the left of an :ref:`IntegralValue <concept-integralvalue>`  by
another :ref:`IntegralValue <concept-value>` with the same number of elements and same element size.

Synopsis
********

   template<typename V, typename Shift> auto operator()( V const& x, Shift const& y ) noexcept;

* Computes a bitwise left shift of each element of ``x`` by each element of ``y``.

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

* ``bit_shl`` is an alias of :ref:`shl <function-shl>`: to the left logical and aritmetic shifts are the same.
* All shift are to be greater or equal to zero and not greater or equal to the size in bit of the element shifted 
  or an assert is issued.

.. seealso::  :ref:`bit_shr <function-bit_shr>`

Example
*******

.. include:: ../../../../test/doc/core/shl.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/bit_shl.txt
  :literal:
