
#include <iostream>

#include <glkernel/uniform_noise.h>
#include <glkernel/normal_noise.h>
#include <glkernel/square_points.h>

#include <qimage.h>
#include <qpainter.h>


int main(int /*argc*/, char * /*argv*/[])
{
    auto noise = glkernel::Kernel<float>(512, 512);

    auto image = QImage(noise.width(), noise.height(), QImage::Format_ARGB32);
    auto bits = image.bits();


    glkernel::uniform_noise(noise, 0.f, 1.f);
 
    for (unsigned int i = 0; i < noise.size(); ++i)
    {
        bits[i * 4 + 0] = noise[i] * 255;
        bits[i * 4 + 1] = noise[i] * 255;
        bits[i * 4 + 2] = noise[i] * 255;
        bits[i * 4 + 3] = 255;
    }

    image.save("uniform_noise.png");


    glkernel::normal_noise(noise, 1.0f, 0.005f);

    for (unsigned int i = 0; i < noise.size(); ++i)
    {
        bits[i * 4 + 0] = qBound<uchar>(0, noise[i] * 255, 255);
        bits[i * 4 + 1] = qBound<uchar>(0, noise[i] * 255, 255);
        bits[i * 4 + 2] = qBound<uchar>(0, noise[i] * 255, 255);
        bits[i * 4 + 3] = 255;
    }

    image.save("normal_noise.png");

    auto points = glkernel::Kernel<glm::vec2>(24, 24);
    std::cout << "square_points_poisson: #" << glkernel::square_points_poisson(points) << std::endl;

    QPainter painter;

    painter.begin(&image);
    painter.fillRect(image.rect(), Qt::white);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);

    for (unsigned int i = 0; i < points.size(); ++i)
        painter.drawEllipse(points[i].x * image.width() - 2, points[i].y * image.height() - 2, 7, 7);

    painter.end();

    image.save("square_points_poisson.png");


    points.reset();
    std::cout << "square_points_poisson: #" << glkernel::square_points_poisson_ext(points, 100) << std::endl;

    painter.begin(&image);
    painter.fillRect(image.rect(), Qt::white);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);

    for (unsigned int i = 0; i < points.size(); ++i)
        painter.drawEllipse(points[i].x * image.width() - 2, points[i].y * image.height() - 2, 7, 7);

    painter.end();

    image.save("square_points_poisson_ext.png");


    return 0;
}
