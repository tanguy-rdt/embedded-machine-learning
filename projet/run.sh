#!/bin/bash

FILE_NAME=$(readlink -f "$0")
WORKDIR=$(dirname "${FILE_NAME}")

COMMAND=${1}
shift 

LANG=""

usage() {
    echo "Usage: $0 [COMMAND] [OPTION]"
}

parse_options() {
    while getopts ":l:" opt; do
        case ${opt} in
            l)
                LANG=${OPTARG}
                ;;
            \?)
                echo "Invalid option: -${OPTARG}" >&2
                usage
                exit 1
                ;;
            :)
                echo "Option -${OPTARG} requires an argument." >&2
                usage
                exit 1
                ;;
        esac
    done
    shift $((OPTIND -1))
}

setup_project() {
    cd "${WORKDIR}/cpp" || exit
    cmake -P CMakeClean.cmake
    cmake .
    make 
    cd .. || exit

    #if [ -d "${WORKDIR}/venv" ]; then
    #    rm -rf venv
    #fi
    #python3 -m venv ./venv
    #source venv/bin/activate
    #pip install -r requirements.txt
}

create_dataset() {
    if [ -d "${WORKDIR}/resources/csv_files" ]; then
        rm -r "${WORKDIR}/resources/csv_files"
    fi

    for type_path in "${WORKDIR}/resources/au_files"/*; do
        if [ -d "${type_path}" ]; then
            type_name=$(basename "${type_path}")
            for file_path in "${type_path}"/*.au; do
                if [ -f "${file_path}" ]; then
                    file_name_with_extension=$(basename "${file_path}")
                    file_name=${file_name_with_extension%.au}
                    echo "Prepare au file ${file_name}"
                    mkdir -p "${WORKDIR}/resources/csv_files/${type_name}/${file_name}/"
                    ./cpp/e_machine_learning.o create_dataset "${file_path}" "${WORKDIR}/resources/csv_files/${type_name}/${file_name}/" "${type_name}"
                    cat "${WORKDIR}/resources/csv_files/${type_name}/${file_name}/descriptor.csv" >> "${WORKDIR}/resources/csv_files/dataset.csv"
                    echo "" >> "${WORKDIR}/resources/csv_files/dataset.csv"
                fi
            done
        fi
    done
}

train_model(){
    if [ -z "${LANG}" ]; then
        echo "Language is required for prediction"
        usage
        exit 1
    fi
    
    source venv/bin/activate
    python ${WORKDIR}/python/main.py train --dataset 'resources/csv_files/dataset.csv' --estimator all
}

predict(){
    if [ -z "${LANG}" ]; then
        echo "Language is required for prediction"
        usage
        exit 1
    fi

    if [ "${LANG}" = "cpp" ]; then
        ./cpp/e_machine_learning.o predict "resources/csv_files/dataset_test.csv" "resources/scaler.txt" "random_forest" "decision_tree" "linear_svc"
    elif [ "${LANG}" = "python" ]; then 
        source venv/bin/activate
        python ${WORKDIR}/python/main.py predict --dataset 'resources/csv_files/dataset_test.csv' --model 'resources/model_python/LinearSVC.joblib'
    else 
        echo "Unknow language"
    fi
}

case ${COMMAND} in 
    'setup_project')
        setup_project
        ;;
    'create_dataset')
        create_dataset
        ;;
    'train_model')
        parse_options "$@"
        train_model
        ;;
    'predict')
        parse_options "$@"
        predict
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
