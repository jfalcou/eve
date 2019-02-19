.. _function-bitwise_or:

bitwise_or
===========

**Required header** ``#include <eve/function/bitwise_or.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr Value0 bitwise_or( Value0 lhs, Value1 rhs ) noexcept
   }

Function object for performing bitwise or over two :ref:`Values <concept-value>` of possibly different types but of same bit size (``lhs | ~rhs``).

The result type is the one of the first operand.

Infix notation can be used with operator '|' execept in scalar mode if any
operand is floating point because of C++ limitations.


Parameters
----------

  - ``lhs``, ``rhs`` : input values

Return value
------------

The bitwise or of  ``lhs`` and ``rhs`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/bitwise_or.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/bitwise_or.txt
  :literal:

