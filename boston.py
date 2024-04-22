#!/usr/bin/env python
# coding: utf-8

# In[6]:


import numpy as np
import pandas as pd


# In[9]:


df = pd.read_csv(r"C:\Users\Owner\Desktop\datasets\housing.csv")


# In[10]:


df.head()


# In[11]:


df.columns


# In[13]:


df.shape


# In[14]:


df.isnull().sum()


# In[15]:


df.dropna(inplace=True)


# In[16]:


df.isnull().sum()


# In[17]:


df.describe()


# In[18]:


df.info()


# In[20]:


from sklearn.preprocessing import StandardScaler
X = df.drop('MEDV', axis=1)
y =df['MEDV']
scaler =StandardScaler()
X =scaler.fit_transform(X)


# In[21]:


from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)


# In[22]:


print('Training set shape:', X_train.shape, y_train.shape)
print('Testing set shape:', X_test.shape, y_test.shape)


# In[23]:


import tensorflow.keras as keras
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout


# In[24]:


model = Sequential()
model.add(Dense(1, input_dim=13, activation='linear'))


# In[25]:


print(model.summary())


# In[26]:


model.compile(optimizer = 'adam',loss ='mean_squared_error',metrics=['mae'])
x_val=X_train
y_val=y_train


# In[27]:


history = model.fit(X_train,y_train,epochs=20,batch_size=512,validation_data=(x_val,y_val))


# In[28]:
import matplotlib.pyplot as plt

# Get training history
training_loss = history.history['loss']
validation_loss = history.history['val_loss']

# Plot training and validation loss
epochs = range(1, len(training_loss) + 1)
plt.plot(epochs, training_loss, 'bo', label='Training loss')
plt.plot(epochs, validation_loss, 'r', label='Validation loss')
plt.title('Training and Validation Loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
plt.show()

results = model.evaluate(X_test, y_test)


# In[ ]:




