import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import confusion_matrix, classification_report

# Step 1: Generate a random dataset
# TODO: Generate a random dataset with features and labels
# Hint: You can use numpy.random functions to create synthetic data

# Step 2: Data Preprocessing
# TODO: Perform data preprocessing steps such as splitting the data into train and test sets,
# standardizing the features, etc.
# Hint: Use train_test_split and StandardScaler from scikit-learn

# Step 3: Visualization
# TODO: Visualize the dataset using scatter plots or any other suitable visualization technique
# Hint: Use matplotlib for visualization

# Step 4: Classification
# TODO: Train a Random Forest Classifier on the dataset
# Hint: Use RandomForestClassifier from scikit-learn

# Step 5: Model Evaluation
# TODO: Evaluate the trained model using confusion matrix and classification report
# Hint: Use confusion_matrix and classification_report from scikit-learn

# Step 6: Optional - Parameter Tuning
# TODO: Perform parameter tuning on the Random Forest Classifier and evaluate the performance
# Hint: Use GridSearchCV from scikit-learn for parameter tuning

# Step 7: Optional - Feature Importance
# TODO: Determine the most important features using feature_importances_ attribute of the trained model
# Hint: Use feature_importances_ attribute of RandomForestClassifier

# Step 8: Optional - Visualization of Decision Trees
# TODO: Visualize the decision trees in the Random Forest Classifier
# Hint: Use plot_tree function from scikit-learn or any other visualization tool

# Step 9: Optional - Additional Analysis
# TODO: Perform any additional analysis or experiments on the dataset to gain insights
# Hint: You can explore different algorithms, experiment with different parameters, etc.

# Step 10: Conclusion
# TODO: Write a conclusion summarizing the findings and insights gained from the analysis

# Step 11: Bonus - Interactive Visualization (Optional)
# TODO: Create an interactive visualization tool using libraries such as Plotly or Bokeh
# Hint: Interactive visualization can provide a more engaging way to explore the data and results

# Step 12: Bonus - Presentation (Optional)
# TODO: Prepare a presentation summarizing the lab assignment and present it to the class
# Hint: Include key findings, visualizations, and insights in the presentation

# Step 13: Bonus - Peer Review (Optional)
# TODO: Conduct a peer review of other students' work and provide constructive feedback
# Hint: Evaluate the clarity, correctness, and completeness of their analysis and code

# Step 14: Bonus - Reflection (Optional)
# TODO: Reflect on your own learning experience from the lab assignment
# Hint: Write down any challenges faced, lessons learned, and areas for improvement

# Step 15: Bonus - Further Exploration (Optional)
# TODO: Explore additional topics or datasets related to data mining that were not covered in this lab assignment
# Hint: Look for online resources, research papers, or tutorials to expand your knowledge further

# Step 16: Bonus - Sharing (Optional)
# TODO: Share your findings, code, and insights with your peers or on social media platforms
# Hint: Share your code on GitHub or create a blog post discussing your analysis and results

# Step 17: Bonus - Continuous Learning (Optional)
# TODO: Keep exploring new techniques, algorithms, and datasets in the field of data mining
# Hint: Attend workshops, conferences, or online courses to stay updated with the latest developments

# Step 18: Bonus - Collaboration (Optional)
# TODO: Collaborate with classmates or researchers to work on real-world projects or competitions
# Hint: Join data science communities, forums, or meetups to connect with like-minded individuals

# Step 19: Bonus - Feedback (Optional)
# TODO: Provide feedback to the instructor on the lab assignment, including suggestions for improvement
# Hint: Reflect on the clarity, relevance, and effectiveness of the lab tasks and materials

# Step 20: End of Lab
print("End of Lab")


#-------------------------------------------------------------------------------------------------------------------------------------
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import confusion_matrix, classification_report
from sklearn.datasets import load_iris  # For using Iris dataset

# Step 1: Load the dataset
def load_dataset():
    iris = load_iris()
    data = pd.DataFrame(data= np.c_[iris['data'], iris['target']],
                        columns= iris['feature_names'] + ['target'])
    return data

# Step 2: Data Preprocessing
def preprocess_data(data):
    X = data.drop('target', axis=1)
    y = data['target']
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
    scaler = StandardScaler()
    X_train_scaled = scaler.fit_transform(X_train)
    X_test_scaled = scaler.transform(X_test)
    return X_train_scaled, X_test_scaled, y_train, y_test

