.. _constant-smallestposval:

Smallestposval 
==============

**Required header** ``#include <eve/constant/smallestposval.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr Value Smallestposval<Value>() noexcept
   }

This 'constant' returns the  :ref:`Value <concept-value>` which is the least normal strictly positive value for the type

  +-------------+-------------------------+---------------+-----------+
  | Type        | double                  | float         | Integral  |
  +-------------+-------------------------+---------------+-----------+
  | **Values**  | 2.225073858507201e-308  | 1.1754944e-38 |  1        |
  +-------------+-------------------------+---------------+-----------+


Template parameter
------------------

  -  ``Value`` : the returned value is of type ``Value``

