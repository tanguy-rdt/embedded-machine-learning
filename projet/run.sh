#!/bin/sh

FILE_NAME=$(readlink -f "$0")
WORKDIR=$(dirname "${FILE_NAME}")

COMMAND=${1}

usage() {
    echo "Usage: $0 [COMMAND]"
    echo "Command:"
    echo "  prepare_audio_file    -- Converte audio file to CSV (time/frequency data and descriptors)"
    echo "  help                  -- Show this message"
}

prepare_audio_file() {
    cd "${WORKDIR}/au_to_csv" || exit
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
                fi
            done
        fi
    done
}

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
