#include "stdafx.h"
#include <iostream>
#include <catch.hpp>
SCENARIO("BinarySearchTree init", "[init]") 
{
  BinarySearchTree<int> Tree;
  REQUIRE(Tree.get_size() == 0);
}
