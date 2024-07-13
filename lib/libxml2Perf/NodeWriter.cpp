#include "NodeWriter.h"

#include <libxml2Perf/DataGen.h>

#include <libxml2/libxml/xmlwriter.h>

#include <string_view>
#include <sstream>

void startFile(xmlTextWriterPtr writer) {
    xmlTextWriterStartDocument(writer, nullptr, nullptr, nullptr);
}

void endFile(xmlTextWriterPtr writer) {
    xmlTextWriterEndDocument(writer);
}

std::string writerWithLibXml2(std::string toEncode) {
    std::stringstream destination;
    xmlOutputBufferPtr outputBuffer = xmlOutputBufferCreateIO(writeTo<std::stringstream>,
                                                              nullptr,
                                                              reinterpret_cast<void *>(&destination),
                                                              nullptr);
    xmlTextWriterPtr writer = xmlNewTextWriter(outputBuffer);

    startFile(writer);

    writeNodeWithBinaryData(writer, toEncode);

    endFile(writer);

    xmlFreeTextWriter(writer);

    return destination.str();
}

std::string writerRaw(std::string toEncode) {
    std::stringstream destination;
    xmlOutputBufferPtr outputBuffer = xmlOutputBufferCreateIO(writeTo<std::stringstream>,
                                                              nullptr,
                                                              reinterpret_cast<void *>(&destination),
                                                              nullptr);
    xmlTextWriterPtr writer = xmlNewTextWriter(outputBuffer);

    startFile(writer);

    base64Encode(toEncode);
    writeNodeWithBinaryDataRaw(destination, outputBuffer, writer, toEncode);

    endFile(writer);

    xmlFreeTextWriter(writer);

    return destination.str();
}

std::string writeRawToBuffer(std::string toEncode) {
    xmlBufferPtr buffer = xmlBufferCreate();
    xmlOutputBufferPtr outputBuffer = xmlOutputBufferCreateBuffer(buffer, nullptr);
    xmlTextWriterPtr writer = xmlNewTextWriter(outputBuffer);

    startFile(writer);

    base64Encode(toEncode);
    writeNodeWithBinaryDataRaw(outputBuffer, writer, toEncode);

    endFile(writer);

    xmlOutputBufferFlush(outputBuffer);

    const char *resultingXml = reinterpret_cast<const char *>(xmlBufferContent(buffer));

    xmlFreeTextWriter(writer);

    return {resultingXml};
}

std::string writeToBufferMemcpyWrapper(std::string toEncode) {
    MemcpyWrapper wrapper(static_cast<size_t>(toEncode.size() * 1.5));
    xmlOutputBufferPtr outputBuffer = xmlOutputBufferCreateIO(MemcpyWrapper::writeTo,
                                                              nullptr,
                                                              reinterpret_cast<void *>(&wrapper),
                                                              nullptr);
    xmlTextWriterPtr writer = xmlNewTextWriter(outputBuffer);

    startFile(writer);

    base64Encode(toEncode);
    writeNodeWithBinaryDataRaw(wrapper, outputBuffer, writer, toEncode);

    endFile(writer);

    xmlFreeTextWriter(writer);

    const auto view = wrapper.stringView();
    return {view.data(), view.size() };
}