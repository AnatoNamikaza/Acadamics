import sys
import numpy as np

from modules.layers import ConvolutionLayer

EPSILON = 1e-6


class TestForward:
    def test_one(self):
        """Tests whether the forward pass gives the correct output shape with stride == 1"""
        input_shape = (3, 8, 8)
        num_filters = 5
        conv_layer = ConvolutionLayer(3, num_filters, 3)
        batch_size = 4
        input_data = np.random.randn(batch_size, *input_shape)
        output = conv_layer.forward(input_data)
        expected_output_shape = (batch_size, num_filters, 6, 6)
        assert output.shape == expected_output_shape

    def test_two(self):
        """Tests whether the forward pass gives the correct output shape
        with stride == 2"""

        input_shape = (3, 8, 8)
        num_filters = 5
        conv_layer = ConvolutionLayer(3, num_filters, 3, stride=2)
        batch_size = 1
        input_data = np.random.randn(batch_size, *input_shape)

        output = conv_layer.forward(input_data)
        expected_output_shape = (batch_size, num_filters, 3, 3)
        assert output.shape == expected_output_shape

    def test_three(self):
        """Tests whether the forward pass function correctly assignes value
        to `self.inputs`"""

        input_shape = (3, 8, 8)
        num_filters = 5
        conv_layer = ConvolutionLayer(3, num_filters, 3, stride=3)
        batch_size = 1
        input_data = np.random.randn(batch_size, *input_shape)

        conv_layer.forward(input_data)
        assert conv_layer.inputs is not None

    def test_four(self):
        """Tests the forward pass function for correctness given a specific
        input and weights"""

        input_shape = (1, 3, 3)
        num_filters = 1
        conv_layer = ConvolutionLayer(1, num_filters, 2, stride=1)
        conv_layer.weights = np.array([[[[1, 2], [3, 4]]]])
        conv_layer.bias = np.array([1])

        input_array = np.arange(9).reshape(1, *input_shape)
        expected_output = np.array([[[[28, 38], [58, 68]]]])
        output = conv_layer.forward(input_array)
        assert np.linalg.norm(output - expected_output) < EPSILON

class TestBackward:
    def test_one(self):
        """Tests whether output of backward pass is a dictionary
        with keys 'd_out', 'd_weights', and 'd_bias'"""

        input_shape = (3, 8, 8)
        num_filters = 5
        conv_layer = ConvolutionLayer(3, num_filters, 3, stride=3)
        batch_size = 1
        input_data = np.random.randn(batch_size, *input_shape)
        conv_layer.forward(input_data)
        d_output = np.random.randn(batch_size, num_filters, 2, 2)
        d_params = conv_layer.backward(d_output)
        assert "d_out" in d_params
        assert "d_weights" in d_params
        assert "d_bias" in d_params

    def test_two(self):
        """Tests whether the shapes of the gradients are correct"""

        input_shape = (3, 8, 8)
        num_filters = 5
        conv_layer = ConvolutionLayer(3, num_filters, 3, stride=3)
        batch_size = 1
        input_data = np.random.randn(batch_size, *input_shape)
        conv_layer.forward(input_data)
        d_output = np.random.randn(batch_size, num_filters, 2, 2)
        d_params = conv_layer.backward(d_output)
        assert d_params["d_out"].shape == input_data.shape
        assert d_params["d_weights"].shape == conv_layer.weights.shape
        assert d_params["d_bias"].shape == conv_layer.bias.shape

    def test_three(self):
        """Tests backward pass for correctness given a specific input and weights"""

        input_shape = (1, 3, 3)
        num_filters = 1
        conv_layer = ConvolutionLayer(1, num_filters, 2, stride=1)

        conv_layer.weights = np.ones(conv_layer.weights.shape, dtype=np.float32) * 2
        conv_layer.bias = np.array([1.0], dtype=np.float32)

        input_array = np.arange(9, dtype=np.float32).reshape(1, *input_shape)
        conv_layer.forward(input_array)

        d_output = np.array([[[[1, 2], [3, 4]]]], dtype=np.float32)
        params = conv_layer.backward(d_output)

        expected_d_weights = np.array([[[[27, 37], [57, 67]]]], dtype=np.float32)
        expected_d_bias = np.array([10], dtype=np.float32)

        expected_d_out = np.array(
            [[[[2, 6, 4], [8, 20, 12], [6, 14, 8]]]], dtype=np.float32
        )

        assert np.linalg.norm(params["d_weights"] - expected_d_weights) < EPSILON
        assert np.linalg.norm(params["d_bias"] - expected_d_bias) < EPSILON
        assert np.linalg.norm(params["d_out"] - expected_d_out) < EPSILON
