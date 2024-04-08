import numpy as np
import pandas as pd
import seaborn as sns
from sklearn.metrics import *
import matplotlib.pyplot as plt

def classification_report(ytrue, ypred):
    print("Confusion matrix :")
    print(confusion_matrix(ytrue,ypred))
    print("Accuracy score : {}".format(accuracy_score(ytrue,ypred)*100))
    print("F1 score : {}".format(f1_score(ytrue, ypred, average='micro')*100))
    print("Recall score : {}".format(recall_score(ytrue, ypred, average='micro')*100))
    print("Sensitivity score : {}".format(precision_recall_fscore_support(ytrue, ypred, average='micro')[0]*100))

def regression_report(ytrue, ypred):
    print("R2 score is: {}".format(r2_score(ytrue,ypred)))
    print("MSE is: {}".format(mean_squared_error(ytrue,ypred)))

    ax = sns.kdeplot(ypred,color='red',label='Predicted')
    sns.kdeplot(ytrue,color='green',label='Original',ax=ax)
    plt.legend()
    plt.show()

def get_correlated_data(dataframe: pd.DataFrame,target_col_name: str ,threshhold: float):
    df = dataframe.copy()
    corrDf = df.corr()[target_col_name]

    for param in corrDf.index:
        if(-threshhold <= corrDf[param] <= threshhold):
            df.drop(columns=[param], inplace=True)
    
    return df

def best_imputator(dataframe):
    print("In progress")

