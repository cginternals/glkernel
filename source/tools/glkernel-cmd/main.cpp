#include "jsonConverter.h"

#include <iostream>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <glkernel/Kernel.h>
#include <glkernel/noise.h>

int main()
{
    auto kernel = glkernel::kernel3(3, 3, 3);

    glkernel::noise::uniform(kernel, glm::vec3{ 0.f, 0.f, 0.f } , glm::vec3{ 1.f, 1.f, 1.f });

    auto jsonObject = toJson(kernel);

    QJsonDocument jsonDocument(jsonObject);

    QFile outFile("kernel.json");

    if (!outFile.open(QIODevice::WriteOnly))
    {
        return 1;
    }

    outFile.write(jsonDocument.toJson(QJsonDocument::JsonFormat::Indented));
}
