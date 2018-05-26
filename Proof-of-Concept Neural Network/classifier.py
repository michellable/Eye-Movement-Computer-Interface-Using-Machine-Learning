#
# classifier.py - A terrible image classifier!
# 
# This runs on Xubuntu Linux 18.4 (from a live USB key, with 8GB RAM).
# This example uses "Eager Execution" and the Keras API
#
# TensorFlow was installed using the following commands:
#
# 	sudo apt install python-pip python-matplotlib
# 	pip install --upgrade tensorflow
#
# This example combines code and syntax from the following...
#
# Iris classification example (4-D feature vectors rather than images):
# 	https://www.tensorflow.org/get_started/eager
#
# Example of importing jpg data (relevant section is "Decoding image data and resizing it"):
# 	https://www.tensorflow.org/programmers_guide/datasets
#
# A good TensorFlow introduction with example:
#	http://cv-tricks.com/artificial-intelligence/deep-learning/deep-learning-frameworks/tensorflow/tensorflow-tutorial/
#
# 

## Import required tensorflow modules
from __future__ import absolute_import, division, print_function

import os
import matplotlib.pyplot as plt

import tensorflow as tf
import tensorflow.contrib.eager as tfe

# Enable eager execution
tf.enable_eager_execution()

print("TensorFlow version: {}".format(tf.VERSION))
print("Eager execution: {}".format(tf.executing_eagerly()))

# Generate lists of filenames and labels which will be used to load data into the neural network
# Filenames and folder lists are needed for containing the list of filenames and the list of label values which will be assigned to each input file
# Filenames are strings and labels are numbers
folders = ['Quadrant_0', 'Quadrant_1', 'Quadrant_2', 'Quadrant_3', 'Quadrant_4']
filenames = []
labels = []

# Lists all of the files in the directory where this program is being run
# The join function takes two strings and joins them together
# Make a list of the number of files in the directory folders and multiply this by the folder number e.g. 0 1 2 3 4. e.g. n=4 and 100 images,
# there would be 400 quad 4 labels. The order of labels needs to match order of the test data. THis basically assigns the proper label to each
# image in the dataset
for n in range(len(folders)):
	folder_files = [os.path.join(folders[n], f) for f in os.listdir(folders[n])]
	filenames = filenames + folder_files
	labels = labels + len(folder_files)*[n] 
# Print count of filenames and labels just for debugging
print('filenames: ' + str(len(filenames)))
print('labels: ' + str(len(labels)))

# Parsing function for examples (example = jpg image + integer label)
# This is the preprocessing by tensorflow before using the data for training.
# The data is stored as an image string and assumes jpeg image format. Due to jpeg being heavily compressed and encoded into compacted encrypted format
# the data must be decoded. The jpeg is decoded and unpacked into pixel values and a 3 dimensional array
# Images are resized to smaller array and the data type of the 3 numbers which identify each pixels changed to a 32 bit float number
# i.e. the data is changed from a byte to 3 dimensional array and each element is a float
# Resized image is taken (3 dim array 28 row 28 col 3 channel per pix) and reshaped into one big long vector(row of numbers)
# In usual application you wouldnt flatten it here you would do it after some convolutional neural network layers.
# Conert label into tensor - datatype that tensorflow expects. A number is converted into a tensor (vector or matrix or 3 dim vector depending)
# Returns all pixel data from original jpg and original label as tensors
def _parse_function(filename, label):
  image_string = tf.read_file(filename) 
  image_decoded = tf.image.decode_jpeg(image_string)  image_resized = tf.image.resize_images(image_decoded, [28, 28]) 
  image_flattened = tf.reshape(image_resized, shape=(28*28*3,)) 
  label = tf.reshape([label], shape=()) 
  return image_flattened, label 

# Convert filenames list and labels to tensors
# Every time take single example is pricesses run the parse function for each example piece of data (each image)
# The batch value is the number of examples that are put through the model at once during training.
filenames = tf.constant(filenames)
labels = tf.constant(labels)
train_dataset = tf.data.Dataset.from_tensor_slices((filenames, labels))
train_dataset = train_dataset.map(_parse_function) 
train_dataset = train_dataset.batch(32)  

# For increased accuracy the dataset would be shuffled. Due to proof-of-concept nature and time constraints, this was not done here.

