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

#ifndef NBLA_FUNCTION_WEIGHT_STANDARDIZATION_HPP
#define NBLA_FUNCTION_WEIGHT_STANDARDIZATION_HPP

#include <nbla/cpu.hpp>
#include <nbla/function.hpp>
#include <nbla/function_registry.hpp>

namespace nbla {

NBLA_REGISTER_FUNCTION_HEADER(WeightStandardization, int, float);

/**
    @todo Write doc.

Inputs:

Outputs:

\ingroup FunctionImplGrp
 */
template <typename T>
class WeightStandardization : public BaseFunction<int, float> {
protected:
  int channel_axis_;
  float eps_;

  Shape_t tn_shape_;
  shared_ptr<Function> f_tensor_norm_;

public:
  WeightStandardization(const Context &ctx, int channel_axis, float eps)
      : BaseFunction(ctx, channel_axis, eps), channel_axis_(channel_axis),
        eps_(eps) {}
  virtual ~WeightStandardization() {}
  virtual shared_ptr<Function> copy() const {
    return create_WeightStandardization(ctx_, channel_axis_, eps_);
  }
  virtual int min_inputs() { return 1; }
  virtual int min_outputs() { return 1; }
  virtual vector<dtypes> in_types() { return vector<dtypes>{get_dtype<T>()}; }
  virtual vector<dtypes> out_types() { return vector<dtypes>{get_dtype<T>()}; }
  virtual vector<string> allowed_array_classes() {
    return SingletonManager::get<Cpu>()->array_classes();
  }
  virtual string name() { return "WeightStandardization"; }
  virtual bool grad_depends_output_data(int i, int o) const {
    // Gradient computation always requires output mean and var.
    return o > 0;
  }

protected:
  NBLA_API virtual void setup_impl(const Variables &inputs,
                                   const Variables &outputs);
  NBLA_API virtual void forward_impl(const Variables &inputs,
                                     const Variables &outputs);
  NBLA_API virtual void backward_impl(const Variables &inputs,
                                      const Variables &outputs,
                                      const vector<bool> &propagate_down,
                                      const vector<bool> &accum);
};
}
#endif
