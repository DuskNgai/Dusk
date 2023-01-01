#include <fstream>
#include <sstream>

#include <Dusk/Assert.hpp>
#include <Dusk/Log.hpp>
#include <Dusk/Utils/Utils.hpp>

DUSK_NAMESPACE_BEGIN

std::string GetFilePath(std::string const& target, int depth) {
    std::string path = target;
    for (int i{}; i < depth; ++i) {
        if (std::filesystem::exists(path)) {
            return path;
        }
        path = "../" + path;
    }
    DUSK_CORE_ERROR("File not found: {:s}", target);
    return target;
}

std::string ReadTextFile(std::string const& filename) {
    std::string text;
    std::ifstream file;
    // Throw when file stream encounters with these status codes.
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        file.open(filename);
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
