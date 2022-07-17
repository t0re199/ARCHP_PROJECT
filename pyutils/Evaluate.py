import os
import sys
from optparse import OptionParser

import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import PolynomialFeatures
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score, confusion_matrix, ConfusionMatrixDisplay

from RawIO import *


__RANDOM_STATE__ = 0xd


if __name__ == '__main__':
    np.random.seed(__RANDOM_STATE__)
    
    parser = OptionParser()
    parser.add_option("-d", "--dataset", action="store_true", dest="dataset_name")
    parser.add_option("-p", "--parameters", action="store_true", dest="parameters_path")
    parser.add_option("-deg", "--degree", action="store_true", dest="degree")
    parser.add_option("-sp", "--singlePrecision", action="store_true", dest="single_precision")
    parser.add_option("-dp", "--doublePrecision", action="store_true", dest="double_precision")

    (options, args) = parser.parse_args()
    
    parametersPath =  options.parameters if options.parameters_path is not None else ""
    datasetPath = options.dataset_name + ".data"
    labelsPath = options.dataset_name + ".labels"

    degree = int(options.degree)
    
    single_precision = options.single_precision if options.single_precision is not None else False
    double_precision = options.double_precision if options.double_precision is not None else False

    if single_precision ^ double_precision == 0x0:
        sys.stderr.write("Evaluate.py -h for help\n")
        exit(0x10)

    if degree < 0x1:
        sys.stderr.write("Illegal Polynomium Degree\n")
        exit(0x21)

    if not os.path.isfile(datasetPath):
        sys.stderr.write("Dataset Not Found!\nEvaluate.py -h for help\n")
        exit(0x30)

    if not os.path.isfile(labelsPath):
        sys.stderr.write("Labels Not Found!\nEvaluate.py -h for help\n")
        exit(0x31)

    if not os.path.isfile(parametersPath):
        sys.stderr.write("Parameters Not Found!\nEvaluate.py -h for help\n")
        exit(0x32)


    print("[*] Loading Data.")
    dtype = np.float32 if single_precision else np.float64
    dataset = load(datasetPath, dtype=dtype)
    labels = load(labelsPath, dtype=dtype).reshape(-1)

    print("[*] Fitting Svc.")
    svc = SVC(decision_function_shape="ovo",
              C=0x1,
              gamma=0.001,
              kernel="poly",
              degree=degree)
    
    svc.fit(dataset, labels)
    y_pred_svc = svc.predict(dataset)


    print("[*] Plotting Confusion Matrix.")
   
    svc_accuracy = accuracy_score(labels, y_pred_svc)
    svc_confusion_matrix = confusion_matrix(labels, y_pred_svc)
    display = ConfusionMatrixDisplay(svc_confusion_matrix, display_labels=np.unique(labels)).plot(cmap="Blues")
    display.ax_.set_title(f"SkLearn's SVC Confusion Matrix (Accuracy: {np.round(svc_accuracy, 0x2)})")
    plt.show()



    print("[*] Loading Parameters.")
    parameters = load(parametersPath, dtype=dtype).reshape(-0x1)


    print("[*] Applying Polynomial Embedding.")
    polynial_features = PolynomialFeatures(degree=degree)
    embedded_dataset = polynial_features.fit_transform(dataset)


    print("[*] Generating Hyperplane.")
    polynial_features = PolynomialFeatures(degree=degree)
    embedded_dataset = polynial_features.fit_transform(dataset)

    w = np.zeros(embedded_dataset.shape[0x1], dtype=dtype)

    for i in range(embedded_dataset.shape[0x0]):
        w += parameters[i] * embedded_dataset[i]


    print("[*] Making Prediction.")
    y_pred_sgd = np.ones_like(labels)
    for i in range(embedded_dataset.shape[0x0]):
        if np.dot(w, embedded_dataset[i]) < 1.0:
            y_pred_sgd[i] = -1.0

    sgd_accuracy = accuracy_score(labels, y_pred_sgd)
    custom_confusion_matrix = confusion_matrix(labels, y_pred_sgd)
    display = ConfusionMatrixDisplay(custom_confusion_matrix, display_labels=np.unique(labels)).plot(cmap="Blues")
    display.ax_.set_title(f"Sgd Confusion Matrix (Accuracy: {np.round(sgd_accuracy, 0x2)})")
    plt.show()

    print("[*] Done.")