# Step 3: Visualization
def visualize_data(data):
    # Visualize the dataset (for simplicity, only visualizing the first two features)
    plt.scatter(data[data['target'] == 0]['sepal length (cm)'],
                data[data['target'] == 0]['sepal width (cm)'],
                label='Setosa', color='r')
    plt.scatter(data[data['target'] == 1]['sepal length (cm)'],
                data[data['target'] == 1]['sepal width (cm)'],
                label='Versicolor', color='g')
    plt.scatter(data[data['target'] == 2]['sepal length (cm)'],
                data[data['target'] == 2]['sepal width (cm)'],
                label='Virginica', color='b')
    plt.xlabel('Sepal Length (cm)')
    plt.ylabel('Sepal Width (cm)')
    plt.title('Scatter plot of Sepal Length vs Sepal Width')
    plt.legend()
    plt.show()

# Step 4: Classification
def train_classifier(X_train, y_train):
    clf = RandomForestClassifier(n_estimators=100, random_state=42)
    clf.fit(X_train, y_train)
    return clf

# Step 5: Model Evaluation
def evaluate_model(clf, X_test, y_test):
    y_pred = clf.predict(X_test)
    print("Confusion Matrix:")
    print(confusion_matrix(y_test, y_pred))
    print("\nClassification Report:")
    print(classification_report(y_test, y_pred))

def main():
    # Step 1: Load the dataset
    data = load_dataset()

    # Step 2: Data Preprocessing
    X_train, X_test, y_train, y_test = preprocess_data(data)

    # Step 3: Visualization
    visualize_data(data)

    # Step 4: Classification
    clf = train_classifier(X_train, y_train)

    # Step 5: Model Evaluation
    evaluate_model(clf, X_test, y_test)

if __name__ == "__main__":
    main()

#--------------------------------------------------------------------------------------------------------
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import confusion_matrix, classification_report
from sklearn.model_selection import GridSearchCV
from sklearn.tree import plot_tree

# Step 1: Load the dataset
iris = load_iris()
X = iris.data
y = iris.target

# Step 2: Data Preprocessing
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# Step 3: Visualization
plt.scatter(X_train_scaled[:, 0], X_train_scaled[:, 1], c=y_train, cmap='viridis')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.title('Scatter plot of Features 1 and 2')
plt.colorbar(label='Target')
plt.show()

# Step 4: Classification
clf = RandomForestClassifier(random_state=42)
clf.fit(X_train_scaled, y_train)

# Step 5: Model Evaluation
y_pred = clf.predict(X_test_scaled)
print("Confusion Matrix:")
print(confusion_matrix(y_test, y_pred))
print("\nClassification Report:")
print(classification_report(y_test, y_pred))

# Step 6: Optional - Parameter Tuning
param_grid = {'n_estimators': [50, 100, 150], 'max_depth': [None, 10, 20]}
grid_search = GridSearchCV(clf, param_grid, cv=5)
grid_search.fit(X_train_scaled, y_train)
best_clf = grid_search.best_estimator_
print("\nBest Parameters:", grid_search.best_params_)
print("Best Score:", grid_search.best_score_)

# Step 7: Optional - Feature Importance
feature_importances = best_clf.feature_importances_
print("\nFeature Importances:")
for i, importance in enumerate(feature_importances):
    print(f"Feature {i+1}: {importance:.4f}")

# Step 8: Optional - Visualization of Decision Trees
plt.figure(figsize=(20,10))
plot_tree(best_clf.estimators_[0], feature_names=iris.feature_names, class_names=iris.target_names, filled=True)
plt.show()

# Step 10: Conclusion
print("\nConclusion:")
print("Random Forest Classifier trained on the Iris dataset achieved good performance.")
print("The model was able to classify the iris species with high accuracy.")
print("Further analysis can be done to explore feature importance and visualize decision trees.")

# Step 11: Bonus - Interactive Visualization (Optional)
# Not implemented

# Step 12: Bonus - Presentation (Optional)
# Not implemented

# Step 13: Bonus - Peer Review (Optional)
# Not implemented

# Step 14: Bonus - Reflection (Optional)
# Not implemented

# Step 15: Bonus - Further Exploration (Optional)
# Not implemented

# Step 16: Bonus - Sharing (Optional)
# Not implemented

# Step 17: Bonus - Continuous Learning (Optional)
# Not implemented

# Step 18: Bonus - Collaboration (Optional)
# Not implemented

# Step 19: Bonus - Feedback (Optional)
# Not implemented

# Step 20: End of Lab
print("\nEnd of Lab")

#--------------------------------------------------------------------------------------------------------

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import confusion_matrix, classification_report
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import GridSearchCV

