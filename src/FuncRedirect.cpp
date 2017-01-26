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

#include "FuncRedirect.hpp"
#include <iostream>

#if IS_POSIX
#include "MemProtectPosix.hpp"
#endif

#if IS_X86
#include "CodeWriterX86.hpp"
#endif

namespace funcRedirect {

FuncRedirect::FuncRedirect() {
#if IS_POSIX
  memPro = new MemProtectPosix();
#endif

#if IS_X86
  writer = new CodeWriterX86();
#endif
}

FuncRedirect::~FuncRedirect() {
  if (writer)
    delete writer;

  if (memPro)
    delete memPro;
}

void FuncRedirect::redirect(void *oldFN, void *dest) {
  if (!oldFN || !dest) {
    return;
  }

  memPro->unprotectPage(oldFN, memPro->getPageSize());
  writer->patchFunction(oldFN, dest);
}
}
