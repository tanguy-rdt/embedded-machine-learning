#!/bin/sh

FILE_NAME=$(readlink -f "$0")
WORKDIR=$(dirname "${FILE_NAME}")

COMMAND=${1}
DEBUG_MODE=0

usage() {
    echo "Usage: $0 [COMMAND] [OPTION]"
    echo "Command:"
    echo "  prepare_audio_file    -- Convert audio files to CSV (time/frequency data and descriptors)"
    echo "  help                  -- Show this message"
    echo "Options:"
    echo "  -d, --debug           -- Enable debug mode"
}

prepare_audio_file() {
    if [ "$DEBUG_MODE" -eq 1 ]; then
        cd "${WORKDIR}/au_to_csv" || exit
        cmake -P CMakeClean.cmake
        cmake -DCMAKE_BUILD_TYPE=Debug .
        make
        cd .. || exit

        ./au_to_csv/machine_learning.o "${WORKDIR}/au_files/blues/blues.00000.au"
        exit
    fi


    cd "${WORKDIR}/au_to_csv" || exit
    cmake -P CMakeClean.cmake
    cmake .
    make 
    cd .. || exit

    if [ -d "${WORKDIR}/csv_files" ]; then
        rm -r "${WORKDIR}/csv_files"
    fi

    for type_path in "${WORKDIR}/au_files"/*; do
        if [ -d "${type_path}" ]; then
            type_name=$(basename "${type_path}")
            for file_path in "${type_path}"/*.au; do
                if [ -f "${file_path}" ]; then
                    file_name_with_extension=$(basename "${file_path}")
                    file_name=${file_name_with_extension%.au}
                    echo "Prepare au file ${file_name}"
                    mkdir -p "${WORKDIR}/csv_files/${type_name}/${file_name}/"
                    ./au_to_csv/machine_learning.o "${file_path}"
                    cat "${WORKDIR}/csv_files/${type_name}/${file_name}/descriptor.csv" >> "${WORKDIR}/csv_files/datatset.csv"
                    echo "" >> "${WORKDIR}/csv_files/datatset.csv"
                fi
            done
        fi
    done
}

shift
while [ "$1" != "" ]; do
    case $1 in
        -d | --debug )           DEBUG_MODE=1
                                 ;;
        * )                      usage
                                 exit 1
    esac
    shift
done

case ${COMMAND} in 
    'prepare_audio_file')
        prepare_audio_file
        ;;
    'help'|'')
        usage
        ;;
    *)
        echo "Unknow operation: ${COMMAND}"
        usage
        exit 1
        ;;
esac
