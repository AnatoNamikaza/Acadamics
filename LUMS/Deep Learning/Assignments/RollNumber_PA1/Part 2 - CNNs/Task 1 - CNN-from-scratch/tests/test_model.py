from modules.layers import LinearLayer, ConvolutionLayer, Flatten
from modules.loss import CrossEntropy
from modules.activation import ReLU, Softmax
from modules.model import Model

from utils import load_dataset, compute_accuracy


class TestAccuracy:

    def test_one(self):
        """Test a model for getting accuracy > 90%"""
        x_train, x_test, y_train, y_test = load_dataset()

        layer_list = [
            ConvolutionLayer(in_channels=1, out_channels=3, kernel_size=5),
            ReLU(),
            Flatten(),
            LinearLayer(48, 10),
            Softmax(),
        ]

        model = Model(layer_list, CrossEntropy())

        model.train(x_train, y_train, 25, 0.01, 32)

        predictions = model.predict(x_test)
        accuracy = compute_accuracy(predictions, y_test)

        assert accuracy > 0.9
