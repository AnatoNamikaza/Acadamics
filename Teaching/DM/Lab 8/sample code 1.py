# Import necessary libraries
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC
from sklearn.ensemble import VotingClassifier
from sklearn.metrics import accuracy_score

# Load the dataset
data = pd.read_csv('imdb_reviews.csv')

# Preprocessing: Convert labels to numerical values (0 for negative, 1 for positive)
data['sentiment'] = data['sentiment'].map({'negative': 0, 'positive': 1})

# Split the dataset into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(data['review'], data['sentiment'], test_size=0.2, random_state=42)

# Preprocessing: Convert text data into numerical features using CountVectorizer
vectorizer = CountVectorizer(stop_words='english')
X_train_vectorized = vectorizer.fit_transform(X_train)
X_test_vectorized = vectorizer.transform(X_test)

# Build individual classifiers
nb_classifier = MultinomialNB()
lr_classifier = LogisticRegression(max_iter=1000)
svm_classifier = SVC(kernel='linear', probability=True)

# Create ensemble classifier using voting mechanism
ensemble_classifier = VotingClassifier(estimators=[('nb', nb_classifier), ('lr', lr_classifier), ('svm', svm_classifier)], voting='soft')

# Train the ensemble classifier
ensemble_classifier.fit(X_train_vectorized, y_train)

# Predict on the testing set
y_pred = ensemble_classifier.predict(X_test_vectorized)

# Calculate accuracy
accuracy = accuracy_score(y_test, y_pred)
print("Ensemble Accuracy:", accuracy)
