#!/usr/bin/env python
# coding: utf-8

# In[1]:


import pandas as pd
import numpy as np
import tensorflow as tf
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import SimpleRNN, Dense


# In[2]:


data = pd.read_csv(r'C:\Users\Owner\Desktop\datasets\Google_Stock_Price_Train.csv')
data['Date'] = pd.to_datetime(data['Date'])
data = data.sort_values('Date')
data.set_index('Date', inplace=True)
data.info()


# In[6]:


data['Close'] = data['Close'].replace(',', '', regex=True).astype(float)  # Removing commas and converting to float
scaler = MinMaxScaler()
data[['Close']] = scaler.fit_transform(data[['Close']]) 


# In[8]:


# Create sequences
SEQ_LENGTH = 20
def create_sequences(data, seq_length):
    sequences = []
    targets = []

    for i in range(len(data) - seq_length):
        seq = data[i:i+seq_length]
        target = data[i+seq_length]
        sequences.append(seq)
        targets.append(target)
    return np.array(sequences), np.array(targets)
sequences, targets = create_sequences(data['Close'].values, SEQ_LENGTH)


# In[10]:


# Train-test split
X_train, X_test, y_train, y_test = train_test_split(sequences,targets, test_size=0.2, shuffle=True)
# Build the model
model = Sequential([
SimpleRNN(50, input_shape=(SEQ_LENGTH, 1), activation='relu'),
Dense(1)
])
model.compile(optimizer='adam', loss='mse')


# In[11]:


history = model.fit(X_train, y_train, epochs=50, batch_size=32, validation_data=(X_test,y_test))


# In[12]:


predictions = model.predict(X_test)
import matplotlib.pyplot as plt
plt.figure(figsize=(15, 6))
plt.plot(y_test, label='True')
plt.plot(predictions, label='Predicted')
plt.title('Google Stock Price Prediction')
plt.legend()
plt.show()


# In[14]:


import requests
print(requests.get("https://raw.githubusercontent.com/Anagha8302/lp5/master/boston.ipynb").text)