# Define the structure of the classifier model using Keras.
# Keras is higher level api for developing machine learning models.
# It can be used with tensorflow or other machine learning libraries.
# The input shape is required . dense layers are fully connected. The answer comes out of network in the final layer shown here.
# The whole object is created here and stored as a model. There is 10 neurons in both hidden layers and 5 in the output layer.
# Relu activation function is implemented as shown
model = tf.keras.Sequential([ tf.keras.layers.Dense(10, activation="relu", input_shape=(28*28*3,)),  
  tf.keras.layers.Dense(10, activation="relu"),
  tf.keras.layers.Dense(5) 
]) 

# The loss function matches numbers in the range of minus to plus infinity to the range 0-1 using sigmoid function
# Puts one example into model at a time and looks at output of network and compares to what label should be
# Uses loss function to calculate gradien for tweaking model
def loss(model, x, y): 
	y_ = model(x)
	return tf.losses.sparse_softmax_cross_entropy(labels=y, logits=y_)

# Goes through every node in the network and replays the tape function.
# This function calculates which direction you should change each variable i.e increaseo r decrease based on the slope.
def grad(model, inputs, targets):
	with tf.GradientTape() as tape: 
		loss_value = loss(model, inputs, targets)
	return tape.gradient(loss_value, model.variables)

# Define the optimiser for training the model and declare learning rate (like an incremental sep size).
optimizer = tf.train.GradientDescentOptimizer(learning_rate=0.01) 

# Keep results for plotting results
train_loss_results = []
train_accuracy_results = []

# Go through all examples 101 times during training. One complete run through all of the training examples is one epoch.
# During each epoch, a batch goes in at once i.e 32 test images at a time and then variables are updated
# tfe lets you measure different metrics
num_epochs = 101
for epoch in range(num_epochs):
	epoch_loss_avg = tfe.metrics.Mean() 
	epoch_accuracy = tfe.metrics.Accuracy()

	# Training loop - using batches of 32 images
	for x, y in train_dataset: # 'each x and y is 32 examples due of batch size
		# Optimize the model
		grads = grad(model, x, y) # Calculates gradient for all variables
		optimizer.apply_gradients(zip(grads, model.variables), # Takes all gradients and tweaks all variables accordingly
							  global_step=tf.train.get_or_create_global_step()) # How much to change all the variables based on learning rate

		# Track progress
		epoch_loss_avg(loss(model, x, y))  # Add current batch loss
		# Compare predicted label to actual label
		epoch_accuracy(tf.argmax(model(x), axis=1, output_type=tf.int32), y)

	# End epoch
	train_loss_results.append(epoch_loss_avg.result()) # Taking whatever loss value is and add to list created earlier the train loss results list
	train_accuracy_results.append(epoch_accuracy.result()) # Same as above but for accuracy.
	
	# Print loss and accuracy every 10th epoch
	if epoch % 10 == 0:
		print("Epoch {:03d}: Loss: {:.3f}, Accuracy: {:.3%}".format(epoch,
																epoch_loss_avg.result(),
																epoch_accuracy.result()))

# Display graphs of accuracy and loss versus epochs processed
fig, axes = plt.subplots(2, sharex=True, figsize=(12, 8))
fig.suptitle('Training Metrics')
axes[0].set_ylabel("Loss", fontsize=14)
axes[0].plot(train_loss_results)
axes[1].set_ylabel("Accuracy", fontsize=14)
axes[1].set_xlabel("Epoch", fontsize=14)
axes[1].plot(train_accuracy_results)
plt.show()

# Just quit for now without testing the model due to poor performance of the network
# It needs to be trained more specifically for the test data
quit()

# Test the trained model - NOT IMPLEMENTED YET FOR GAZE IMAGES!

test_url = "http://download.tensorflow.org/data/iris_test.csv"

test_fp = tf.keras.utils.get_file(fname=os.path.basename(test_url),
                                  origin=test_url)

test_dataset = tf.data.TextLineDataset(test_fp)
test_dataset = test_dataset.skip(1)             # skip header row
test_dataset = test_dataset.map(parse_csv)      # parse each row with the funcition created earlier
test_dataset = test_dataset.shuffle(1000)       # randomize
test_dataset = test_dataset.batch(32)           # use the same batch size as the training set

test_accuracy = tfe.metrics.Accuracy()

for (x, y) in test_dataset:
  prediction = tf.argmax(model(x), axis=1, output_type=tf.int32)
  test_accuracy(prediction, y)

print("Test set accuracy: {:.3%}".format(test_accuracy.result()))
