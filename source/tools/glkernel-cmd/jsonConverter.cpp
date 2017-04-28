#include "jsonConverter.h"

#include <QJsonArray>

QJsonObject toJson(const glkernel::kernel3& kernel)
{
    QJsonObject jsonObject;

    QJsonArray zArray;

    for (int z = 0; z < kernel.depth(); ++z)
    {
        QJsonArray yArray;

        for (int y = 0; y < kernel.height(); ++y)
        {
            QJsonArray xArray;

            for (int x = 0; x < kernel.width(); ++x)
            {
                QJsonArray elementArray;

                const auto& value = kernel.value(x, y, z);

                elementArray.append(value.x);
                elementArray.append(value.y);
                elementArray.append(value.z);

                xArray.append(elementArray);
            }

            yArray.append(xArray);
        }

        zArray.append(yArray);
    }

    jsonObject["kernel"] = zArray;

    return jsonObject;
}
