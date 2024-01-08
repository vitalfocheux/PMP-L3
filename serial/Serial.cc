#include "Serial.h"

#include <stdexcept>

namespace serial {

    OBinaryFile::OBinaryFile(const std::string& filename, Mode mode) {
        const char* modeStr = (mode == Mode::Truncate) ? "wb" : "ab";
        this->file = std::fopen(filename.c_str(), modeStr);

        if (!this->file) {
            throw std::runtime_error("Couldn't open file " + filename + " for writing\n");
        }
    }

    /**
     * TODO: revoir le cours pour ces deux fonctions
    */
    OBinaryFile::OBinaryFile(OBinaryFile&& other) noexcept {
        other.file = this->file;
        this->file = nullptr;
    }


    OBinaryFile& OBinaryFile::operator=(OBinaryFile&& other) noexcept {
        if(this != &other) {
            std::swap(this->file, other.file);
        }
        return *this;
    }

    OBinaryFile::~OBinaryFile() {
        if(std::fclose(this->file)) {
            throw std::runtime_error("Couldn't close file\n");
        }
    }

    std::size_t OBinaryFile::write(const std::byte* data, std::size_t size) {
        return std::fwrite(data, sizeof(std::byte), size, this->file);
    }

    IBinaryFile::IBinaryFile(const std::string& filename) {
        this->file = std::fopen(filename.c_str(), "rb");

        if (!this->file) {
            throw std::runtime_error("Couldn't open file " + filename + " for reading\n");
        }
    }

    IBinaryFile::IBinaryFile(IBinaryFile&& other) noexcept {
        std::swap(this->file, other.file);
    }

    IBinaryFile& IBinaryFile::operator=(IBinaryFile&& other) noexcept {
        if(this != &other) {
            std::swap(this->file, other.file);
        }
        return *this;
    }

    IBinaryFile::~IBinaryFile() {
        if(this->file) {
            std::fclose(this->file);
        }
    }

    std::size_t IBinaryFile::read(std::byte* data, std::size_t size) {
        return std::fread(data, sizeof(std::byte), size, this->file);
    }

    OBinaryFile& operator<<(OBinaryFile& file, uint8_t x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, int8_t x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, uint16_t x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, int16_t x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, uint32_t x) {
        // TODO
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, int32_t x) {
        // TODO
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, uint64_t x) {
        // TODO
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, int64_t x) {
        // TODO
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, char x) {
        // TODO
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, float x) {
        // TODO
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, double x) {
        // TODO
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, bool x) {
        // TODO
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, const std::string& x) {
        uint64_t size = x.size();
        file << size;

        file.write(reinterpret_cast<const std::byte*>(x.data()), sizeof(char) * size);
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int8_t& x) {
        file.read(reinterpret_cast<std::byte*>(&x), sizeof(x));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint8_t& x) {
        file.read(reinterpret_cast<std::byte*>(&x), sizeof(x));
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int16_t& x) {
        // TODO
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint16_t& x) {
        // TODO
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int32_t& x) {
        // TODO
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint32_t& x) {
        // TODO
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int64_t& x) {
        // TODO
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint64_t& x) {
        // TODO
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, char& x) {
        // TODO
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, float& x) {
        // TODO
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, double& x) {
        // TODO
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, bool& x) {
        // TODO
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, std::string& x) {
        // TODO
        return file;
    }

    




}
