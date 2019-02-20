.. _function-is_ordered:

is_ordered
============

**Required header** ``#include <eve/function/is_ordered.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_ordered( Value lhs, Value rhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` if and only if the two parameters are ordered 
(that is none is a  :ref:`Nan <constant-nan>` value).
Acoordingly it returns :ref:`False <constant-false_>` if and only if at least one of the parameters is a :ref:`Nan <constant-nan>`.

.. seealso::  :ref:`is_unordered <function-is_unordered>`

Parameters
----------

  - ``lhs``, ``rhs`` : values to compare of the same type

Return value
------------

Semantically equivalent to ``(lhs == lhs) && (rhs == rhs)``  for each parameters element.

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_ordered.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_ordered.txt
  :literal:

