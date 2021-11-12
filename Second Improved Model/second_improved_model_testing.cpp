#include <bits/stdc++.h>
using namespace std;

int N = 60;  // Number of data points in training set
int M = 9;   // Number of regression coefficients 9 here a_0, a_1,... a_8

int main()
{
    // Testing Set
    // 60 data points
    vector<long double> concavity_mean = {0.01288, 0.01063, 0.01236, 0.02685, 0.02475, 0.02495, 0.2197, 0.0683, 0.2283, 0.02297, 0.03344, 0.01974, 0.001461, 0.003681, 0.002758, 0.004559, 0.01583, 0.01447, 0.04052, 0.01367, 0, 0.004473, 0.01123, 0.113, 0.1975, 0.01342, 0.06726, 0.1155, 0.038, 0.2565, 0.01994, 0.03193, 0.01765, 0.001546, 0.1478, 0.1799, 0.1204, 0.07107, 0.005006, 0.0009737, 0.007756, 0.1508, 0.03738, 0.106, 0.02511, 0.2308, 0.08007, 0.08422, 0.05397, 0.1863, 0.04006, 0.03581, 0.00751, 0.04608, 0.02587, 0.01171, 0.008306, 0.2914, 0.3368, 0.1235};
    vector<long double> radius_mean = {12.72, 13.77, 10.91, 11.76, 14.26, 10.51, 19.53, 12.46, 20.09, 10.49, 11.46, 11.6, 13.2, 9, 13.5, 13.05, 11.7, 14.61, 12.76, 11.54, 8.597, 12.49, 12.18, 18.22, 9.042, 12.43, 10.25, 20.16, 12.86, 20.34, 12.2, 12.67, 14.11, 12.03, 16.27, 16.26, 16.03, 12.98, 11.22, 11.25, 12.3, 17.06, 12.99, 18.77, 10.05, 23.51, 14.42, 9.606, 11.06, 19.68, 11.71, 10.26, 12.06, 14.76, 11.47, 11.95, 11.66, 15.75, 25.73, 15.08};
    vector<long double> texture_mean = {13.78, 13.27, 12.35, 18.14, 18.17, 23.09, 18.9, 19.89, 23.86, 18.61, 18.16, 24.49, 15.82, 14.4, 12.71, 13.84, 19.11, 15.69, 13.37, 10.72, 18.6, 16.85, 14.08, 18.87, 18.9, 17, 16.18, 19.66, 13.32, 21.51, 15.21, 17.3, 12.88, 17.93, 20.71, 21.88, 15.51, 19.35, 19.86, 14.78, 19.02, 21, 14.23, 21.43, 17.53, 24.27, 16.54, 16.84, 14.96, 21.68, 15.45, 14.71, 18.9, 14.74, 16.03, 14.96, 17.07, 19.22, 17.46, 25.74};
    vector<long double> perimeter_mean = {81.78, 88.06, 69.14, 75, 91.22, 66.85, 129.5, 80.43, 134.7, 66.86, 73.59, 74.23, 84.07, 56.36, 85.69, 82.71, 74.33, 92.68, 82.29, 73.73, 54.09, 79.19, 77.25, 118.7, 60.07, 78.6, 66.52, 131.1, 82.82, 135.9, 78.01, 81.25, 90.03, 76.09, 106.9, 107.5, 105.8, 84.52, 71.94, 71.38, 77.88, 111.8, 84.08, 122.9, 64.41, 155.1, 94.15, 61.64, 71.49, 129.9, 75.03, 66.2, 76.66, 94.87, 73.02, 77.23, 73.7, 107.1, 174.2, 98};
    vector<long double> area_mean = {492.1, 582.7, 363.7, 431.1, 633.1, 334.2, 1217, 471.3, 1247, 334.3, 403.1, 417.2, 537.3, 246.3, 566.2, 530.6, 418.7, 664.9, 504.1, 409.1, 221.2, 481.6, 461.4, 1027, 244.5, 477.3, 324.2, 1274, 504.8, 1264, 457.9, 489.9, 616.5, 446, 813.7, 826.8, 793.2, 514, 387.3, 390, 464.4, 918.6, 514.3, 1092, 310.8, 1747, 641.2, 280.5, 373.9, 1194, 420.3, 321.6, 445.3, 668.7, 402.7, 426.7, 421, 758.6, 2010, 716.6};
    vector<long double> smoothness_mean = {0.09667, 0.09198, 0.08518, 0.09968, 0.06576, 0.1015, 0.115, 0.08451, 0.108, 0.1068, 0.08853, 0.07474, 0.08511, 0.07005, 0.07376, 0.08352, 0.08814, 0.07618, 0.08794, 0.08597, 0.1074, 0.08511, 0.07734, 0.09746, 0.09968, 0.07557, 0.1061, 0.0802, 0.1134, 0.117, 0.08673, 0.1028, 0.09309, 0.07683, 0.1169, 0.1165, 0.09491, 0.09579, 0.1054, 0.08306, 0.08313, 0.1119, 0.09462, 0.09116, 0.1007, 0.1069, 0.09751, 0.08481, 0.1033, 0.09797, 0.115, 0.09882, 0.08386, 0.08875, 0.09076, 0.1158, 0.07561, 0.1243, 0.1149, 0.1024};
    vector<long double> compactness_mean = {0.08393, 0.06221, 0.04721, 0.05914, 0.0522, 0.06797, 0.1642, 0.1014, 0.1838, 0.06678, 0.07694, 0.05688, 0.05251, 0.03116, 0.03614, 0.03735, 0.05253, 0.03515, 0.07948, 0.05969, 0.05847, 0.03834, 0.03212, 0.1117, 0.1972, 0.03454, 0.1111, 0.08564, 0.08834, 0.1875, 0.06545, 0.07664, 0.05306, 0.03892, 0.1319, 0.1283, 0.1371, 0.1125, 0.06779, 0.04458, 0.04202, 0.1056, 0.09965, 0.1402, 0.07326, 0.1283, 0.1139, 0.09228, 0.09097, 0.1339, 0.07281, 0.09159, 0.05794, 0.0778, 0.05886, 0.1206, 0.0363, 0.2364, 0.2363, 0.09769};
    vector<long double> concave_points_mean = {0.01924, 0.01917, 0.01369, 0.03515, 0.01374, 0.01875, 0.1062, 0.03099, 0.128, 0.0178, 0.01502, 0.01313, 0.003261, 0.003472, 0.004419, 0.008829, 0.01148, 0.01877, 0.02548, 0.008907, 0, 0.006423, 0.005051, 0.0795, 0.04908, 0.01699, 0.03965, 0.07726, 0.034, 0.1504, 0.01692, 0.02107, 0.02733, 0.005592, 0.08488, 0.07981, 0.07041, 0.0295, 0.007583, 0.002941, 0.008535, 0.09934, 0.02098, 0.0609, 0.01775, 0.141, 0.04223, 0.02292, 0.03341, 0.1103, 0.0325, 0.02037, 0.008488, 0.03528, 0.02322, 0.01787, 0.01162, 0.1242, 0.1913, 0.06553};
    vector<long double> fractal_dimension_mean = {0.061, 0.05912, 0.06031, 0.06287, 0.05586, 0.06556, 0.06552, 0.06249, 0.07469, 0.066, 0.06243, 0.05878, 0.05894, 0.06833, 0.05335, 0.05518, 0.06128, 0.05255, 0.0614, 0.061, 0.07359, 0.05673, 0.05649, 0.05664, 0.08743, 0.05561, 0.07279, 0.05096, 0.06476, 0.0667, 0.06129, 0.05984, 0.057, 0.0607, 0.06277, 0.06532, 0.05976, 0.0654, 0.06028, 0.06081, 0.05945, 0.06071, 0.07238, 0.06083, 0.06331, 0.05506, 0.06412, 0.07125, 0.06907, 0.05715, 0.06506, 0.07005, 0.06048, 0.05912, 0.06372, 0.06581, 0.05731, 0.07603, 0.06121, 0.06464};


    // // Feature Scaling using Min-Max normalization

    // radius_mean
    long double mini = *min_element(radius_mean.begin(), radius_mean.end());
    long double maxi = *max_element(radius_mean.begin(), radius_mean.end());
    for (int i = 0; i < radius_mean.size(); i++)
    {
        radius_mean[i] = (radius_mean[i] - mini) / (maxi - mini);
    }

    // texture_mean
    mini = *min_element(texture_mean.begin(), texture_mean.end());
    maxi = *max_element(texture_mean.begin(), texture_mean.end());
    for (int i = 0; i < texture_mean.size(); i++)
    {
        texture_mean[i] = (texture_mean[i] - mini) / (maxi - mini);
    }

    // perimeter_mean
    mini = *min_element(perimeter_mean.begin(), perimeter_mean.end());
    maxi = *max_element(perimeter_mean.begin(), perimeter_mean.end());
    for (int i = 0; i < perimeter_mean.size(); i++)
    {
        perimeter_mean[i] = (perimeter_mean[i] - mini) / (maxi - mini);
    }

    // area_mean
    mini = *min_element(area_mean.begin(), area_mean.end());
    maxi = *max_element(area_mean.begin(), area_mean.end());
    for (int i = 0; i < area_mean.size(); i++)
    {
        area_mean[i] = (area_mean[i] - mini) / (maxi - mini);
    }

    // smoothness_mean
    mini = *min_element(smoothness_mean.begin(), smoothness_mean.end());
    maxi = *max_element(smoothness_mean.begin(), smoothness_mean.end());
    for (int i = 0; i < smoothness_mean.size(); i++)
    {
        smoothness_mean[i] = (smoothness_mean[i] - mini) / (maxi - mini);
    }

    // compactness_mean
    mini = *min_element(compactness_mean.begin(), compactness_mean.end());
    maxi = *max_element(compactness_mean.begin(), compactness_mean.end());
    for (int i = 0; i < compactness_mean.size(); i++)
    {
        compactness_mean[i] = (compactness_mean[i] - mini) / (maxi - mini);
    }

    // concave_points_mean
    mini = *min_element(concave_points_mean.begin(), concave_points_mean.end());
    maxi = *max_element(concave_points_mean.begin(), concave_points_mean.end());
    for (int i = 0; i < concave_points_mean.size(); i++)
    {
        concave_points_mean[i] = (concave_points_mean[i] - mini) / (maxi - mini);
    }

    // fractal_dimension_mean
    mini = *min_element(fractal_dimension_mean.begin(), fractal_dimension_mean.end());
    maxi = *max_element(fractal_dimension_mean.begin(), fractal_dimension_mean.end());
    for (int i = 0; i < fractal_dimension_mean.size(); i++)
    {
        fractal_dimension_mean[i] = (fractal_dimension_mean[i] - mini) / (maxi - mini);
    }

    // phi vector from training model
    vector<long double> coefficients = {0.008312, -0.088533, 0.010066, 0.278948, -0.181611, -0.041188, 0.131236, 0.292271, 0.041467};

    long double MAE = 0;
    long double MSE = 0;
    long double RMAE = 0;
    long double y_bar = 0;
    long double SSres = 0;
    vector<long double> values(N);


    for (int i = 0 ; i < N ; i++)
    {
        long double value = 0;
        value = value + coefficients[0] * 1;
        value = value + coefficients[1] * radius_mean[i] * radius_mean[i];
        value = value + coefficients[2] * texture_mean[i] * texture_mean[i];
        value = value + coefficients[3] * perimeter_mean[i] * perimeter_mean[i];
        value = value + coefficients[4] * area_mean[i];
        value = value + coefficients[5] * smoothness_mean[i] * smoothness_mean[i];
        value = value + coefficients[6] * compactness_mean[i];
        value = value + coefficients[7] * concave_points_mean[i];
        value = value + coefficients[8] * fractal_dimension_mean[i] * fractal_dimension_mean[i];

        y_bar = y_bar + value;
        MSE = MSE + (value - concavity_mean[i]) * (value - concavity_mean[i]);
        MAE = MAE + abs((value - concavity_mean[i])) ;

        SSres = SSres + (value - concavity_mean[i]) * (value - concavity_mean[i]);

    }

    y_bar = y_bar / 60;
    MAE = MAE / 60;
    MSE = MSE / 60;
    cout << "MAE = " << MAE << "\n";
    cout << "MSE = " << MSE << "\n";
    cout << "RMSE = " << sqrt(MSE) << "\n";


    long double SStol = 0;
    for (int i = 0 ; i < N ; i++)
    {
        long double value = 0;
        value = value + coefficients[0] * 1;
        value = value + coefficients[1] * radius_mean[i] * radius_mean[i];
        value = value + coefficients[2] * texture_mean[i] * texture_mean[i];
        value = value + coefficients[3] * perimeter_mean[i] * perimeter_mean[i];
        value = value + coefficients[4] * area_mean[i];
        value = value + coefficients[5] * smoothness_mean[i] * smoothness_mean[i];
        value = value + coefficients[6] * compactness_mean[i];
        value = value + coefficients[7] * concave_points_mean[i];
        value = value + coefficients[8] * fractal_dimension_mean[i] * fractal_dimension_mean[i];
        values[i] = value;

        SStol = SStol + (value - y_bar) * (value - y_bar);

    }

    cout << "SSres = " << SSres << " SStol = " << SStol << "\n";

    cout << "coefficient of Determination (R^2) = " << (1 - (SSres / SStol)) * 100  << " %" << "\n";

    // output predicted values in predicted_values.csv file
    ofstream fout ("predicted_values.csv");
    fout << "concavity_mean actual" << "," << "predicted_values\n";

    for (int i = 0 ; i < N ; i++)
    {
        fout << concavity_mean[i] << "," << values[i] << "\n";
    }
    fout.close();




}