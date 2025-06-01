import numpy as np


class ReLU:
    def __init__(self):
        self.inputs = None
        self.has_weights = False

    def forward(self, inputs):
        """Forward pass for the ReLU activation function

        Args:
            inputs (np.ndarray):
                input array, can have any shape

        Returns: (np.ndarray):
            array of the same shape as the input
        """

        self.inputs = inputs

        # ================ Insert Code Here ================
        raise NotImplementedError
        # ==================================================

    def backward(self, d_outputs):
        """Backward pass for the ReLU activation function

        Args:
            d_outputs (np.ndarray): array of any shape

        Returns (dict):
            Dictionary containing the derivative of the loss with
            respect to the output of the layer. The key of the dictionary
            should be "d_out"
        """
        # ================ Insert Code Here ================
        raise NotImplementedError
        # ==================================================


class Sigmoid:
    def __init__(self):
        self.inputs = None
        self.has_weights = False

    def forward(self, inputs):
        """Forward pass for the Sigmoid activation function

        Args:
            inputs (np.ndarray):
                input array, can have any shape

        Returns: (np.ndarray):
            array of the same shape as the input
        """

        self.inputs = inputs

        # ================ Insert Code Here ================
        raise NotImplementedError
        # ==================================================

    def backward(self, d_outputs):
        """Backward pass for the Sigmoid activation function

        Args:
            d_outputs (np.ndarray): array of any shape

        Returns (dict):
            Dictionary containing the derivative of the loss with
            respect to the output of the layer. The key of the dictionary
            should be "d_out"
        """

        # ================ Insert Code Here ================
        raise NotImplementedError
        # ==================================================


class Softmax:
    def __init__(self):
        self.inputs = None
        self.has_weights = False

    def forward(self, inputs):
        """Forward pass for the ReLU activation function

        Args:
            inputs (np.ndarray):
                input array, can have any shape

        Returns: (np.ndarray):
            array of the same shape as the input
        """
        self.inputs = inputs

        # ================ Insert Code Here ================
        raise NotImplementedError
        # ==================================================

    def backward(self, d_outputs):
        """Backward pass for the Softmax activation function

        Args:
            d_outputs (np.ndarray): array of any shape

        Returns (dict):
            Dictionary containing the derivative of the loss with
            respect to the output of the layer. The key of the dictionary
            should be "d_out"
        """

        # ================ Insert Code Here ================
        raise NotImplementedError
        # ==================================================
