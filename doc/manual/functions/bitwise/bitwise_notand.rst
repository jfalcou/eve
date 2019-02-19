.. _function-bitwise_notand:

bitwise_notand
==============

**Required header** ``#include <eve/function/bitwise_notand.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr Value0 bitwise_notand( Value0 lhs, Value1 rhs ) noexcept
   }

Function object for performing bitwise notand over two :ref:`Values <concept-value>` of possibly different types but of same bit size, (``~lhs & rhs``).

The result type is the one of the first opernotand.


Parameters
----------

  - ``lhs``, ``rhs`` : input values

Return value
------------

The bitwise notand of  ``lhs`` and ``rhs`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/bitwise_notand.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/bitwise_notand.txt
  :literal:

