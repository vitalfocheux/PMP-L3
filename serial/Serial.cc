#include "Serial.h"

#include <stdexcept>

namespace serial {


    OBinaryFile::OBinaryFile(const std::string& filename, Mode mode) {
        const char* modeStr = (mode == Mode::Truncate) ? "wb" : "ab";
        this->file = std::fopen(filename.c_str(), modeStr);

        if (!this->file) {
            throw std::runtime_error("Couldn't open file " + filename + " for writing\n");
        }
        // printf("Constructor %p\n", this);
    }

    

    
    OBinaryFile::OBinaryFile(OBinaryFile&& other) noexcept : file(other.file){
        // printf("Move constructor %p\n", this);
        other.file = nullptr;
    }
        


    OBinaryFile& OBinaryFile::operator=(OBinaryFile&& other) noexcept {
        
        // printf("Move assignment %p\n", this);
        if(this != &other) {
            std::fclose(this->file);
            this->file = other.file;
            other.file = nullptr;
        }
        return *this;
    }

    OBinaryFile::~OBinaryFile() {
        // printf("Destructor %p\n", this);
        if(this->file) {
            std::fclose(this->file);
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
        // printf("Fichier ouvert avec succès pour la lecture.\n");
        // Position the cursor at the beginning of the file
        std::fseek(this->file, 0, SEEK_SET);

        // Get the file size
        std::fseek(this->file, 0, SEEK_END);
        this->fileSize = std::ftell(this->file);
        std::rewind(this->file);
        // printf("Chemin du fichier : %s\n", filename.c_str());
        // printf("Taille du fichier : %ld octets\n", this->fileSize);
       
    }

    IBinaryFile::IBinaryFile(IBinaryFile&& other) noexcept : file(other.file), fileSize(other.fileSize) {
        other.file = nullptr;
        other.fileSize = 0;
    }

    IBinaryFile& IBinaryFile::operator=(IBinaryFile&& other) noexcept {
        if(this != &other) {
            std::fclose(file);
            this->file = other.file;
            this->fileSize = other.fileSize;
            other.file = nullptr;
            other.fileSize = 0;
        }
        return *this;
    }

    IBinaryFile::~IBinaryFile() {
        if(this->file) {
            std::fclose(this->file);
            this->fileSize = 0;
        }
    }

    std::size_t IBinaryFile::read(std::byte* data, std::size_t size) {
        return std::fread(data, sizeof(std::byte), size, this->file);
    }

    OBinaryFile& operator<<(OBinaryFile& file, uint8_t x) {
        std::size_t bytesWrite = file.write(reinterpret_cast<const std::byte*>(&x), sizeof(uint8_t));
        if(bytesWrite != sizeof(uint8_t)) {
            throw std::runtime_error("Couldn't write uint8_t to file\n");
        }
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, int8_t x) {
        std::size_t bytesWrite = file.write(reinterpret_cast<const std::byte*>(&x), sizeof(int8_t));
        if(bytesWrite != sizeof(int8_t)) {
            throw std::runtime_error("Couldn't write int8_t to file\n");
        }
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, uint16_t x) {
        std::size_t bytesWrite = file.write(reinterpret_cast<const std::byte*>(&x), sizeof(uint16_t));
        if(bytesWrite != sizeof(uint16_t)) {
            throw std::runtime_error("Couldn't write uint16_t to file\n");
        }
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile& file, int16_t x) {
        std::size_t bytesWrite = file.write(reinterpret_cast<const std::byte*>(&x), sizeof(int16_t));
        if(bytesWrite != sizeof(int16_t)) {
            throw std::runtime_error("Couldn't write int16_t to file\n");
        }
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
        std::size_t bytesRead = file.read(reinterpret_cast<std::byte*>(&x), sizeof(int8_t));
        if(bytesRead != sizeof(int8_t)) {
            throw std::runtime_error("Couldn't read int8_t from file\n");
        }
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint8_t& x) {
        std::size_t bytesRead = file.read(reinterpret_cast<std::byte*>(&x), sizeof(uint8_t));
        if(bytesRead != sizeof(uint8_t)) {
            throw std::runtime_error("Couldn't read uint8_t from file\n");
        }
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
        file.read(reinterpret_cast<std::byte*>(&x), sizeof(char));
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
