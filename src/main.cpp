
#include <SecureFileAccess.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <getopt.h>
#include <cstring>

// Mock process monitoring for demo purposes
void monitorProcess(const std::string& process_name, SecureFileAccess::Auditor& auditor) {
    auditor.startMonitoring();
    
    // Simulate application file operations
    auditor.events_.push_back({"/home/user/Documents/report.txt", SecureFileAccess::FileAccessOperation::READ, true, 25});
    auditor.events_.push_back({"/tmp/app_data/config.cfg", SecureFileAccess::FileAccessOperation::WRITE, false, 10});
    auditor.events_.push_back({"/var/log/app.log", SecureFileAccess::FileAccessOperation::WRITE, true, 35});
    
    auditor.stopMonitoring();
}

int main(int argc, char* argv[]) {
    std::string process_name = "";
    std::string output_file = "";
    std::string report_file = "";
    std::string format = "json";
    
    // Command-line options
    int opt;
    while ((opt = getopt(argc, argv, "p:o:r:f:")) != -1) {
        switch (opt) {
            case 'p':
                process_name = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'r':
                report_file = optarg;
                break;
            case 'f':
                format = optarg;
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " --process [name] --output [file] or --report [file] --format [json/markdown]" << std::endl;
                return 1;
        }
    }
    
    if (!process_name.empty() && !output_file.empty()) {
        SecureFileAccess::Auditor auditor;
        monitorProcess(process_name, auditor);
        
        std::ofstream out(output_file);
        if (format == "json") {
            out << auditor.getReportJson();
        } else {
            out << auditor.getReportMarkdown();
        }
        out.close();
        std::cout << "Report saved to " << output_file << std::endl;
        return 0;
    }
    
    if (!report_file.empty() && !format.empty()) {
        std::ifstream in(report_file);
        if (!in) {
            std::cerr << "Error: Report file not found" << std::endl;
            return 1;
        }
        
        std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        in.close();
        
        if (format == "markdown") {
            std::cout << content << std::endl;
        } else {
            std::cout << "JSON report:\n" << content << std::endl;
        }
        return 0;
    }
    
    std::cerr << "Error: Missing required parameters" << std::endl;
    std::cerr << "Usage: " << argv[0] << " --process [name] --output [file] or --report [file] --format [json/markdown]" << std::endl;
    return 1;
}
