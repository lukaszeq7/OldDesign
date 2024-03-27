#include "Bed.h"

Bed::Bed(QObject *parent) : QObject(parent)
{

}

Bed::~Bed()
{

}

int Bed::id() const
{
    return _id;
}

void Bed::setId(int id)
{
    _id = id;
}

const QString &Bed::name() const
{
    return _name;
}

void Bed::setName(const QString &name)
{
    _name = name;
}

int Bed::width() const
{
    return _width;
}

void Bed::setWidth(int width)
{
    _width = width;
}

int Bed::length() const
{
    return _length;
}

void Bed::setLength(int length)
{
    _length = length;
}

int Bed::height() const
{
    return _height;
}

void Bed::setHeight(int height)
{
    _height = height;
}

const QString &Bed::fabric() const
{
    return _fabric;
}

void Bed::setFabric(const QString &fabric)
{
    _fabric = fabric;
}