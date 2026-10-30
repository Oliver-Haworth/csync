// AI assisted file, I have made sure I understand everything generated
#include "hash.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <memory>
#include <system_error>

#define XXH_INLINE_ALL
#include "xxhash.h"

namespace fs = std::filesystem;

namespace {

struct XXH3StateDeleter {
    void operator()(XXH3_state_t* state) const noexcept {
        if (state) XXH3_freeState(state);
    }
};
using UniqueXXH3State = std::unique_ptr<XXH3_state_t, XXH3StateDeleter>;

std::string toHexString(const XXH128_hash_t& hash) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0')
        << std::setw(16) << hash.high64
        << std::setw(16) << hash.low64;
    return oss.str();
}

bool feedFileToState(const fs::path& filepath, XXH3_state_t* state) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) return false;

    constexpr size_t buffer_size = 64 * 1024;
    std::vector<char> buffer(buffer_size);

    while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
        if (XXH3_128bits_update(state, buffer.data(), file.gcount()) == XXH_ERROR) {
            return false;
        }
    }
    return true;
}

} // anonymous namespace

std::string hashFile(const fs::path& filepath) {
    UniqueXXH3State state(XXH3_createState());
    if (!state || XXH3_128bits_reset(state.get()) == XXH_ERROR) {
        return "";
    }

    if (!feedFileToState(filepath, state.get())) {
        return "";
    }

    XXH128_hash_t hash = XXH3_128bits_digest(state.get());
    return toHexString(hash);
}

std::string hashDirectory(const fs::path& dirpath) {
    std::error_code ec;
    if (!fs::is_directory(dirpath, ec) || ec) {
        return "";
    }

    std::vector<fs::path> relative_paths;
    auto iter_options = fs::directory_options::skip_permission_denied;

    for (fs::recursive_directory_iterator it(dirpath, iter_options, ec), end; 
         it != end && !ec; 
         it.increment(ec)) 
    {
        if (it->is_symlink(ec)) continue;

        if (it->is_regular_file(ec)) {
            // Ignore syncing metadata folder if you don't want it affecting the hash
            if (it->path().string().find(".csync") != std::string::npos) {
                continue;
            }
            relative_paths.push_back(fs::relative(it->path(), dirpath, ec));
        }
    }

    if (ec) return "";

    std::sort(relative_paths.begin(), relative_paths.end());

    UniqueXXH3State state(XXH3_createState());
    if (!state || XXH3_128bits_reset(state.get()) == XXH_ERROR) {
        return "";
    }

    for (const auto& rel_path : relative_paths) {
        std::string path_str = rel_path.generic_string();
        uint64_t path_len = static_cast<uint64_t>(path_str.size());

        if (XXH3_128bits_update(state.get(), &path_len, sizeof(path_len)) == XXH_ERROR ||
            XXH3_128bits_update(state.get(), path_str.data(), path_str.size()) == XXH_ERROR) {
            return "";
        }

        fs::path full_path = dirpath / rel_path;
        if (!feedFileToState(full_path, state.get())) {
            return "";
        }
    }

    XXH128_hash_t hash = XXH3_128bits_digest(state.get());
    return toHexString(hash);
}

std::string hashPath(const fs::path& path) {
    if (fs::is_directory(path)) {
        return hashDirectory(path);
    }
    return hashFile(path);
}