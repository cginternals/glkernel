ARG BASE=cginternals/graphics-base:latest
ARG BASE_DEV=cginternals/graphics-base:dev
ARG PROJECT_NAME=glkernel

# BUILD

FROM $BASE_DEV AS build

ARG PROJECT_NAME
ARG COMPILER_FLAGS="-j 4"

ENV glkernel_DIR="$WORKSPACE/$PROJECT_NAME"

WORKDIR $WORKSPACE/$PROJECT_NAME

ADD cmake cmake
ADD docs docs
ADD deploy deploy
ADD source source
ADD CMakeLists.txt CMakeLists.txt
ADD configure configure
ADD $PROJECT_NAME-config.cmake $PROJECT_NAME-config.cmake
ADD LICENSE LICENSE
ADD README.md README.md
ADD AUTHORS AUTHORS

RUN ./configure
RUN CMAKE_OPTIONS="-DOPTION_BUILD_TESTS=Off" ./configure
RUN cmake --build build -- $COMPILER_FLAGS

# INSTALL

FROM build as install

ARG PROJECT_NAME

WORKDIR $WORKSPACE/$PROJECT_NAME

RUN CMAKE_OPTIONS="-DCMAKE_INSTALL_PREFIX=$WORKSPACE/$PROJECT_NAME-install" ./configure
RUN cmake --build build --target install

# DEPLOY

FROM $BASE AS deploy

ARG PROJECT_NAME

ENV glm_DIR="$WORKSPACE/glm"
ENV glkernel_DIR="$WORKSPACE/$PROJECT_NAME"

COPY --from=build $WORKSPACE/glm $WORKSPACE/glm

COPY --from=install $WORKSPACE/$PROJECT_NAME-install $WORKSPACE/$PROJECT_NAME
