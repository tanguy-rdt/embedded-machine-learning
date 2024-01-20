import argparse
from sklearn.model_selection import train_test_split

import train_model
import predict

def warn(*args, **kwargs):
    pass
import warnings
warnings.warn = warn


def opt_parse():
    parser = argparse.ArgumentParser()
    
    subparsers = parser.add_subparsers(dest="op_type", required=True, help="Operation to do")

    parser_train = subparsers.add_parser('train', help='Train a model')
    parser_train.add_argument("--dataset", required=True, help="Dataset path")
    parser_train.add_argument("--estimator", nargs='+', choices=['random_forest', 'logistic_regression', 'svm', 'neural_network', 'decision_tree_classifier', 'all'], required=True, help="Estimator type to train")

    parser_predict = subparsers.add_parser('predict', help='Predict using a model')
    parser_predict.add_argument("--dataset", required=True, help="Dataset path for prediction")
    parser_predict.add_argument("--model", required=True, help="Model path")

    args = parser.parse_args()
    return args

opt = opt_parse()
if opt.op_type == 'train':
    train_model.run(opt.dataset, opt.estimator)
elif opt.op_type == 'predict':
    predict.run(opt.dataset, opt.model)