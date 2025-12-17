# SecureFileAccess

A C++ library and command-line tool designed to audit and secure file access permissions for applications, inspired by Microsoft's Windows 11 AI agents data security concerns. This project helps developers and users understand and control file access patterns to prevent unauthorized data exposure.

## Why This Matters
Microsoft's recent clarification about Windows 11 AI agents' file access capabilities has raised significant data security concerns. SecureFileAccess proactively identifies potential security risks in application file operations before they lead to data breaches.

## Key Features
- **Real-time File Access Monitoring**: Tracks all file operations during application execution
- **Permission Risk Scoring**: Rates file access patterns (0-100) based on security risk
- **Audit Report Generation**: Creates comprehensive security reports in JSON and human-readable format
- **Secure Default Configuration**: Enforces least-privilege access by default
- **Cross-Platform Support**: Works on Windows, Linux, and macOS

## Installation
```bash
# Clone the repository
git clone https://github.com/yourusername/SecureFileAccess.git

# Build the project
cd SecureFileAccess
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Usage
### As a Library
```cpp
#include <SecureFileAccess.h>

int main() {
    SecureFileAccess::Auditor auditor;
    auditor.startMonitoring();
    
    // ... application code that accesses files ...
    
    auto report = auditor.generateReport();
    std::cout << report.toJson() << std::endl;
    return 0;
}
```

### As Command-Line Tool
```bash
# Monitor a process (e.g., your application)
./bin/secure_file_access --process "my_app" --output report.json

# Generate human-readable report
./bin/secure_file_access --report report.json --format markdown
```

## Example Output
```
SECUREFILEACCESS AUDIT REPORT (Generated 2023-10-15)

[PROCESS] my_app (PID: 12345)
[RISK SCORE] 78/100 (High Risk)
[THREATS]
  • Access to sensitive user directory: /Users/johndoe/Documents
  • Unrestricted write access to application data folder
  • No encryption for file operations

[RECOMMENDATIONS]
  1. Restrict file access to application-specific directories only
  2. Implement file encryption for sensitive data
  3. Add permission checks before file operations
```

## Security Philosophy
- **Least Privilege Principle**: By default, applications should only access necessary files
- **Transparent Operations**: Users always know which files an application accesses
- **Proactive Protection**: Identifies risks before data exposure occurs

## Contributing
We welcome security researchers and C++ developers to contribute. Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## License
This project is licensed under the MIT License - see [LICENSE](LICENSE) for details.

---

*Inspired by Microsoft's Windows 11 AI agent data security concerns and the growing need for transparent file access management in modern applications.*
