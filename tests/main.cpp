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

#define CATCH_CONFIG_MAIN

#include "Redirector.hpp"
#include <catch.hpp>

using namespace funcRedirect;

int func3(int i);
int func4(int i);

class AAA {
 public:
  std::string func1(int i, uint32_t f) { return "FUNC1 " + std::to_string(i) + " " + std::to_string(f); }
};

class BBB : public AAA {
 public:
  std::string func2(int i, uint32_t f) { return "FUNC2 " + std::to_string(i + 100) + " " + std::to_string(f - 5); }
};

int func3(int i) { return i; }
int func4(int i) { return (-1) * i; }

TEST_CASE("std::to_string sanity check") {
  REQUIRE(std::to_string(1) == "1");
  REQUIRE(std::to_string(100) == "100");
  REQUIRE(std::to_string(101) == "101");
  REQUIRE(std::to_string(95) == "95");
}

TEST_CASE("Function redirection") {
  AAA a;
  BBB b;

  {
    REQUIRE(a.func1(1, 100) == "FUNC1 1 100");
    REQUIRE(func3(100) == 100);

    Redirector r;
    r.redirect(&AAA::func1, &BBB::func2);
    r.redirect(&func3, &func4);

    REQUIRE(a.func1(1, 100) == "FUNC2 101 95");
    REQUIRE(func3(100) == -100);
  }

  // Destroying r restores the function
  REQUIRE(a.func1(1, 100) == "FUNC1 1 100");
  REQUIRE(func3(100) == 100);
}
