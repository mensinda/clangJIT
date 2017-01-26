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

#include "FuncRedirect.hpp"
#include <iostream>

using namespace funcRedirect;

class AAA {
 public:
  std::string func1(int i, std::string f) { return "FUNC1 " + f + std::to_string(i); }
  std::string func2(int i, std::string f) { return "FUNC2 " + f + std::to_string(i); }
};

int main(int argc, char *argv[]) {
  std::cout << "Hello World " << argc << " " << argv[0] << std::endl;

  AAA a;
  std::cout << a.func1(1, " normal ") << std::endl;

  FuncRedirect fr;

  std::string (AAA::*pf1)(int, std::string) = &AAA::func1;
  std::string (AAA::*pf2)(int, std::string) = &AAA::func2;

  fr.redirect((void *&)(pf1), (void *&)(pf2));

  std::cout << a.func1(2, " patched? ") << std::endl;

  return 0;
}
