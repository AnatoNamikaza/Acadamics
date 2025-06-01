class Model:
    def __init__(self, layers, loss_fn):
        self.layers = layers
        self.loss_fn = loss_fn

    def forward(self, inputs):
        for layer in self.layers:
            inputs = layer.forward(inputs)
        return inputs

    def backward(self, d_outputs):
        param_list = []
        d_out = d_outputs["d_out"]
        for layer in reversed(self.layers):
            deltas = layer.backward(d_out)
            d_out = deltas["d_out"]
            param_list.append(deltas)
        return param_list

    def update_weights(self, param_list, learning_rate):
        for layer, deltas in zip(reversed(self.layers), param_list):
            if layer.has_weights:
                layer.update(deltas["d_weights"], deltas["d_bias"], learning_rate)

    def train(self, inputs, targets, epochs, learning_rate=0.001, batch_size=10):
        loss_list = []
        for epoch in range(epochs):
            batch_loss_list = []
            for i in range(0, len(inputs), batch_size):
                inputs_batch = inputs[i : i + batch_size]
                targets_batch = targets[i : i + batch_size]

                outputs = self.forward(inputs_batch)
                batch_loss = self.loss_fn.forward(outputs, targets_batch)
                batch_loss_list.append(batch_loss)

                d_outputs = self.loss_fn.backward()
                param_list = self.backward(d_outputs)

                self.update_weights(param_list, learning_rate)
            loss = sum(batch_loss_list) / len(batch_loss_list)
            loss_list.append(loss)
            print(f"Epoch: {epoch + 1}, Loss: {loss:3f}")

        return loss_list

    def predict(self, inputs):
        output = self.forward(inputs)
        return output.argmax(axis=1)
