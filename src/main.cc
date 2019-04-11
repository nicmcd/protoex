/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * - Neither the name of prim nor the names of its contributors may be used to
 * endorse or promote products derived from this software without specific prior
 * written permission.
 *
 * See the NOTICE file distributed with this work for additional information
 * regarding copyright ownership.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <prim/prim.h>

#include <cstdio>

#include "Port.pb.h"
#include "Switch.pb.h"

void printSwitch(const Switch& _s) {
  u32 numPorts = _s.port_size();
  printf("vendor=%s arch=%s ports=%i\n",
         _s.vendor().c_str(), _s.arch().c_str(), numPorts);
  for (u32 p = 0; p < numPorts; p++) {
    printf("  %i -> speed=%f lanes=%i\n",
           p, _s.port(p).speed(), _s.port(p).lanes());
  }
}

s32 main(s32 _argc, char** _argv) {
  (void)_argc;
  (void)_argv;

  Switch s1;
  s1.set_vendor("Broadcom");
  s1.set_arch("Tomahawk");
  Port* p1 = s1.add_port();
  p1->set_speed(123.456);
  p1->set_lanes(4);

  size_t size = s1.ByteSizeLong();
  printf("using %lu bytes\n", size);
  printSwitch(s1);

  char* array = new char[size];
  s1.SerializeToArray(array, size);

  Switch s2;
  s2.ParseFromArray(array, size);
  printSwitch(s2);

  return 0;
}
