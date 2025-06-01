import numpy as np
import matplotlib.pyplot as plt

def generate_problem(problem_id):
    """Generate a dataset for the given problem ID (1 to 8)."""
    np.random.seed(42)  # Seed for reproducibility
    
    if problem_id == 1:
        X = np.random.randn(1000, 2) * 2
        y = (X[:, 0] + X[:, 1] > 0).astype(int)
        title = "Linear Separation"
        
    elif problem_id == 2:
        X = np.random.randn(1000, 2) * 2
        radius = np.sqrt(X[:, 0]**2 + X[:, 1]**2)
        y = (radius > 3).astype(int)
        title = "Circular Boundary"
        
    elif problem_id == 3:
        X = np.random.randn(1000, 2) * 1.5
        y = (np.sign(X[:, 0] * X[:, 1]) > 0).astype(int)
        title = "XOR Pattern"
        
    elif problem_id == 4:
        theta = np.linspace(0, 4 * np.pi, 500)
        r = np.linspace(0.5, 5, 500)
        X1 = np.vstack([r * np.cos(theta), r * np.sin(theta)]).T
        X2 = np.vstack([r * np.cos(theta + np.pi), r * np.sin(theta + np.pi)]).T
        X = np.vstack([X1, X2])
        y = np.hstack([np.zeros(500), np.ones(500)])
        title = "Spiral Pattern"
        
    elif problem_id == 5:
        t = np.linspace(0, 2 * np.pi, 500)
        X1 = np.vstack([3 * np.cos(t) + 1.5, 3 * np.sin(t)]).T
        X2 = np.vstack([3 * np.cos(t) + 4.5, 3 * np.sin(t) + 1.5]).T
        X = np.vstack([X1, X2]) + np.random.randn(1000, 2) * 0.3
        y = np.hstack([np.zeros(500), np.ones(500)])
        title = "Moon Pattern"
        
    elif problem_id == 6:
        X1 = np.random.randn(500, 2) + [2, 2]
        X2 = np.random.randn(500, 2) - [2, 2]
        X = np.vstack([X1, X2])
        y = np.hstack([np.zeros(500), np.ones(500)])
        title = "Gaussian Mixture"
        
    elif problem_id == 7:
        xx, yy = np.meshgrid(np.linspace(-5, 5, 40), np.linspace(-5, 5, 40))
        X = np.vstack([xx.ravel(), yy.ravel()]).T
        y = ((xx.ravel() + yy.ravel()) % 4 > 2).astype(int)
        title = "Checkerboard"
        
    elif problem_id == 8:
        X = np.random.randn(1000, 2) * 3
        y = (np.random.rand(1000) > 0.5).astype(int)
        title = "High Noise"
        
    else:
        raise ValueError("Invalid problem_id. Choose 1-8.")
    
    return X, y, title
