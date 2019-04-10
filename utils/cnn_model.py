import torch
import torch.nn.functional as F
import torch.optim as optim
import time
import csv
import random
from torch.utils.data.sampler import SubsetRandomSampler
from torch.autograd import Variable

import numpy as np

def createLossAndOptimizer(net, learning_rate=0.001):
    # Loss function
    loss = torch.nn.CrossEntropyLoss()

    # Optimizer
    optimizer = optim.Adam(net.parameters(), lr=learning_rate)

    return (loss, optimizer)


class GaitNN(torch.nn.Module):
    def __init__(self):
        super(GaitNN, self).__init__()

        # Generate 20 independent convolutions for each of our channels
        # (3 * 6 IMU data series + 2 for affected leg FSR), with
        # kernel of size 3.
        self.convs = torch.nn.Conv1d(20, 40, 3, stride=1, padding=1, groups=20)

        # Add a max pool layer to shrink input by 2
        self.pool = torch.nn.MaxPool1d(2)

        self.fc1 = torch.nn.Linear(40 * 10, 32)

        self.fc2 = torch.nn.Linear(32, 3)

    def forward(self, x):
        x = F.relu(self.convs(x))

        x = self.pool(x)

        # Reshape all channels into a single vector
        x = x.view(-1, 40 * 10)

        x = F.relu(self.fc1(x))

        x = self.fc2(x)

        return (x)



def parseCSVDataset(filename):
    with open(filename) as f:
        csv_reader = csv.reader(f, delimiter=',')
        dataSet = []
        for row in  csv_reader:
            channels = []
            for j in range(0, 400, 20):
                feature = row[j : j + 20]
                channels.append([float(x) for x in feature])
            label = row[400]
            dataSet.append((list(channels), label))
    return dataSet


def get_train_loader(train_set, batch_size, train_sampler):
    train_loader = torch.utils.data.DataLoader(train_set, batch_size=batch_size,
                                           sampler=train_sampler, num_workers=2)
    return(train_loader)


labelToIdx = { 'good' : int(0), 'hemiplegic' : int(1), 'dragging' : int(2)}

def trainNet(net, data, batch_size, n_epochs, learning_rate):
    # Print all of the hyperparameters of the training iteration:
    print("===== HYPERPARAMETERS =====")
    print("batch_size=", batch_size)
    print("epochs=", n_epochs)
    print("learning_rate=", learning_rate)
    print("=" * 30)

    # --------------- SAMPLERS -----------------
    # Training
    n_training_samples = int(len(data) * 0.8)
    train_sampler = SubsetRandomSampler(np.arange(n_training_samples, dtype=np.int64))

    # Validation
    n_val_samples = int(len(data) * 0.1)
    val_sampler = SubsetRandomSampler(np.arange(n_training_samples, n_training_samples + n_val_samples, dtype=np.int64))

    # Test
    n_test_samples = int(len(data) * 0.1)
    test_sampler = SubsetRandomSampler(np.arange(n_test_samples, dtype=np.int64))


    # Get training data

    train_loader = get_train_loader(data, batch_size, train_sampler)
    test_loader = torch.utils.data.DataLoader(data, batch_size=1, sampler=test_sampler, num_workers=2)
    val_loader = torch.utils.data.DataLoader(data, batch_size=1, sampler=val_sampler, num_workers=2)

    n_batches = len(train_loader)

    # Create our loss and optimizer functions
    loss, optimizer = createLossAndOptimizer(net, learning_rate)

    # Time for printing
    training_start_time = time.time()

    # Loop for n_epochs
    for epoch in range(n_epochs):

        running_loss = 0.0
        print_every = n_batches // 10
        start_time = time.time()
        total_train_loss = 0

        for i, data in enumerate(train_loader, 0):

            # Get inputs
            inputs, labels = data

            inputs = torch.Tensor(inputs).reshape(batch_size, 20, 20)

            # Wrap them in a Variable object
            inputs = Variable(inputs)
            labels = Variable(torch.LongTensor([int(labelToIdx[x]) for x in labels]))

            # Set the parameter gradients to zero
            optimizer.zero_grad()

            # Forward pass, backward pass, optimize
            outputs = net(inputs)

            loss_size = loss(outputs, labels)
            loss_size.backward()
            optimizer.step()

            # Print statistics
            running_loss += loss_size.item()
            total_train_loss += loss_size.item()

            # Print every 10th batch of an epoch
            if (i + 1) % (print_every + 1) == 0:
                print("Epoch {}, {:d}% \t train_loss: {:.5f} took: {:.2f}s".format(
                    epoch + 1, int(100 * (i + 1) / n_batches), running_loss / print_every, time.time() - start_time))
                # Reset running loss and time
                running_loss = 0.0
                start_time = time.time()

        # At the end of the epoch, do a pass on the validation set
        total_val_loss = 0
        for inputs, labels in val_loader:
            # Wrap tensors in Variables
            inputs = torch.Tensor(inputs).reshape(batch_size, 20, 20)


            # Wrap them in a Variable object
            inputs = Variable(inputs)
            labels = Variable(torch.LongTensor([int(labelToIdx[x]) for x in labels]))


            # Forward pass
            val_outputs = net(inputs)
            val_loss_size = loss(val_outputs, labels)
            total_val_loss += val_loss_size.item()

        print("Validation loss = {:.5f}".format(total_val_loss / len(val_loader)))

    print("Training finished, took {:.2f}s".format(time.time() - training_start_time))


net = GaitNN()

data = parseCSVDataset("combined.csv")
random.shuffle(data)

trainNet(net, data, 1, 2, 0.01)












