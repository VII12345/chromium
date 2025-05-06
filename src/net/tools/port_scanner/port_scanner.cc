#include "port_scanner.h"

#include <vector>

#include "base/command_line.h"
#include "base/logging.h"
#include "base/strings/str_split.h"
#include "base/strings/string_number_conversions.h"
#include "chrome/common/chrome_switches.h"  // 或者 net/tools/port_scanner/switches.h

// 解析命令行 --fingerprint-port，返回端口列表
std::vector<int> GetAllowedPorts() {
  base::CommandLine* cmd = base::CommandLine::ForCurrentProcess();
  if (cmd->HasSwitch(switches::kFingerprintPort)) {
    std::string val = cmd->GetSwitchValueASCII(switches::kFingerprintPort);
    std::vector<int> ports;
    for (const auto& token : base::SplitString(val, ",", base::TRIM_WHITESPACE,
                                               base::SPLIT_WANT_NONEMPTY)) {
      int port = 0;
      if (base::StringToInt(token, &port)) {
        ports.push_back(port);
      } else {
        LOG(WARNING) << "Invalid port in --fingerprint-port: " << token;
      }
    }
    if (!ports.empty()) {
      return ports;
    }
  }
  // 回退默认列表
  return {80, 443, 8080};
}

// 实现真正的扫描逻辑
void PortScanner::Scan() {
  std::vector<int> ports = GetAllowedPorts();
  for (int port : ports) {
    ScanPort(port);
  }
}

// 示例：简单尝试 TCP 连接
void PortScanner::ScanPort(int port) {
  LOG(INFO) << "Scanning port " << port;
  // … 在这里用 net::TCPClientSocket 等类去连接端口 …
}

int main(int argc, char* argv[]) {
  base::CommandLine::Init(argc, argv);
  PortScanner scanner;
  scanner.Scan();
  return 0;
}
