/* Copyright (c) 2017, Daniel Mensinger
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Daniel Mensinger nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS >AS IS> AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Daniel Mensinger BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "FuncRedirect.hpp"
#include <memory>
#include <vector>

namespace funcRedirect {

class Redirector {
 private:
  std::vector<std::unique_ptr<FuncRedirect>> redirects;

 public:
  Redirector() = default;
  virtual ~Redirector();

  Redirector(const Redirector &) = delete; // No copies
  Redirector(Redirector &&)      = delete; // No copies

  Redirector &operator=(const Redirector &) = delete; // No copies
  Redirector &operator=(Redirector &&) = delete;      // No copies

  template <class RET, class CLASS1, class CLASS2, class... ARGS>
  void redirect(RET (CLASS1::*oldFN)(ARGS... _arg), RET (CLASS2::*dest)(ARGS... _arg)) {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundefined-reinterpret-cast"

    void *RAWoldFN = reinterpret_cast<void *&>(oldFN);
    void *RAWdest  = reinterpret_cast<void *&>(dest);

#pragma clang diagnostic pop

    auto redir = std::make_unique<FuncRedirect>(RAWoldFN, RAWdest);
    redirects.emplace_back(std::move(redir));
  }

  template <class RET, class... ARGS>
  void redirect(RET (*oldFN)(ARGS... _arg), RET (*dest)(ARGS... _arg)) {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundefined-reinterpret-cast"

    void *RAWoldFN = reinterpret_cast<void *&>(oldFN);
    void *RAWdest  = reinterpret_cast<void *&>(dest);

#pragma clang diagnostic pop

    auto redir = std::make_unique<FuncRedirect>(RAWoldFN, RAWdest);
    redirects.emplace_back(std::move(redir));
  }
};
}
