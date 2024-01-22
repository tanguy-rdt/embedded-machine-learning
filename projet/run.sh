#!/bin/bash

FILE_NAME=$(readlink -f "$0")
WORKDIR=$(dirname "${FILE_NAME}")

COMMAND=${1}
shift 

DEBUG=false
TARGET=false
LANG=""

usage() {
    echo "Usage: $0 [COMMAND] [OPTION]"
}

parse_options() {
    while getopts ":l:td" opt; do
        case ${opt} in
            l)
                LANG=${OPTARG}
                ;;
            t)
                TARGET=true
                ;;
            d)
                DEBUG=true
                ;;
            \?)
                echo "ERROR -- Invalid option: -${OPTARG}" >&2
                usage
                exit 1
                ;;
            :)
                echo "ERROR - Option -${OPTARG} requires an argument." >&2
                usage
                exit 1
                ;;
        esac
    done
    shift $((OPTIND -1))
}

setup_project() {
    if [ ! -d "${WORKDIR}/build" ]; then
        mkdir "${WORKDIR}/build"
    else 
        rm -r "${WORKDIR}/build"
    fi
    

    if [ "${TARGET}" = true ]; then
        cmake -DCOMPILE_FOR_RPI=ON -S "${WORKDIR}/cpp/" -B "${WORKDIR}/build/"
    else
        if [ "${DEBUG}" = true ]; then
            cmake -DDEBUG=ON  -S "${WORKDIR}/cpp/" -B "${WORKDIR}/build/"
        else
            cmake  -S "${WORKDIR}/cpp/" -B "${WORKDIR}/build/"
        fi

        if [ -d !"${WORKDIR}/venv" ]; then
            python3 -m venv ${WORKDIR}/venv
        fi
        source ${WORKDIR}/venv/bin/activate
        pip install -r ${WORKDIR}/requirements.txt
    fi

    make -C "${WORKDIR}/build/"
}

create_dataset() {
    if [ -d "${WORKDIR}/resources/csv_files" ]; then
        rm -r "${WORKDIR}/resources/csv_files"
    fi

    if [ "${DEBUG}" = true ]; then
        ./build/e_machine_learning.o create_dataset "${WORKDIR}/resources/au_files/blues/blues.00000.au" "${WORKDIR}/resources/csv_files/debug.csv" "blues"
        exit
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
                    ./build/e_machine_learning.o create_dataset "${file_path}" "${WORKDIR}/resources/csv_files/${type_name}/${file_name}/" "${type_name}"
                    cat "${WORKDIR}/resources/csv_files/${type_name}/${file_name}/descriptor.csv" >> "${WORKDIR}/resources/csv_files/dataset.csv"
                    echo "" >> "${WORKDIR}/resources/csv_files/dataset.csv"
                fi
            done
        fi
    done
}

train_model(){
    source ${WORKDIR}/venv/bin/activate
    python ${WORKDIR}/python/main.py train --dataset "${WORKDIR}/resources/csv_files/dataset.csv" --estimator all
}

predict(){
    if [ -z "${LANG}" ]; then
        echo "ERROR -- Language is required for prediction"
        usage
        exit 1
    fi

    if [ "${LANG}" = "cpp" ]; then
        ./build/e_machine_learning.o predict "${WORKDIR}/resources/csv_files/dataset_test.csv" "${WORKDIR}/resources/scaler.txt" "random_forest" "decision_tree" "linear_svc" "neural_network"
    elif [ "${LANG}" = "python" ]; then 
        source ${WORKDIR}/venv/bin/activate
        python ${WORKDIR}/python/main.py predict --dataset "${WORKDIR}/resources/csv_files/dataset_test.csv" --model "${WORKDIR}/resources/model/RandomForestClassifier.joblib"
        python ${WORKDIR}/python/main.py predict --dataset "${WORKDIR}/resources/csv_files/dataset_test.csv" --model "${WORKDIR}/resources/model/DecisionTreeClassifier.joblib"
        python ${WORKDIR}/python/main.py predict --dataset "${WORKDIR}/resources/csv_files/dataset_test.csv" --model "${WORKDIR}/resources/model/LinearSVC.joblib"
        python ${WORKDIR}/python/main.py predict --dataset "${WORKDIR}/resources/csv_files/dataset_test.csv" --model "${WORKDIR}/resources/model/NeuralNetwork.tflite"
    else 
        echo "ERROR -- opt -l, Unknow language"
    fi
}

case ${COMMAND} in 
    'setup_project')
        parse_options "$@"
        setup_project
        ;;
    'create_dataset')
        parse_options "$@"
        create_dataset
        ;;
    'train_model')
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
        echo "ERROR -- Unknow operation: ${COMMAND}"
        usage
        exit 1
        ;;
esac
