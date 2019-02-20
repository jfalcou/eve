.. _function-is_unordered:

is_unordered
============

**Required header** ``#include <eve/function/is_unordered.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_unordered( Value lhs, Value rhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` if and only if the two parameters are unordered (that is at least one is a Nan value).
Accordingly it returns :ref:`False <constant-false_>` if and only if none of the parameters is a Nan.

.. seealso::  :ref:`is_ordered <function-is_ordered>`

Parameters
----------

  - ``lhs``, ``rhs`` : values to compare of the same type

Return value
------------

The logical  unordered of ``lhs`` and ``rhs`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_unordered.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_unordered.txt
  :literal:

