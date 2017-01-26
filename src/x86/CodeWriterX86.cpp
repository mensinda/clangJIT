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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
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

#include "CodeWriterX86.hpp"
#include <string.h>

namespace funcRedirect {

CodeWriterX86::~CodeWriterX86() {}

size_t CodeWriterX86::calculateDistance(void *oldFN, void *dest) {
  return reinterpret_cast<std::size_t>(dest)    // destination
         - reinterpret_cast<std::size_t>(oldFN) // minus source
         - 5;                                   // For jmp instruction;
}

bool CodeWriterX86::checkNeedLongJmp(void *oldFN, void *dest) {
  std::size_t dist = calculateDistance(oldFN, dest);
  return dist > INT32_MAX && static_cast<int64_t>(dist) < (static_cast<int64_t>(INT32_MIN));
}

void CodeWriterX86::patchFunctionNormal(void *oldFN, void *dest) {
  std::size_t dist = calculateDistance(oldFN, dest);

  char *func = reinterpret_cast<char *>(oldFN);
  // : jmp 0x********;
  func[0] = static_cast<char>(0xE9); // jmp
  memcpy(func + 1, &dist, 4);
}

void CodeWriterX86::patchFunctionLong(void *oldFN, void *dest) {
  char *dist = reinterpret_cast<char *>(&dest); // Pointer to the address of the destination
  char *func = reinterpret_cast<char *>(oldFN); // Pointer to begin of function

  // instructions:
  // push (low 32bit)
  // mov [rsp + 4] (high 32bit)
  // ret
  func[0] = static_cast<char>(0x68); // push
  memcpy(func + 1, dist, 4);
  // C7442404 is prefix of: mov dword [rsp+4], *
  func[5] = static_cast<char>(0xC7);
  func[6] = static_cast<char>(0x44);
  func[7] = static_cast<char>(0x24);
  func[8] = static_cast<char>(0x04);
  memcpy(func + 9, dist + 4, 4);
  func[13] = static_cast<char>(0xC3); // ret
}

void CodeWriterX86::patchFunction(void *oldFN, void *dest) {
  if (checkNeedLongJmp(oldFN, dest)) {
    patchFunctionLong(oldFN, dest);
  } else {
    patchFunctionNormal(oldFN, dest);
  }
}
}