# Load the Breast Cancer Wisconsin dataset
data = load_breast_cancer()
X = pd.DataFrame(data.data, columns=data.feature_names)
y = pd.Series(data.target)

# Step 1: Mining of frequent patterns, associations, and correlations
# Not implemented

# Step 2: Characterization
print("Characterization:")
print(X.describe())

# Step 3: Data discrimination
# Not implemented

# Step 4: Classification
# Splitting the data into train and test sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Standardizing the features
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# Training a Random Forest Classifier
rf_classifier = RandomForestClassifier(random_state=42)
rf_classifier.fit(X_train_scaled, y_train)

# Step 5: Regression
# Not implemented

# Step 6: Clustering
# Not implemented

# Step 7: Outlier analysis
# Not implemented

# Step 8: Description Methods
# Types of attributes
print("\nTypes of attributes:")
print(X.dtypes)

# Important characteristics of data
print("\nImportant characteristics of data:")
print("Dimensionality:", X.shape)
print("Sparsity:", np.count_nonzero(X) / np.prod(X.shape))
print("Resolution: Not applicable")
print("Size:", X.size)

# Types of datasets
# Not implemented

# Step 9: Data Quality
# Common data quality problems
# Not implemented

# Exploratory data analysis (EDA)
# Not implemented

# Anomaly detection
# Not implemented

# Summary statistics
print("\nSummary statistics:")
print("Mean:\n", X.mean())
print("\nMedian:\n", X.median())
print("\nRange:\n", X.max() - X.min())
print("\nVariance:\n", X.var())
print("\nStandard Deviation:\n", X.std())

# Step 10: Data Visualization
# Histograms
X.hist(figsize=(12, 10))
plt.show()

# Scatter plots
sns.pairplot(X)
plt.show()

# Contour plots
# Not implemented

# Matrix plots
plt.figure(figsize=(10, 8))
sns.heatmap(X.corr(), annot=True, cmap='coolwarm')
plt.show()

# Step 11: Data Preprocessing
# Aggregation
# Not implemented

# Sampling techniques
# Not implemented

# Discretization and binarization
# Not implemented

# Attribute transformation
# Not implemented

# Dimensionality reduction
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X)

# Feature subset selection
# Not implemented

# Feature creation
# Not implemented

# Step 12: Classification Algorithms
# Base classifiers
# Not implemented

# Decision tree-based methods
dt_classifier = DecisionTreeClassifier(random_state=42)
dt_classifier.fit(X_train_scaled, y_train)

# Rule-based methods
# Not implemented

# Nearest-neighbor
# Not implemented

# Naïve Bayes and Bayesian belief networks
# Not implemented

# Support vector machines
# Not implemented

# Neural networks and deep neural networks
# Not implemented

# Ensemble classifiers
# Not implemented

# Step 13: Decision Tree Induction
# Algorithms: Hunt’s, CART, ID3, C4.5, SLIQ, SPRINT
# Not implemented

# Test conditions for nominal and continuous attributes
# Not implemented

# Determining the best split
# Not implemented

# Pruning techniques
# Not implemented

# Step 14: Model Evaluation
# Confusion matrix
y_pred_rf = rf_classifier.predict(X_test_scaled)
conf_mat_rf = confusion_matrix(y_test, y_pred_rf)
print("\nConfusion Matrix (Random Forest):")
print(conf_mat_rf)

# Evaluation metrics
print("\nClassification Report (Random Forest):")
print(classification_report(y_test, y_pred_rf))

# Trade-off between precision and recall
# Not implemented

# Bias and variance
# Not implemented

# Ensemble methods (Bagging, Random forests, Boosting)
# Not implemented

# Step 15: Support Vector Machines (SVM)
# Not implemented

# Linear SVM
# Not implemented

# Learning linear SVM
# Not implemented

# Non-linearly separable data
# Not implemented

# Soft margin
# Not implemented

# Nonlinear SVM
# Not implemented

# Step 16: Gradient Boosting
# Not implemented

# Gradient boosting technique
# Not implemented

# Minimizing weighted error
# Not implemented

# Step 17: AdaBoost (Adaptive boosting)
# Not implemented


#--------------------------------------------------------------------------------------------------------

pip install ucimlrepo

from ucimlrepo import fetch_ucirepo 
  
# fetch dataset 
heart_disease = fetch_ucirepo(id=45) 
  
# data (as pandas dataframes) 
X = heart_disease.data.features 
y = heart_disease.data.targets 
  
# metadata 
print(heart_disease.metadata) 
  
# variable information 
print(heart_disease.variables) 
