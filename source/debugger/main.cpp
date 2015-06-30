
#include <iostream>
#include <chrono>

#include <glkernel/kernel.h>

#include <glkernel/noise.h>
#include <glkernel/sample.h>

#include <qimage.h>
#include <qpainter.h>

using namespace glkernel;


int main(int /*argc*/, char * /*argv*/ [])
{
    auto kernel = kernel3{ 256, 256 };

    auto image = QImage(kernel.width(), kernel.height(), QImage::Format_ARGB32);
    auto bits = image.bits();

    // test uniform noise

    noise::uniform(kernel, glm::vec3{ 0.f, 0.f, 0.f } , glm::vec3{ 1.f, 1.f, 1.f });
 
    for (unsigned int i = 0; i < kernel.size(); ++i)
    {
        bits[i * 4 + 2] = glm::clamp(0.f, kernel[i][0] * 255.f, 255.f);
        bits[i * 4 + 1] = glm::clamp(0.f, kernel[i][1] * 255.f, 255.f);
        bits[i * 4 + 0] = glm::clamp(0.f, kernel[i][2] * 255.f, 255.f);
        bits[i * 4 + 3] = 255;
    }

    image.save("noise--uniform.png");


    // test normal noise

    kernel.reset();

    noise::normal(kernel, glm::vec3{ 0.5f, 0.5f, 0.5f }, glm::vec3{ 0.1f, 0.2f, 0.4f });

    for (unsigned int i = 0; i < kernel.size(); ++i)
    {
        bits[i * 4 + 2] = glm::clamp(0.f, kernel[i][0] * 255.f, 255.f);
        bits[i * 4 + 1] = glm::clamp(0.f, kernel[i][1] * 255.f, 255.f);
        bits[i * 4 + 0] = glm::clamp(0.f, kernel[i][2] * 255.f, 255.f);
        bits[i * 4 + 3] = 255;
    }

    image.save("noise--normal.png");

    // test poisson square samples
   

    auto samples = kernel2{ 32, 32 };

    auto num_samples = sample::poisson_square(samples);
    std::cout << "sample::poisson_square    : #" << num_samples << " of " << samples.size() << std::endl;

    QPainter painter;

    painter.begin(&image);
    painter.fillRect(image.rect(), Qt::white);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);

    for (unsigned int i = 0; i < num_samples; ++i)
    {
        painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0, samples[i].y * image.height() + 0.5 - 1.0), 3, 3);
 
        // since poisson square is tilable, render tilable (and skip the check, its just for debugging)
        painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0, samples[i].y * image.height() + 0.5 - 1.0 + image.height()), 3, 3);
        painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0, samples[i].y * image.height() + 0.5 - 1.0 - image.height()), 3, 3);
        painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0 + image.width(), samples[i].y * image.height() + 0.5 - 1.0), 3, 3);
        painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0 - image.width(), samples[i].y * image.height() + 0.5 - 1.0), 3, 3);
        painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0 + image.width(), samples[i].y * image.height() + 0.5 - 1.0 + image.height()), 3, 3);
        painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0 + image.width(), samples[i].y * image.height() + 0.5 - 1.0 - image.height()), 3, 3);
        painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0 - image.width(), samples[i].y * image.height() + 0.5 - 1.0 + image.height()), 3, 3);
        painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0 - image.width(), samples[i].y * image.height() + 0.5 - 1.0 - image.height()), 3, 3);
    }

    painter.end();

    image.save("sample--poisson_square.png");

    return 0;
}
