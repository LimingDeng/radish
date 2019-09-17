/*
 * File: transformer_encoder.h
 * Project: transformer
 * Author: koth (Koth Chen)
 * -----
 * Last Modified: 2019-09-17 9:55:29
 * Modified By: koth (nobody@verycool.com)
 * -----
 * Copyright 2020 - 2019
 */
#pragma once

#include <torch/nn/cloneable.h>
#include <torch/nn/module.h>
#include <torch/nn/modules/any.h>

#include <torch/nn/pimpl.h>
#include <torch/types.h>

#include <cstddef>
#include <vector>

#include "transformer/encoder_layer.h"
#include "layers/embedding.h"
#include "layers/modulelist.h"

namespace knlp {
using Tensor = torch::Tensor;
/// Options for the `TransformerEncoder` module.
struct TORCH_API TransformerEncoderOptions {
  TransformerEncoderOptions(int64_t n_src_vocab, int64_t len_max_seq, int64_t d_word_vec, int64_t n_layers, int64_t n_head,
                      int64_t d_k, int64_t d_v, int64_t d_model, int64_t d_inner, double dropout = 0.1);
  TORCH_ARG(int64_t, n_src_vocab);
  TORCH_ARG(int64_t, len_max_seq);
  TORCH_ARG(int64_t, d_word_vec);
  TORCH_ARG(int64_t, n_layers);
  TORCH_ARG(int64_t, n_head);
  TORCH_ARG(int64_t, d_k);
  TORCH_ARG(int64_t, d_v);
  TORCH_ARG(int64_t, d_model);
  TORCH_ARG(int64_t, d_inner);
  TORCH_ARG(double, dropout) = 0.1;
};

class TORCH_API TransformerEncoderImpl
    : public ::torch::nn::Cloneable<TransformerEncoderImpl> {
 public:
  TransformerEncoderImpl(int64_t n_src_vocab, int64_t len_max_seq, int64_t d_word_vec, int64_t n_layers, int64_t n_head,
                      int64_t d_k, int64_t d_v, int64_t d_model, int64_t d_inner, double dropout = 0.1)
      : TransformerEncoderImpl(
            TransformerEncoderOptions(n_src_vocab, len_max_seq, d_word_vec, n_layers,n_head, d_k, d_v,d_model,d_inner,dropout)) {}
  explicit TransformerEncoderImpl(TransformerEncoderOptions options);

  void reset() override;

  void pretty_print(std::ostream& stream) const override;

  std::vector<Tensor> forward(const Tensor& src_seq, const Tensor& src_pos, bool return_attns=false);

  /// The options used to configure this module.
  TransformerEncoderOptions options;
  knlp::Embedding src_word_emb=nullptr;
  knlp::Embedding pos_emb=nullptr;
  torch::nn::ModuleList  encoder_stack={};
};

/// A `ModuleHolder` subclass for `TransformerEncoderImpl`.
/// See the documentation for `TransformerEncoderImpl` class to learn what
/// methods it provides, or the documentation for `ModuleHolder` to learn about
/// PyTorch's module storage semantics.
TORCH_MODULE(TransformerEncoder);

}  // namespace knlp
