#ifndef JSONDOCUMENT_H
#define JSONDOCUMENT_H
namespace _sutl {
class JsonDocumentImp;
class JsonDocument
{
public:
    JsonDocument();

protected:
    JsonDocumentImp *m_imp=nullptr;
};
}

#endif // JSONDOCUMENT_H
