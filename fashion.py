#!/usr/bin/env python
# coding: utf-8

# In[1]:


from tensorflow.keras.datasets import fashion_mnist


# In[2]:


(train_x, train_y), (test_x, test_y) = fashion_mnist.load_data()


# In[3]:


from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Flatten, MaxPooling2D, Conv2D


# In[4]:


model = Sequential()


# In[5]:


model.add(Conv2D(filters=64,kernel_size=(3,3),activation='relu',input_shape=(28, 28, 1)))

model.add(MaxPooling2D(pool_size=(2,2)))

model.add(Flatten())
model.add(Dense(128, activation = "relu"))
model.add(Dense(10, activation = "softmax"))


# In[6]:


model.summary()


# In[7]:


model.compile(optimizer = 'adam', loss = 'sparse_categorical_crossentropy', metrics = ['accuracy'])


# In[9]:


import numpy as np
model.fit(train_x.astype(np.float32), train_y.astype(np.float32), epochs = 5, validation_split = 0.2)


# In[10]:


loss, acc = model.evaluate(test_x, test_y)


# In[11]:


labels = ['t_shirt', 'trouser', 'pullover', 'dress', 'coat', 'sandal', 'shirt', 'sneaker',   'bag', 'ankle_boots']


# In[13]:


predictions = model.predict(test_x[:1])


# In[14]:


label = labels[np.argmax(predictions)]


# In[15]:


import matplotlib.pyplot as plt
print(label)
plt.imshow(test_x[:1][0])
plt.show


# In[ ]:




