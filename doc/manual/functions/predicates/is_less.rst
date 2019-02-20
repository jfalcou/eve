.. _function-is_less:

is_less
============

**Required header** ``#include <eve/function/is_less.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_less( Value lhs, Value rhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
according its first parameter is less than the second.


Infix notation can be used with operator '<'.

.. seealso::  :ref:`is_less_equal <function-is_less_equal>`

Parameters
----------

  - ``lhs``, ``rhs`` : values to compare of the same type

Return value
------------

The logical values ``lhs`` less than ``rhs`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_less.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_less.txt
  :literal:

