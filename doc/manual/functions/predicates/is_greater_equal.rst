.. _function-is_greater_equal:

is_greater_equal
============

**Required header** ``#include <eve/function/is_greater_equal.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_greater_equal( Value lhs, Value rhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
  according its first parameter is greater or equal to the second.


Infix notation can be used with operator '>='.

.. seealso::  :ref:`is_greater <function-is_greater>`

Parameters
----------

  - ``lhs``, ``rhs`` : values to compare of the same type

Return value
------------

The logical values ``lhs`` greater or equal to ``rhs`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_greater_equal.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_greater_equal.txt
  :literal:

