# %%
import numpy as np
import pandas as pd
import seaborn as sns

# %%
data = pd.read_csv('car price.csv')
data.drop(columns=['Unnamed: 0'],inplace=True)
data.head()

# %%
data.info()

# %%
data.describe()

# %%
data.isna().sum()

# %%
x = data
y = data['Price']
categorical = pd.DataFrame()

# %%
from sklearn.preprocessing import LabelEncoder

# %%
label = LabelEncoder()
for i in x.columns:
    if(x[i].dtype == 'object'):
        x[i] = label.fit_transform(x[i])
        categorical[i] = x[i]
categorical

# %%
x.head()

# %%
sns.heatmap(x.corr())

# %%
from scipy import stats

for i in categorical.columns:
    stats.pointbiserialr(categorical[i], y)
    print(i +' '+ str(stats.pointbiserialr(categorical[i], y)[0]))

# %%
x.drop(columns=['Company Name','Model Name','Location','Engine Type','Color'],inplace=True)
x.head()

# %%
sns.heatmap(x.corr())

# %%
x.drop(columns=['Price'],inplace = True)

# %%
x.head()

# %%
from sklearn.preprocessing import StandardScaler
scale = StandardScaler()
linearVar = [['Mileage','Engine Capacity']]
x[['Mileage','Engine Capacity']] = scale.fit_transform(x[['Mileage','Engine Capacity']])

# %%
from sklearn.preprocessing import PolynomialFeatures
poly = PolynomialFeatures(3)
x = poly.fit_transform(x)

# %%
x

# %%
from sklearn.model_selection import train_test_split
xtrain,xtest,ytrain,ytest = train_test_split(x,y,test_size=0.4,random_state=100)

# %%
from sklearn.linear_model import LinearRegression
model = LinearRegression()
model.fit(xtrain,ytrain)
result = model.fit(xtrain,ytrain)

# %%
ypred = model.predict(xtest)

# %%
ax1 = sns.kdeplot(ytest, color = 'r', label = 'Actual Value')
sns.kdeplot(ypred, color = 'b', label = 'Fitted Value', ax = ax1)

# %%
from sklearn.metrics import mean_squared_error,mean_absolute_error,r2_score
resid = ytest - ypred
std_dev = np.std(resid)
rmse = np.sqrt(mean_squared_error(ytest,ypred))
mae = mean_absolute_error(ytest,ypred)
r2 = r2_score(ytest,ypred)

# %%
print('Standard Deviation: ' + str(std_dev))
print('Root mean squared error: ' + str(rmse))
print('Mean absolute error: ' + str(mae))
print('R2 score: ' + str(r2))


