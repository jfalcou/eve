.. _function-bitwise_xor:

bitwise_xor
===========

**Required header** ``#include <eve/function/bitwise_xor.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr Value0 bitwise_xor( Value0 lhs, Value1 rhs ) noexcept
   }

Function object for performing bitwise xor over two :ref:`Values <concept-value>` of possibly different types
but of same bit size.

The result type is the one of the first operxor.

Infix notation can be used with operator '^' execept in scalar mode if any
operxor is floating point because of C++ limitations.


Parameters
----------

  - ``lhs``, ``rhs`` : input values

Return value
------------

The bitwise xor of  ``lhs`` and ``rhs`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/bitwise_xor.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/bitwise_xor.txt
  :literal:

