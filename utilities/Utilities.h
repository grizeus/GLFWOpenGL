#pragma once
#include <fstream>
#include <sstream>
#include <string>

// display file name to window header
inline const char* extract_version(const char* full)
{
    std::string p1 = full;
    static std::string p2;
    p2.clear();
    p2 = p1.substr(
        p1.find_last_of("/\\") + 1, // from last slash
        (p1.length() - p1.find_last_of("/\\")) - (p1.length() - (p1.find_last_of(".")) + 1) // up to last dot
    );
    return p2.c_str();
}

#ifdef _DEBUG
inline void write_log(const char* msg)
{
    std::ofstream logs;
    logs.open("log.txt", std::ofstream::app | std::ofstream::out);
    logs << msg;
    logs.close();
}
#else
inline void write_log(const char* msg)
{ }
#endif

inline std::string read_to_string(const char* path)
{
    std::ifstream input_file_stream(path);
    if(!input_file_stream.is_open())
        throw ("Invalid file path!");
    std::stringstream data;
    data << input_file_stream.rdbuf();
    return data.str();
}
