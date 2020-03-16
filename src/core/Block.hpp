#pragma once

class Element;

#include <memory>
#include <vector>
#include <QString>

class Block
{
public:
    bool operator==(const Block &other) const;

    QString description;
    QString category;
    quint16 address;
    std::vector<std::shared_ptr<Element>> elements;
};
