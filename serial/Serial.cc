#include "Serial.h"

namespace serial {

    OBinaryFile::OBinaryFile(const std::string& filename, Mode mode) {
        // TODO
    }

    OBinaryFile::OBinaryFile(OBinaryFile&& other) noexcept {
        // TODO: Implement move constructor
        return;
    }


    OBinaryFile& OBinaryFile::operator=(OBinaryFile&& other) noexcept {
        // TODO: Implement move assignment
        return *this;
    }

    OBinaryFile::~OBinaryFile() {
        // TODO
    }

    std::size_t OBinaryFile::write(const std::byte* data, std::size_t size) {
        // TODO
        return 0;
    }

    IBinaryFile::IBinaryFile(const std::string& filename) {
        // TODO
    }

    IBinaryFile::IBinaryFile(IBinaryFile&& other) noexcept {
        // TODO: Implement move constructor
        return;
    }

    IBinaryFile& IBinaryFile::operator=(IBinaryFile&& other) noexcept {
        // TODO: Implement move assignment
        return *this;
    }

    IBinaryFile::~IBinaryFile() {
        // TODO
    }

    std::size_t IBinaryFile::read(std::byte* data, std::size_t size) {
        // TODO
        return 0;
    }

    OBinaryFile& operator<<(OBinaryFile& file, uint8_t x) {
        // TODO
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, int8_t x) {
        // TODO
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, uint16_t x) {
        // TODO
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, int16_t x) {
        // TODO
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

    IBinaryFile& operator>>(IBinaryFile& file, int8_t& x) {
        // TODO
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint8_t& x) {
        // TODO
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
