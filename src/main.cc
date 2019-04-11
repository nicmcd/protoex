#include "prim/prim.h"

#include <cstdio>

#include "Port.pb.h"
#include "Switch.pb.h"

void printSwitch(Switch& _s) {
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
