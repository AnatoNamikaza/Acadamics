import numpy as np

from modules.layers import LinearLayer

EPSILON = 1e-6


class TestForward:
    def test_one(self):
        """Tests whether the forward pass gives the correct output shape"""
        in_features = 3
        out_features = 5
        linear_layer = LinearLayer(in_features, out_features)
        batch_size = 4
        input_data = np.random.randn(batch_size, in_features)
        output = linear_layer.forward(input_data)
        expected_output_shape = (batch_size, out_features)
        assert output.shape == expected_output_shape

    def test_two(self):
        """Tests whether the forward pass function correctly assignes value
        to `self.inputs`"""

        in_features = 3
        out_features = 5
        linear_layer = LinearLayer(in_features, out_features)
        batch_size = 1
        input_data = np.random.randn(batch_size, in_features)

        linear_layer.forward(input_data)
        assert linear_layer.inputs is not None

    def test_three(self):
        """Tests the forward pass function for correctness given a specific
        input and weights"""

        in_features = 3
        out_features = 2
        linear_layer = LinearLayer(in_features, out_features)
        linear_layer.weights = np.array([[1, 2, 3], [4, 5, 6]])
        linear_layer.bias = np.array([1, 2])

        input_array = np.array([[1, 2, 3]])
        expected_output = np.array([[15, 34]])
        output = linear_layer.forward(input_array)
        assert np.linalg.norm(output - expected_output) < EPSILON


class TestBackward:
    def test_one(self):
        """Test whether backward pass returns dictionary
        with keys 'd_out', 'd_weights', and 'd_bias'"""
        in_features = 3
        out_features = 5
        linear_layer = LinearLayer(in_features, out_features)
        batch_size = 4
        input_data = np.random.randn(batch_size, in_features)
        output = linear_layer.forward(input_data)
        d_output = np.random.randn(batch_size, out_features)
        grad = linear_layer.backward(d_output)
        assert "d_out" in grad.keys()
        assert "d_weights" in grad.keys()
        assert "d_bias" in grad.keys()

    def test_two(self):
        """Tests whether the backward pass gives the correct output shape"""
        in_features = 3
        out_features = 5
        linear_layer = LinearLayer(in_features, out_features)
        batch_size = 4
        input_data = np.random.randn(batch_size, in_features)
        output = linear_layer.forward(input_data)
        d_output = np.random.randn(batch_size, out_features)
        grad = linear_layer.backward(d_output)
        expected_output_shape = (batch_size, in_features)
        assert grad["d_out"].shape == expected_output_shape

    def test_three(self):
        """Tests the backward pass for correctness"""

        in_features = 3
        out_features = 2
        linear_layer = LinearLayer(in_features, out_features)
        linear_layer.weights = np.array([[1, 2, 3], [4, 5, 6]])
        linear_layer.bias = np.array([1, 2])

        input_array = np.array([[1, 2, 3]])
        linear_layer.forward(input_array)
        d_output = np.array([[1, 2]])
        grad = linear_layer.backward(d_output)

        expected_d_weights = np.array([[1, 2, 3], [2, 4, 6]])
        expected_d_bias = np.array([1, 2])
        expected_d_out = np.array([[9, 12, 15]])

        print(grad["d_weights"])
        print(grad["d_bias"])
        print(grad["d_out"])

        assert np.linalg.norm(grad["d_weights"] - expected_d_weights) < EPSILON
        assert np.linalg.norm(grad["d_bias"] - expected_d_bias) < EPSILON
        assert np.linalg.norm(grad["d_out"] - expected_d_out) < EPSILON
