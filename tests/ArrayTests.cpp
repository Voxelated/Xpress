//==--- Xpress/Array/ArrayFwd.hpp -------------------------- -*- C++ -*- ---==//
//            
//                                Voxel : Xpress
//
//                        Copyright (c) 2017 Rob Clucas
//  
//  This file is distributed under the MIT License. See LICENSE for details.
//  
//==------------------------------------------------------------------------==//
//
/// \file  ArrayTests.cpp
/// \brief This file defines tests for the array module.
// 
//==------------------------------------------------------------------------==//

#include <gtest/gtest.h>
#include <Voxel/Xpress/Array/Array.hpp>

using namespace Voxx::Xpress;

static constexpr std::size_t defaultSize = 10;

TEST(ArrayTests, CanCreateDefaultArray) {
  Array<float, defaultSize> array;
  EXPECT_EQ(array.size(), defaultSize);
}

TEST(ArrayTests, CanCreateSingleValuedArray) {
  Array<float, defaultSize> array{1};
  EXPECT_EQ(array.size(), defaultSize);
  for (std::size_t i = 0; i < array.size(); ++i)
    EXPECT_EQ(array[i], 1);
}

TEST(ArrayTests, CanCreateArrayFromVariadicList) {
  Array<int, 5> array{0, 1, 2, 3, 4};
  EXPECT_EQ(array.size(), 5);
  for (std::size_t i = 0; i < array.size(); ++i)
    EXPECT_EQ(array[i], i); 
}

TEST(ArrayTests, CanCopyConstructArrays) {
  Array<float, defaultSize> array{7};
  EXPECT_EQ(array.size(), defaultSize);
  for (std::size_t i = 0; i < array.size(); ++i)
    EXPECT_EQ(array[i], 7);

  auto otherArray(array);
  EXPECT_EQ(otherArray.size(), defaultSize);
  for (std::size_t i = 0; i < otherArray.size(); ++i)
    EXPECT_EQ(otherArray[i], 7);
}

TEST(ArrayTests, CanMoveConstructArrays) {
  Array<float, defaultSize> array{7};
  EXPECT_EQ(array.size(), defaultSize);
  for (std::size_t i = 0; i < array.size(); ++i)
    EXPECT_EQ(array[i], 7);

  auto otherArray(std::move(array));
  EXPECT_EQ(otherArray.size(), defaultSize);
  for (std::size_t i = 0; i < otherArray.size(); ++i)
    EXPECT_EQ(otherArray[i], 7);
}

TEST(ArrayTests, CanCopyAssignArrays) {
  Array<float, defaultSize> array{1};
  EXPECT_EQ(array.size(), defaultSize);
  for (std::size_t i = 0; i < array.size(); ++i)
    EXPECT_EQ(array[i], 1);

  auto otherArray = array;
  EXPECT_EQ(otherArray.size(), defaultSize);
  for (std::size_t i = 0; i < otherArray.size(); ++i)
    EXPECT_EQ(otherArray[i], 1);
}

TEST(ArrayTests, CanMoveAssignArrays) {
  Array<float, defaultSize> array{1};
  EXPECT_EQ(array.size(), defaultSize);
  for (std::size_t i = 0; i < array.size(); ++i)
    EXPECT_EQ(array[i], 1);

  auto otherArray = std::move(array);
  EXPECT_EQ(otherArray.size(), defaultSize);
  for (std::size_t i = 0; i < otherArray.size(); ++i)
    EXPECT_EQ(otherArray[i], 1);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}