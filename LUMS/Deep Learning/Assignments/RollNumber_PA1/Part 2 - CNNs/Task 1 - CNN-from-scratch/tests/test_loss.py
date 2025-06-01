import numpy as np

from modules.loss import CrossEntropy

EPSILON = 1e-6


class TestForward:
    def test_one(self):
        """Test forward pass for correctness"""
        cross_entropy = CrossEntropy()
        inputs = np.array([0.6, 0.2, 0.1, 0.1])
        targets = np.array([1, 0, 0, 0])
        loss = cross_entropy.forward(inputs, targets)
        expected_loss = 0.12770640177483103

        assert np.abs(loss - expected_loss) < EPSILON

    def test_two(self):
        """test forward pass for correctness with multi-batch inputs"""
        cross_entropy = CrossEntropy()
        inputs = np.array([[0.6, 0.2, 0.1, 0.1], [0.2, 0.6, 0.1, 0.1]])
        targets = np.array([[1, 0, 0, 0], [0, 1, 0, 0]])
        loss = cross_entropy.forward(inputs, targets)
        expected_loss = 0.5108256070993241

        assert np.abs(loss - expected_loss) < EPSILON

    def test_three(self):
        """test whether forward pass correctly assigns value to
        `self.inputs` and `self.targets`"""

        cross_entropy = CrossEntropy()
        inputs = np.array([0.6, 0.2, 0.1, 0.1])
        targets = np.array([1, 0, 0, 0])
        cross_entropy.forward(inputs, targets)
        assert cross_entropy.inputs is not None
        assert cross_entropy.targets is not None


class TestBackward:
    def test_one(self):
        """Test whether backward pass returns a dictionary with keys 'd_out'"""
        cross_entropy = CrossEntropy()
        inputs = np.array([0.6, 0.2, 0.1, 0.1])
        targets = np.array([1, 0, 0, 0])
        cross_entropy.forward(inputs, targets)
        grad = cross_entropy.backward()
        assert "d_out" in grad
