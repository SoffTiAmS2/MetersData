// include/core/file/IFileFormat.h
#pragma once
#include "core/model/MeterList.h"
#include <QTextStream>

class IFileFormat {
public:
    virtual ~IFileFormat() = default;
    virtual void parse(QIODevice& input, MeterList& data) = 0;
    virtual void serializeTo(QIODevice& output, const MeterList& data) = 0;
};