#!/bin/bash

set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROJ_DIR=$(dirname ${DIR})

cd ${PROJ_DIR}

python3 -m pip install -U pybind11 wheel build tox

rm -rf ${PROJ_DIR}/buildlib
bash ${PROJ_DIR}/chdb/build_libchdb.sh