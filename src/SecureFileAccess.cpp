
#include "SecureFileAccess.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstring>

namespace SecureFileAccess {

// Cross-platform sensitive path detection
bool Auditor::is_sensitive_path(const std::string& path) const {
    // Common sensitive directories (case-insensitive)
    std::vector<std::string> sensitive_keywords = {
        "documents", "downloads", "desktop", "music", "videos", "pictures",
        "appdata", "local", "roaming", "user", "profile", "data"
    };

    std::string lower_path = path;
    std::transform(lower_path.begin(), lower_path.end(), lower_path.begin(), 
                   [](unsigned char c){ return std::tolower(c); });

    for (const auto& keyword : sensitive_keywords) {
        if (lower_path.find(keyword) != std::string::npos) {
            return true;
        }
    }
    return false;
}

void Auditor::startMonitoring() {
    if (monitoring_) return;
    
    // In a real implementation, this would set up file system hooks
    // For demo purposes, we'll simulate basic monitoring
    monitoring_ = true;
    
    // Get current process info
    char buffer[256];
    if (getenv("PROCESS_NAME")) {
        process_name_ = getenv("PROCESS_NAME");
    } else {
        process_name_ = "current_process";
    }
    
    // Simulate getting PID
    process_pid_ = std::to_string(static_cast<unsigned int>(getpid()));
}

void Auditor::stopMonitoring() {
    if (!monitoring_) return;
    monitoring_ = false;
    computeRiskScore();
}

void Auditor::computeRiskScore() {
    risk_score_ = 0;
    for (const auto& event : events_) {
        if (event.is_sensitive) {
            risk_score_ += 20;  // Sensitive path access
            if (event.operation == FileAccessOperation::WRITE) {
                risk_score_ += 30;  // Write to sensitive path
            }
        }
        if (event.risk_level > 0) {
            risk_score_ += event.risk_level;
        }
    }
    risk_score_ = std::min(risk_score_, 100);
}

std::string Auditor::generateReport() const {
    return getReportMarkdown();
}

std::string Auditor::getReportJson() const {
    std::ostringstream oss;
    oss << "{\n";
    oss << "  \"process\": \"" << process_name_ << "\",\n";
    oss << "  \"pid\": \"" << process_pid_ << "\",\n";
    oss << "  \"risk_score\": " << risk_score_ << ",\n";
    oss << "  \"threats\": [\n";
    
    bool first = true;
    for (const auto& event : events_) {
        if (event.is_sensitive) {
            if (!first) oss << ",\n";
            first = false;
            oss << "    \"Access to sensitive path: " << event.path << "\"";
        }
    }
    
    oss << "\n  ],\n";
    oss << "  \"recommendations\": [\n";
    oss << "    \"Restrict file access to application-specific directories only\",\n";
    oss << "    \"Implement file encryption for sensitive data\",\n";
    oss << "    \"Add permission checks before file operations\"\n";
    oss << "  ]\n";
    oss << "}";
    return oss.str();
}

std::string Auditor::getReportMarkdown() const {
    std::ostringstream oss;
    oss << "SECUREFILEACCESS AUDIT REPORT (Generated " << __DATE__ << ")\n\n";
    
    oss << "[PROCESS] " << process_name_ << " (PID: " << process_pid_ << ")\n";
    oss << "[RISK SCORE] " << risk_score_ << "/100";
    if (risk_score_ > 75) {
        oss << " (High Risk)";
    } else if (risk_score_ > 50) {
        oss << " (Medium Risk)";
    } else {
        oss << " (Low Risk)";
    }
    oss << "\n\n[THREATS]\n";
    
    for (const auto& event : events_) {
        if (event.is_sensitive) {
            oss << "  • Access to sensitive path: " << event.path << "\n";
        }
    }
    
    if (events_.empty()) {
        oss << "  • No file access detected\n";
    }
    
    oss << "\n[RECOMMENDATIONS]\n";
    oss << "  1. Restrict file access to application-specific directories only\n";
    oss << "  2. Implement file encryption for sensitive data\n";
    oss << "  3. Add permission checks before file operations\n";
    
    return oss.str();
}

}  // namespace SecureFileAccess
