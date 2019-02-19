.. _function-bitwise_andnot:

bitwise_andnot
==============

**Required header** ``#include <eve/function/bitwise_andnot.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr Value0 bitwise_andnot( Value0 lhs, Value1 rhs ) noexcept
   }

Function object for performing bitwise and over two :ref:`Values <concept-value>` 
of possibly different types but of same bit size (``lhs & ~rhs``).

The result type is the one of the first operand.


Parameters
----------

  - ``lhs``, ``rhs`` : input values

Return value
------------

The bitwise and of  ``lhs`` and the complement of the ``rhs`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/bitwise_andnot.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/bitwise_andnot.txt
  :literal:

