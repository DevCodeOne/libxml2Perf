#pragma once

#include <string>

#include <libxml2Perf/DataGen.h>

std::string writerWithLibXml2(std::string toEncode);
std::string writerRaw(std::string base64Content);
std::string writeRawToBuffer(std::string base64Content);
std::string writeToBufferMemcpyWrapper(std::string toEncode);

template<typename Backend>
int writeTo(void *backendAsRawPtr, const char *content, int len) {
    auto* backend = reinterpret_cast<Backend *>(backendAsRawPtr);

    std::string_view contentView(content, len);
    (*backend) << contentView;

    return len;
}

class MemcpyWrapper final {
public:
    explicit MemcpyWrapper(size_t allocSize) : written(0) { dest.resize(allocSize); }

    void write(const char *str, size_t len) {
        if (written + len > dest.capacity()) {
            dest.resize((written + len) * 2);
        }

        std::memcpy(reinterpret_cast<void *>(dest.data() + written), str, len);
        written += len;
    }

    static int writeTo(void *wrapperInstance, const char *content, int len) {
        MemcpyWrapper *instance = reinterpret_cast<MemcpyWrapper *>(wrapperInstance);
        instance->write(content, len);
        return len;
    }

    std::string_view stringView() const { return {dest.data(), written }; }
private:

    std::vector<char> dest;
    size_t written;
};

template<typename Container>
void writeNodeWithBinaryData(xmlTextWriterPtr writer, Container &&data) {
    xmlTextWriterStartElement(writer, BAD_CAST("example"));
    xmlTextWriterWriteString(writer, BAD_CAST(""));
    xmlTextWriterWriteBase64(writer,
                             reinterpret_cast<const char *>(data.data()),
                             0, static_cast<int>(data.size()));
    xmlTextWriterEndElement(writer);
}

template<typename Destination, typename Container>
void writeNodeWithBinaryDataRaw(Destination &destination,
                                xmlOutputBufferPtr underlyingBuffer,
                                xmlTextWriterPtr writer,
                                Container &&data) {
    xmlTextWriterStartElement(writer, BAD_CAST("example"));
    xmlTextWriterWriteString(writer, BAD_CAST(""));
    xmlOutputBufferFlush(underlyingBuffer);

    destination << data;

    xmlTextWriterEndElement(writer);
}

template<typename Container>
void writeNodeWithBinaryDataRaw(MemcpyWrapper &destination,
                                xmlOutputBufferPtr underlyingBuffer,
                                xmlTextWriterPtr writer,
                                Container &&data) {
    xmlTextWriterStartElement(writer, BAD_CAST("example"));
    xmlTextWriterWriteString(writer, BAD_CAST(""));
    xmlOutputBufferFlush(underlyingBuffer);

    destination.write(data.data(), data.size());

    xmlTextWriterEndElement(writer);
}

template<typename Container>
void writeNodeWithBinaryDataRaw(xmlOutputBufferPtr underlyingBuffer,
                                xmlTextWriterPtr writer,
                                Container &&data) {
    xmlTextWriterStartElement(writer, BAD_CAST("example"));
    // Is necessary to end the current tag
    xmlTextWriterWriteString(writer, BAD_CAST(""));
    xmlOutputBufferFlush(underlyingBuffer);

    xmlOutputBufferWrite(underlyingBuffer, static_cast<int>(data.size()), data.data());

    xmlTextWriterEndElement(writer);
}