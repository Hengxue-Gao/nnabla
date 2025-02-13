# Copyright 2018,2019,2020,2021 Sony Corporation.
# Copyright 2021,2022 Sony Group Corporation.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

FROM ubuntu:18.04

ARG PIP_INS_OPTS
ARG PYTHONWARNINGS
ARG CURL_OPTS
ARG WGET_OPTS
ARG PYTHON_VER

ENV DEBIAN_FRONTEND noninteractive

RUN eval ${APT_OPTS} && apt-get update \
    && apt-get install -y software-properties-common \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* \
    && add-apt-repository -y ppa:deadsnakes/ppa \
    && apt-get update \
    && apt-get install -y --no-install-recommends \
       bzip2 \
       ca-certificates \
       curl \
       libglib2.0-0 \
       libgl1-mesa-glx \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*


ARG NNABLA_VER
RUN eval ${APT_OPTS} \
    && apt update \
    && apt install -y --no-install-recommends \
       git \
       make \
       build-essential \
       libssl-dev \
       zlib1g-dev \
       libbz2-dev \
       libreadline-dev \
       libsqlite3-dev \
       wget \
       llvm \
       libncursesw5-dev \
       xz-utils \
       tk-dev \
       libxml2-dev \
       libxmlsec1-dev \
       libffi-dev \
       liblzma-dev \
    && git clone https://github.com/pyenv/pyenv.git ~/.pyenv \
    && export PYENV_ROOT="$HOME/.pyenv" \
    && export PATH="$PYENV_ROOT/bin:$PYENV_ROOT/plugins/python-build/bin:$PATH" \
    && export PYTHON_BUILD_CURL_OPTS="${CURL_OPTS}" \
    && export PYTHON_BUILD_WGET_OPTS="${WGET_OPTS}" \
    && export PYTHON_CONFIGURE_OPTS=--disable-shared \
    && PYTHON_VERSION_MINOR=${PYTHON_VER#*.} \
    && if [ ${PYTHON_VERSION_MINOR} -ge 10 ]; then export CPPFLAGS=-I/usr/include/openssl11 && export LDFLAGS=-L/usr/lib64/openssl11; fi \
    && eval "$(pyenv init -)" \
    && python-build `pyenv latest -k ${PYTHON_VER}` /usr/local \
    && pyenv global system \
    && rm -rf ~/.pyenv /tmp/* \
    && apt autoremove --purge -y \
       git \
       make \
       build-essential \
       libssl-dev \
       zlib1g-dev \
       libbz2-dev \
       libreadline-dev \
       libsqlite3-dev \
       wget \
       llvm \
       libncursesw5-dev \
       xz-utils \
       tk-dev \
       libxml2-dev \
       libxmlsec1-dev \
       libffi-dev \
       liblzma-dev \
    && pip install ${PIP_INS_OPTS} --no-cache-dir --upgrade pip \
    && pip install ${PIP_INS_OPTS} --no-cache-dir wheel setuptools \
    && pip install ${PIP_INS_OPTS} --no-cache-dir opencv-python || true \
    && pip install ${PIP_INS_OPTS} --no-cache-dir nnabla==${NNABLA_VER} nnabla_converter==${NNABLA_VER}

# Entrypoint
COPY .entrypoint.sh /opt/.entrypoint.sh
RUN chmod +x /opt/.entrypoint.sh

ENTRYPOINT ["/bin/bash", "-c", "/opt/.entrypoint.sh \"${@}\"", "--"]
