#pragma once

#include "core/model/MeterList.h"
#include <QTextStream>



class IFileFormat {
public:
    virtual void parse(QIODevice& input, MeterList* data) = 0;
    virtual void serializeTo(QIODevice& output, const MeterList& data) = 0;

    virtual ~IFileFormat() = default;
};