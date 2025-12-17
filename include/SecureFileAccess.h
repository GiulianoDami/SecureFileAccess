
#pragma once

#include <string>
#include <vector>
#include <map>
#include <filesystem>

namespace SecureFileAccess {

enum class FileAccessOperation {
    READ,
    WRITE,
    OPEN,
    DELETE
};

struct FileAccessEvent {
    std::string path;
    FileAccessOperation operation;
    bool is_sensitive;
    int risk_level;
};

class Auditor {
public:
    void startMonitoring();
    void stopMonitoring();
    std::string generateReport() const;
    std::string getReportJson() const;
    std::string getReportMarkdown() const;

private:
    std::vector<FileAccessEvent> events_;
    int risk_score_ = 0;
    std::string process_name_;
    std::string process_pid_;
    bool monitoring_ = false;
    bool is_sensitive_path(const std::string& path) const;
    void computeRiskScore();
};

}  // namespace SecureFileAccess
