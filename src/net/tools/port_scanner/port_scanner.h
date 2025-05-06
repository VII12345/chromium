#ifndef NET_TOOLS_PORT_SCANNER_PORT_SCANNER_H_
#define NET_TOOLS_PORT_SCANNER_PORT_SCANNER_H_

#include <vector>

std::vector<int> GetAllowedPorts();

class PortScanner {
 public:
  void Scan();

 private:
  void ScanPort(int port);
};

#endif  // NET_TOOLS_PORT_SCANNER_PORT_SCANNER_H_
