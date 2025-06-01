import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from sklearn.datasets import load_digits
from sklearn.model_selection import train_test_split
import os


FIGURE_PATH = os.path.join(os.getcwd(), "figures")
os.makedirs(FIGURE_PATH, exist_ok=True)


def load_dataset():
    digits = load_digits()

    # Convert target into one-hot encoded format
    target = pd.get_dummies(digits.target)

    # Divide into train-test split
    x_train, x_test, y_train, y_test = train_test_split(
        digits.data, target, test_size=0.2, random_state=42
    )

    x_train = x_train.reshape(-1, 8, 8, 1).transpose(0, 3, 1, 2) / 255
    x_test = x_test.reshape(-1, 8, 8, 1).transpose(0, 3, 1, 2) / 255
    y_train = y_train.to_numpy().reshape(-1, 10)
    y_test = y_test.to_numpy().reshape(-1, 10)

    return x_train, x_test, y_train, y_test


def compute_accuracy(predictions, targets):
    return (predictions == np.argmax(targets, axis=1)).mean()


def plot_history(history):
    plot_path = os.path.join(FIGURE_PATH, "training_loss.png")
    sns.lineplot(x=range(len(history)), y=history)
    plt.xlabel("Epochs")
    plt.ylabel("Loss")
    plt.title("Training Loss")
    plt.savefig(plot_path)
    print(f"Traning loss plot saved at {plot_path}")
    plt.close()


def plot_predictions(x_test, predictions, accuracy):
    plot_path = os.path.join(FIGURE_PATH, "predictions.png")

    fig, axes = plt.subplots(2, 5, figsize=(12, 6))
    fig.suptitle(f"Predictions -- Accuracy: {accuracy:.2%}")

    axes = axes.ravel()

    for i in range(10):
        axes[i].imshow(x_test[i].reshape(8, 8), cmap="gray")
        axes[i].set_title(f"Predicted: {predictions[i]}")
        axes[i].axis("off")

    plt.tight_layout()
    plt.savefig(plot_path)
    print(f"Prediction plot saved at {plot_path}")
    plt.close()


def plot_confusion_matrix(y_test, predictions):
    plot_path = os.path.join(FIGURE_PATH, "confusion_matrix.png")
    confusion_matrix = np.zeros((10, 10))

    for i in range(len(y_test)):
        confusion_matrix[np.argmax(y_test[i])][predictions[i]] += 1

    plt.figure()
    sns.heatmap(confusion_matrix, annot=True, fmt=".0f")
    plt.xlabel("Predicted")
    plt.ylabel("True")
    plt.title("Confusion Matrix")
    plt.savefig(plot_path)
    print(f"Confusion Matrix plot saved at {plot_path}")
