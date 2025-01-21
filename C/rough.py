Load Training and Testing file
Assign column names to training and testing data
for each entry in df[′outcome′] 
do
if entry == ”normal” then
entry ← 0
else
entry ← 1
end if
end for
Preprocess (dataframe, train columns)
if train columns ̸= NULL then
Identify missingcols ← train columns −
dataframe.columns
for each col in missingcols do
dataframe[col] ← 0
end for
Reorder dataframe to match train columns
end if
return dataframe
scaledtrain ← preprocess(df train)
scaledtest ← preprocess(df test, train columns)
x train, y train ← features, labels from scaledtrain
x test, y test ← features, labels from scaledtest
Initialize pca ← P CA(20)
x train reduced ← pca.f it transform(x train)
x test reduced ← pca.transform(x test)
(xtrain, xtest, ytrain, ytest) ←
train test split(x train reduced, y train, test size)
train and save models(models, xtrain, ytrain)
for each model in models do
Train model on (xtrain, ytrain)
end for
evaluate models(models, xtrain, ytrain, xtest, ytest)
Call train and save models
Call evaluate models
Display accuracy, precision, and recall for each model on Training and test data
END =0
