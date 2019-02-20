.. _function-is_lessgreater:

is_lessgreater
============

**Required header** ``#include <eve/function/is_lessgreater.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_lessgreater( Value lhs, Value rhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` if and only if
its first parameter is :ref:`less <function-is_less>` or 
:ref:` greater <function-is_greater>` than the second.
Accordingly :ref:`False <constant-true_>`
is returned if and only if the two values are  :ref:`equal <function-is_equal>`
or :ref:`unordered <function-is_unordered>`.


Infix notation can be used with operator '=='.

.. seealso::  :ref:`is_ordered <function-is_ordered>`

Parameters
----------

  - ``lhs``, ``rhs`` : values to compare of the same type

Return value
------------

The logical  lessgreater of ``lhs`` and ``rhs`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_lessgreater.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_lessgreater.txt
  :literal:

