// Copyright (c) 2017 Sony Corporation. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/** Div2
 */
#ifndef __NBLA_FUNCTION_DIV2_HPP__
#define __NBLA_FUNCTION_DIV2_HPP__

#include <nbla/function/utils/base_transform_binary.hpp>

#include <cmath>

namespace nbla {

/** @class Div2
@brief Elementwise division defined as
@f[
y_i = x^{(0)}_i / x^{(1)}_i.
@f]

Inputs:
- N-D array.
- N-D array.

Outputs:
- N-D array.

@tparam T Data type for computation.
\ingroup FunctionImplGrp
 */
// Inplacing is obsoleted.
NBLA_DEFINE_TRANSFORM_BINARY_INPLACE(Div2, x0 / x1, dy / x1,
                                     -dy *x0 / (x1 * x1), false, false, true,
                                     true, true);
}
#endif
