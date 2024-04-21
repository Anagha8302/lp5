#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
from tensorflow.keras.datasets import imdb
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Embedding, Flatten
from tensorflow.keras.preprocessing import sequence


# In[2]:


max_features = 5000 # Number of words to consider as features
maxlen = 400 # Cut texts after this number of words
batch_size = 32
embedding_dims = 50
epochs = 5


# In[3]:


(x_train, y_train), (x_test, y_test) = imdb.load_data(num_words=max_features)
print(len(x_train), 'train sequences')
print(len(x_test), 'test sequences')


# In[4]:


# Pad sequences to make them all the same length
x_train = sequence.pad_sequences(x_train, maxlen=maxlen)
x_test = sequence.pad_sequences(x_test, maxlen=maxlen)


# In[5]:


# Build the model
model = Sequential()


# In[6]:


# Embedding layer
model.add(Embedding(max_features, embedding_dims, input_length=maxlen))


# In[7]:


# Flatten the 3D tensor to 2D for dense layer
model.add(Flatten())


# In[8]:


# Dense layer
model.add(Dense(256, activation='relu'))
model.add(Dense(1, activation='sigmoid'))


# In[9]:


# Compile the model
model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])


# In[10]:


# Train the model
history = model.fit(x_train, y_train, batch_size=batch_size, epochs=epochs, validation_data=(x_test,y_test))


# In[11]:


results = model.evaluate(x_test, y_test)


# In[ ]:




