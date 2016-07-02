//
// Created by max on 02.07.16.
//

#ifndef FASTCRAFT_FILE_H
#define FASTCRAFT_FILE_H

#include <iostream>

class File {
public:
    static std::string open(const char *path) {
        std::string str;
        std::ifstream if_stream_file;
        // ensures ifstream objects can throw exceptions:
        if_stream_file.exceptions(std::ifstream::badbit);
        try {
            // Open files
            if_stream_file.open(path);
            std::stringstream stream;
            // Read file's buffer contents into streams
            stream << if_stream_file.rdbuf();
            // close file handlers
            if_stream_file.close();
            // Convert stream into string
            str = stream.str();
        }
        catch (std::ifstream::failure e) {
            return "";
        }

        return str;
    }
};

#endif //FASTCRAFT_FILE_H
