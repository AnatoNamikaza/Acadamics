import numpy as np


class ConvolutionLayer:
    def __init__(self, in_channels, out_channels, kernel_size, stride=1):
        self.in_channels = in_channels
        self.out_channels = out_channels
        self.kernel_size = kernel_size
        self.stride = stride

        self.weights = np.random.rand(
            out_channels, in_channels, kernel_size, kernel_size
        ).astype(np.float32)
        self.bias = np.random.rand(out_channels).astype(np.float32)

        self.inputs = None
        self.has_weights = True

    def forward(self, inputs):
        """Forward pass for a convolution layer

        Args:
            inputs (np.ndarray):
                array of shape
                (batch_size, in_channels, height, width)

        Returns: (np.ndarray):
            array of shape
            (batch_size, out_channels, new_height, new_width)
        """

        self.inputs = inputs

        # ================ Insert Code Here ================
        raise NotImplementedError
        # ==================================================

    def backward(self, d_outputs):
        """Backward pass of convolution layer

        Args:
            d_outputs (np.ndarray):
                derivative of loss with respect to the output
                of the layer. Will have shape
                (batch_size, out_channels, new_height, new_width)

        Returns: (dict):
            Dictionary containing the derivatives of loss with respect to
            the weights and bias and input of the layer. The keys of
            the dictionary should be "d_weights", "d_bias", and "d_out"

        """

        self.inputs = None
        if self.inputs is None:
            raise NotImplementedError(
                "Need to call forward function before backward function"
            )

        # ================ Insert Code Here ================
        raise NotImplementedError
        # ==================================================

    def update(self, d_weights, d_bias, learning_rate):

        # ================ Insert Code Here ================
        raise NotImplementedError
        # ==================================================


class Flatten:
    def __init__(self):
        self.inputs_shape = None
        self.has_weights = False

    def forward(self, inputs):
        self.inputs_shape = inputs.shape
        return inputs.reshape(inputs.shape[0], -1)

    def backward(self, d_outputs):
        return {"d_out": d_outputs.reshape(self.inputs_shape)}


class LinearLayer:
    def __init__(self, in_features, out_features):
        self.in_features = in_features
        self.out_features = out_features

        self.weights = np.random.rand(out_features, in_features).astype(np.float32)
        self.bias = np.random.rand(out_features).astype(np.float32)

        self.inputs = None
        self.has_weights = True

    def forward(self, inputs):
        """Forward pass for a linear layer

        Args:
            inputs (np.ndarray):
                array of shape (batch_size, in_features)

        Returns: (np.ndarray):
            array of shape (batch_size, out_features)
        """

        # ================ Insert Code Here ================
        raise NotImplementedError
        # ==================================================

    def backward(self, d_outputs):
        """Backward pass of Linear layer

        Args:
            d_outputs (np.ndarray):
                derivative of loss with respect to the output
                of the layer. Will have shape
                (batch_size, out_features)

        Returns: (dict):
            Dictionary containing the derivatives of loss with respect to
            the weights and bias and input of the layer. The keys of
            the dictionary should be "d_weights", "d_bias", and "d_out"
        """
        if self.inputs is None:
            raise NotImplementedError("Need to call forward function before backward function")
        
        # ================ Insert Code Here ================
        raise NotImplementedError
        # ==================================================

    def update(self, d_weights, d_bias, learning_rate):

        # ================ Insert Code Here ================
        raise NotImplementedError
        # ==================================================
