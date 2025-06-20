from torch import no_grad
from torch.utils.data import DataLoader


"""
Functions you should use.
Please avoid importing any other functions or modules.
Your code will not pass if the gradescope autograder detects any changed imports
"""
from torch import optim, tensor
from losses import regression_loss, digitclassifier_loss, languageid_loss, digitconvolution_Loss
from torch import movedim
import torch

"""
##################
### QUESTION 1 ###
##################
"""


def train_perceptron(model, dataset):
    """
    Train the perceptron until convergence.
    You can iterate through DataLoader in order to 
    retrieve all the batches you need to train on.

    Each sample in the dataloader is in the form {'x': features, 'label': label} where label
    is the item we need to predict based off of its features.
    """
    with no_grad():
        dataloader = DataLoader(dataset, batch_size=1, shuffle=True)
        while True:
            all_correct = True
            for batch in dataloader:
                x = batch['x']
                y = batch['label']

                pred = model.get_prediction(x)

                if pred.item() != y.item():
                    # Atualiza os pesos
                    model.w += x.squeeze() * y.item()
                    all_correct = False

            if all_correct:
                break


def train_regression(model, dataset):
    """
    Trains the model.

    In order to create batches, create a DataLoader object and pass in `dataset` as well as your required 
    batch size. You can look at PerceptronModel as a guideline for how you should implement the DataLoader

    Each sample in the dataloader object will be in the form {'x': features, 'label': label} where label
    is the item we need to predict based off of its features.

    Inputs:
        model: Pytorch model to use
        dataset: a PyTorch dataset object containing data to be trained on
        
    """
    LRATE = 0.01
    MAX_EPOCHS = 5000
    BREAK_THRES = 0.015

    dataloader = DataLoader(dataset, batch_size=32, shuffle=True)
    optimizer = optim.Adam(model.parameters(), LRATE)

    for epoch in range(MAX_EPOCHS):
        total_loss = 0.0

        for batch in dataloader:
            x = batch['x']
            y = batch['label']

            predictions = model(x)
            loss = regression_loss(predictions, y)

            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

            total_loss += loss.item()

        avg_loss = total_loss / len(dataloader)
        if avg_loss < BREAK_THRES:
            break
         

def train_digitclassifier(model, dataset):
    """
    Trains the model.
    """
    model.train()
    LRATE = 0.001
    MAX_EPOCHS = 15
    BREAK_THRES = 0.975

    dataloader = DataLoader(dataset, batch_size=64, shuffle=True)
    optimizer = optim.Adam(model.parameters(), LRATE)

    for epoch in range(MAX_EPOCHS):
        for batch in dataloader:
            x = batch['x']
            y = batch['label']

            predictions = model(x)
            loss = digitclassifier_loss(predictions, y)

            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

        # Verifica acurácia do treinamento
        model.eval()
        accuracy = dataset.get_validation_accuracy()
        model.train()

        if accuracy >= BREAK_THRES:
            break


def train_languageid(model, dataset):
    """
    Trains the model.

    Note that when you iterate through dataloader, each batch will returned as its own vector in the form
    (batch_size x length of word x self.num_chars). However, in order to run multiple samples at the same time,
    get_loss() and run() expect each batch to be in the form (length of word x batch_size x self.num_chars), meaning
    that you need to switch the first two dimensions of every batch. This can be done with the movedim() function 
    as follows:

    movedim(input_vector, initial_dimension_position, final_dimension_position)

    For more information, look at the pytorch documentation of torch.movedim()
    """
    model.train()
    LRATE = 0.001
    MAX_EPOCHS = 25

    dataloader = DataLoader(dataset, batch_size=32, shuffle=True)
    optimizer = optim.Adam(model.parameters(), LRATE)

    for epoch in range(MAX_EPOCHS):
        for batch in dataloader:
            x = batch['x']
            y = batch['label']

            x_moved = movedim(x, 1, 0)
            predictions = model(x_moved)
            loss = languageid_loss(predictions, y)

            optimizer.zero_grad()
            loss.backward()
            optimizer.step()



def Train_DigitConvolution(model, dataset):
    """
    Trains the model.
    """
    LRATE = 0.001
    MAX_EPOCHS = 20
    BREAK_THRES = 0.80

    dataloader = DataLoader(dataset, batch_size=32, shuffle=True)
    optimizer = optim.Adam(model.parameters(), LRATE)

    for epoch in range(MAX_EPOCHS):
        for batch in dataloader:
            x = batch['x']
            y = batch['label']
            
            predictions = model(x)
            loss = digitconvolution_Loss(predictions, y)

            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

        # Verifica acurácia do treinamento
        model.eval()
        accuracy = dataset.get_validation_accuracy()
        model.train()

        if accuracy >= BREAK_THRES:
            break
