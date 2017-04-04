//==--- Xpress/Array/ArrayFwd.hpp ------------------------- -*- C++ -*- ---==//
//            
//                                Voxel : Xpress 
//
//                        Copyright (c) 2017 Rob Clucas
//  
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==-----------------------------------------------------------------------==//
//
/// \file  ArrayFwd.hpp
/// \brief This file defines forward declarations for an Array class.
//
//==-----------------------------------------------------------------------==//

#ifndef VOXX_XPRESS_ARRAY_ARRAY_FWD_HPP
#define VOXX_XPRESS_ARRAY_ARRAY_FWD_HPP

#include <cstdlib>

namespace Voxx   {
namespace Xpress {

/// The Array class defines a structure which stores a fixed-size number of
/// elements, contiguously. The class will work on the CPU and the GPU,
/// however, only small versions should be used on the GPU.
/// \tparam     T         The tyoe of the elements in the array.
/// \tparam     Elements  The number of elements in the array.
template <typename T, std::size_t Elements>
class Array;

}} // namespace Voxx::Xpress

#endif // VOXEL_XPRESS_ARRAY_ARRAY_FWD_HPP