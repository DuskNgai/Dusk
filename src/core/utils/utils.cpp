#include <fstream>
#include <sstream>

#include <dusk/assert.hpp>
#include <dusk/log.hpp>
#include <dusk/core/utils/utils.hpp>

DUSK_NAMESPACE_BEGIN

std::string get_file_path(std::string const& target, int depth) {
    std::string path{ target };
    for (auto i{ 0 }; i < depth; ++i) {
        if (std::filesystem::exists(path)) {
            return path;
        }
        path = "../" + path;
    }
    DUSK_CORE_ERROR("File not found: {:s}", target);
    return target;
}

std::string read_text_file(std::string const& file_name) {
    std::string text;
    std::ifstream file;
    // Throw when file stream encounters with these status codes.
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        file.open(file_name);
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        text = ss.str();
    }
    catch (std::ifstream::failure& e) {
        DUSK_CORE_ASSERT(false, std::string(e.what()));
    }

    return text;
}

DUSK_NAMESPACE_END
