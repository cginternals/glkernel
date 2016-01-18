
#include <iostream>
#include <chrono>

#include <glkernel/Kernel.h>

#include <glkernel/noise.h>
#include <glkernel/sample.h>
#include <glkernel/sequence.h>
#include <glkernel/shuffle.h>

#include <qimage.h>
#include <qpainter.h>
#include <qfile.h>
#include <qtextstream.h>

using namespace glkernel;


int main(int /*argc*/, char * /*argv*/ [])
{
    //auto kernel = kernel3{ 1024, 1024 };

    //auto image = QImage(kernel.width(), kernel.height(), QImage::Format_ARGB32);
    //auto bits = image.bits();

    //// test uniform noise

    //noise::uniform(kernel, glm::vec3{ 0.f, 0.f, 0.f } , glm::vec3{ 1.f, 1.f, 1.f });
 
    //for (unsigned int i = 0; i < kernel.size(); ++i)
    //{
    //    bits[i * 4 + 2] = glm::clamp(0.f, kernel[i][0] * 255.f, 255.f);
    //    bits[i * 4 + 1] = glm::clamp(0.f, kernel[i][1] * 255.f, 255.f);
    //    bits[i * 4 + 0] = glm::clamp(0.f, kernel[i][2] * 255.f, 255.f);
    //    bits[i * 4 + 3] = 255;
    //}

    //image.save("noise--uniform.png");


    //// test normal noise

    //kernel.reset();

    //noise::normal(kernel, glm::vec3{ 0.5f, 0.5f, 0.5f }, glm::vec3{ 0.1f, 0.2f, 0.4f });

    //for (unsigned int i = 0; i < kernel.size(); ++i)
    //{
    //    bits[i * 4 + 2] = glm::clamp(0.f, kernel[i][0] * 255.f, 255.f);
    //    bits[i * 4 + 1] = glm::clamp(0.f, kernel[i][1] * 255.f, 255.f);
    //    bits[i * 4 + 0] = glm::clamp(0.f, kernel[i][2] * 255.f, 255.f);
    //    bits[i * 4 + 3] = 255;
    //}

    //image.save("noise--normal.png");

    // test poisson square samples
   
   /* auto screendoor_alpha = kernel1{ 8, 8 };
    const auto epsilon = 1.f / (screendoor_alpha.size() + 1);
    sequence::uniform(screendoor_alpha, epsilon, 1.f - epsilon);
    shuffle::bucket_permutate(screendoor_alpha, 4, 4);


    auto alpha_mask = QImage(screendoor_alpha.width(), screendoor_alpha.height(), QImage::Format_ARGB32);
    auto alpha_mask_bits = alpha_mask.bits();

    for (unsigned int i = 0; i < screendoor_alpha.size(); ++i)
    {
        alpha_mask_bits[i * 4 + 0] = glm::clamp(0.f, screendoor_alpha[i] * 255.f, 255.f);
        alpha_mask_bits[i * 4 + 1] = glm::clamp(0.f, screendoor_alpha[i] * 255.f, 255.f);
        alpha_mask_bits[i * 4 + 2] = glm::clamp(0.f, screendoor_alpha[i] * 255.f, 255.f);
        alpha_mask_bits[i * 4 + 3] = 255;
    }

    alpha_mask.save("alphasampler.png");

    QFile file("alphasampler.txt");
    if (file.open(QIODevice::ReadWrite)) 
    {
        QTextStream stream(&file);
        for (size_t i = 0; i < screendoor_alpha.size(); ++i)
        {
            stream << static_cast<int>(screendoor_alpha[i] * 255) << ", ";
            if ((i + 1) % screendoor_alpha.width() == 0)
                stream << "\n";
        }
    }*/

    //auto t0 = std::chrono::high_resolution_clock::now();

    //auto samples = kernel2{ 512, 512 };

    //auto num_samples = sample::poisson_square(samples, 30);

    //auto t1 = std::chrono::high_resolution_clock::now();
    //std::cout << " time :" << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << std::endl;




    //std::cout << "sample::poisson_square    : #" << num_samples << " of " << samples.size() << std::endl;

    //QPainter painter;

    //painter.begin(&image);

    //painter.setRenderHints(QPainter::RenderHint::TextAntialiasing | QPainter::Antialiasing);
    //painter.fillRect(image.rect(), Qt::white);

    //painter.setPen(Qt::NoPen);
    //painter.setBrush(Qt::black);

    //for (unsigned int i = 0; i < num_samples; ++i)
    //{
    //    painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0, samples[i].y * image.height() + 0.5 - 1.0), 3, 3);
 
    //    // since poisson square is tilable, render tilable (and skip the check, its just for debugging)
    //    painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0, samples[i].y * image.height() + 0.5 - 1.0 + image.height()), 3, 3);
    //    painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0, samples[i].y * image.height() + 0.5 - 1.0 - image.height()), 3, 3);
    //    painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0 + image.width(), samples[i].y * image.height() + 0.5 - 1.0), 3, 3);
    //    painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0 - image.width(), samples[i].y * image.height() + 0.5 - 1.0), 3, 3);
    //    painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0 + image.width(), samples[i].y * image.height() + 0.5 - 1.0 + image.height()), 3, 3);
    //    painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0 + image.width(), samples[i].y * image.height() + 0.5 - 1.0 - image.height()), 3, 3);
    //    painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0 - image.width(), samples[i].y * image.height() + 0.5 - 1.0 + image.height()), 3, 3);
    //    painter.drawEllipse(QPointF(samples[i].x * image.width() + 0.5 - 1.0 - image.width(), samples[i].y * image.height() + 0.5 - 1.0 - image.height()), 3, 3);
    //}

    //painter.end();

    //image.save("sample--poisson_square.png");

    return 0;
}
