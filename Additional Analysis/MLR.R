#reading the file.
mydata <- read.csv(file = "MLR_data.csv")

#attaching the database to the R search path.
attach(mydata)

#define variables
Y <- cbind(concavity_mean)
X <- cbind(radius_mean, texture_mean, perimeter_mean, area_mean, smoothness_mean, compactness_mean, concave_points_mean, fractal_dimension_mean)

#descriptive statistics
summary(Y)
summary(X)

model1 <- lm(Y ~ X)
summary(model1)

plot(model1)
