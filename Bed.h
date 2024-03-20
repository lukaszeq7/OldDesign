#ifndef OLDDESIGN_BED_H
#define OLDDESIGN_BED_H

#include <QObject>

class Bed : public QObject
{
Q_OBJECT

public:
    explicit Bed(QObject *parent = nullptr);
    ~Bed();

public slots:
    int id() const;
    void setId(int &id);

    const QString &name() const;
    void setName(const QString &name);

    int width() const;
    void setWidth(int width);

    int length() const;
    void setLength(int length);

    int height() const;
    void setHeight(int height);

    const QString &fabric() const;
    void setFabric(const QString &fabric);

private:
    int _id;
    QString _name;
    int _width;
    int _length;
    int _height;
    QString _fabric;
};

#endif //OLDDESIGN_BED_H
