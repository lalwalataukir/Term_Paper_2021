#include <bits/stdc++.h>
#include <fstream>
using namespace std;

int N = 140; // Number of data points in training set
int M = 9;   // Number of regression coefficients 9 here a_0, a_1,... a_8


/**********************************************************************************************************/


void transpose(vector<vector<long double>> &X, vector<vector<long double>> &X_transpose) // function for finding the transpose
{
    for (int i = 0 ; i < N ; i++)
    {
        for (int j = 0 ; j < M ; j++)
        {
            X_transpose[j][i] = X[i][j];
        }
    }

}

void multiply_X_transpose_and_X(vector<vector<long double>> &X_transpose, vector<vector<long double>> &X , vector<vector<long double>> &X_transpose_multiplied_with_X)
{

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            long double temp = 0;

            for (int k = 0; k < N; k++)
            {
                temp += X_transpose[i][k] * X[k][j];
            }

            X_transpose_multiplied_with_X[i][j] = temp;
        }
    }
}

void inverse(vector<vector<long double>> X_transpose_multiplied_with_X, vector<vector<long double>> &inverse_of_X_transpose_multiplied_with_X)
{
    // calculates inverse using gauss jordan method
    int n = X_transpose_multiplied_with_X.size();

    // Augmented matrix
    vector<vector<long double>> Aug(n, vector<long double>(2 * n));
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n ; j++)
        {
            Aug[i][j] = X_transpose_multiplied_with_X[i][j];
        }
        for (int j = n ; j < 2 * n ; j++)
        {
            if (j - n == k)
            {
                Aug[i][j] = 1;

            }
            else
            {
                Aug[i][j] = 0;
            }
        }
        k++;
    }


    for (int j = 0 ; j < n ; j++)
    {
        // find largest element below the pivot and replace both rows

        int l = j;
        long double ele = Aug[j][j];

        for (int i = j + 1 ; i < n ; i++)
        {
            if (Aug[i][j] > ele)
            {
                l = i;
                ele = Aug[i][j];
            }
        }

        swap(Aug[j], Aug[l]); // swap


        // make elements below and abobe the pivot element zero
        long double temp = Aug[j][j];
        for (int i = 0 ; i < 2 * n ; i++)
        {
            Aug[j][i] = Aug[j][i] / temp;
        }

        for (int row = 0; row < n; row++)
        {
            if (row != j)
            {
                long double temp = Aug[row][j];
                for (int col = 0; col < 2 * n; col++)
                {
                    Aug[row][col] = Aug[row][col] - (((temp * (Aug[j][col]))));

                }
            }
        }
    }


    for (int i = 0 ; i < n ; i++)
    {
        for (int j = n; j < 2 * n ; j++)
        {
            inverse_of_X_transpose_multiplied_with_X[i][j - n] = Aug[i][j];
        }
    }
}

void multiply_Z_and_Y(vector<vector<long double>> Z, vector<long double> Y , vector<long double> &phi)
{

    for (int i = 0; i < M; i++)
    {
        long double temp = 0;

        for (int k = 0; k < N; k++)
        {
            temp += Z[i][k] * Y[k];
        }

        phi[i] = temp;

    }
}

void multiply_inverse_of_X_transpose_multiplied_with_X_and_X_transpose(vector<vector<long double>> inverse_of_X_transpose_multiplied_with_X, vector<vector<long double>> X_transpose , vector<vector<long double>> &Z)
{

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            Z[i][j] = 0;

            for (int k = 0; k < M; k++)
            {
                Z[i][j] += inverse_of_X_transpose_multiplied_with_X[i][k] * X_transpose[k][j];
            }


        }
    }
}


void multiply_Z_and_Y(vector<long double> &phi)
{
    ifstream fin("phi_output.txt");
    for (int i = 0; i < M; i++)
    {
        fin >> phi[i];
    }
    fin.close();
}


/***********************************************************************************************************/


int main()
{
    // Data
    // 140 data points
    vector<long double> concavity_mean = {0.3001, 0.0869, 0.1974, 0.2414, 0.198, 0.1578, 0.1127, 0.09366, 0.1859, 0.2273, 0.03299, 0.09954, 0.2065, 0.09938, 0.2128, 0.1639, 0.07395, 0.1722, 0.1479, 0.06664, 0.04568, 0.02956, 0.2077, 0.1097, 0.1525, 0.2229, 0.1425, 0.149, 0.1683, 0.09875, 0.2319, 0.1218, 0.2417, 0.1657, 0.1354, 0.1348, 0.1319, 0.02562, 0.02398, 0.1063, 0.0311, 0.1044, 0.2107, 0.09847, 0.08259, 0.1974, 0.01588, 0.1226, 0.06592, 0.04751, 0.01657, 0.01857, 0.01972, 0.1772, 0.05253, 0.03036, 0.1323, 0.1293, 0.000692, 0.02061, 0.01084, 0.03, 0.2135, 0.05988, 0.1128, 0.1267, 0.02172, 0.03709, 0.313, 0.03653, 0.108, 0.08606, 0.1692, 0.07789, 0.03372, 0.09769, 0.06877, 0.1684, 0.3754, 0.03889, 0.04591, 0.1169, 0.3339, 0.1937, 0.04151, 0.1335, 0.1204, 0.1468, 0.06015, 0.09966, 0.03102, 0.1122, 0.03261, 0.03974, 0.17, 0.1465, 0.0249, 0.006829, 0.04196, 0.09388, 0.08625, 0, 0.02383, 0.06154, 0.02995, 0.2071, 0.0707, 0.02643, 0.4264, 0.05133, 0.04334, 0.1065, 0.3003, 0.06476, 0.04132, 0.03328, 0.09263, 0.169, 0.2133, 0.07293, 0.03512, 0.1457, 0.4268, 0.08842, 0.08092, 0.0142, 0.05285, 0.09271, 0.1138, 0.2545, 0.02855, 0.1466, 0.1043, 0.07135, 0.1153, 0.04711, 0.03592, 0.03503, 0.1539, 0.04635};
    vector<long double> radius_mean = {17.99, 20.57, 19.69, 11.42, 20.29, 12.45, 18.25, 13.71, 13, 12.46, 16.02, 15.78, 19.17, 15.85, 13.73, 14.54, 14.68, 16.13, 19.81, 13.54, 13.08, 9.504, 15.34, 21.16, 16.65, 17.14, 14.58, 18.61, 15.3, 17.57, 18.63, 11.84, 17.02, 19.27, 16.13, 16.74, 14.25, 13.03, 14.99, 13.48, 13.44, 10.95, 19.07, 13.28, 13.17, 18.65, 8.196, 13.17, 12.05, 13.49, 11.76, 13.64, 11.94, 18.22, 15.1, 11.52, 19.21, 14.71, 13.05, 8.618, 10.17, 8.598, 14.25, 9.173, 12.68, 14.78, 9.465, 11.31, 9.029, 12.78, 18.94, 8.888, 17.2, 13.8, 12.31, 16.07, 13.53, 18.05, 20.18, 12.86, 11.45, 13.34, 25.22, 19.1, 12, 18.46, 14.48, 19.02, 12.36, 14.64, 14.62, 15.37, 13.27, 13.45, 15.06, 20.26, 12.18, 9.787, 11.6, 14.42, 13.61, 6.981, 12.18, 9.876, 10.49, 13.11, 11.64, 12.36, 22.27, 11.34, 9.777, 12.63, 14.26, 10.51, 8.726, 11.93, 8.95, 14.87, 15.78, 17.95, 11.41, 18.66, 24.25, 14.5, 13.37, 13.85, 13.61, 19, 15.1, 19.79, 12.19, 15.46, 16.16, 15.71, 18.45, 12.77, 11.71, 11.43, 14.95, 11.28};
    vector<long double> texture_mean = {10.38, 17.77, 21.25, 20.38, 14.34, 15.7, 19.98, 20.83, 21.82, 24.04, 23.24, 17.89, 24.8, 23.95, 22.61, 27.54, 20.13, 20.68, 22.15, 14.36, 15.71, 12.44, 14.26, 23.04, 21.38, 16.4, 21.53, 20.25, 25.27, 15.05, 25.11, 18.7, 23.98, 26.47, 17.88, 21.59, 21.72, 18.42, 25.2, 20.82, 21.58, 21.35, 24.81, 20.28, 21.81, 17.6, 16.84, 18.66, 14.63, 22.3, 21.6, 16.34, 18.24, 18.7, 22.02, 18.75, 18.57, 21.59, 19.31, 11.79, 14.88, 20.98, 22.15, 13.86, 23.84, 23.94, 21.01, 19.04, 17.33, 16.49, 21.31, 14.64, 24.52, 15.79, 16.52, 19.65, 10.94, 16.15, 23.97, 18, 20.97, 15.86, 24.91, 26.29, 15.65, 18.52, 21.46, 24.59, 21.8, 15.24, 24.02, 22.76, 14.76, 18.3, 19.83, 23.03, 17.84, 19.94, 12.84, 19.77, 24.98, 13.43, 20.52, 19.4, 19.29, 15.56, 18.33, 18.54, 19.67, 21.26, 16.99, 20.76, 19.65, 20.19, 15.83, 21.53, 15.76, 16.67, 22.91, 20.01, 10.82, 17.12, 20.2, 10.89, 16.39, 17.21, 24.69, 18.91, 16.39, 25.12, 13.29, 19.48, 21.54, 13.93, 21.91, 22.47, 16.67, 15.39, 17.57, 13.39};
    vector<long double> perimeter_mean = {122.8, 132.9, 130, 77.58, 135.1, 82.57, 119.6, 90.2, 87.5, 83.97, 102.7, 103.6, 132.4, 103.7, 93.6, 96.73, 94.74, 108.1, 130, 87.46, 85.63, 60.34, 102.5, 137.2, 110, 116, 97.41, 122.1, 102.4, 115, 124.8, 77.93, 112.8, 127.9, 107, 110.1, 93.63, 82.61, 95.54, 88.4, 86.18, 71.9, 128.3, 87.32, 85.42, 123.7, 51.71, 85.98, 78.04, 86.91, 74.72, 87.21, 75.71, 120.3, 97.26, 73.34, 125.5, 95.55, 82.61, 54.34, 64.55, 54.66, 96.42, 59.2, 82.69, 97.4, 60.11, 71.8, 58.79, 81.37, 123.6, 58.79, 114.2, 90.43, 79.19, 104.1, 87.91, 120.2, 143.7, 83.19, 73.81, 86.49, 171.5, 129.1, 76.95, 121.1, 94.25, 122, 79.78, 95.77, 94.57, 100.2, 84.74, 86.6, 100.3, 132.4, 77.79, 62.11, 74.34, 94.48, 88.05, 43.79, 77.22, 63.95, 67.41, 87.21, 75.17, 79.01, 152.8, 72.48, 62.5, 82.15, 97.83, 68.64, 55.84, 76.53, 58.74, 98.64, 105.7, 114.2, 73.34, 121.4, 166.2, 94.28, 86.1, 88.44, 87.76, 123.4, 99.58, 130.4, 79.08, 101.7, 106.2, 102, 120.2, 81.72, 74.72, 73.06, 96.85, 73};
    vector<long double> area_mean = {1001, 1326, 1203, 386.1, 1297, 477.1, 1040, 577.9, 519.8, 475.9, 797.8, 781, 1123, 782.7, 578.3, 658.8, 684.5, 798.8, 1260, 566.3, 520, 273.9, 704.4, 1404, 904.6, 912.7, 644.8, 1094, 732.4, 955.1, 1088, 440.6, 899.3, 1162, 807.2, 869.5, 633, 523.8, 698.8, 559.2, 563, 371.1, 1104, 545.2, 531.5, 1076, 201.9, 534.6, 449.3, 561, 427.9, 571.8, 437.6, 1033, 712.8, 409, 1152, 656.9, 527.2, 224.5, 311.9, 221.8, 645.7, 260.9, 499, 668.3, 269.4, 394.1, 250.5, 502.5, 1130, 244, 929.4, 584.1, 470.9, 817.7, 559.2, 1006, 1245, 506.3, 401.5, 520, 1878, 1132, 443.3, 1075, 648.2, 1076, 466.1, 651.9, 662.7, 728.2, 551.7, 555.1, 705.6, 1264, 451.1, 294.5, 412.6, 642.5, 582.7, 143.5, 458.7, 298.3, 336.1, 530.2, 412.5, 466.7, 1509, 396.5, 290.2, 480.4, 629.9, 334.2, 230.9, 438.6, 245.2, 682.5, 782.6, 982, 403.3, 1077, 1761, 640.7, 553.5, 588.7, 572.6, 1138, 674.5, 1192, 455.8, 748.9, 809.8, 761.7, 1075, 506.3, 423.6, 399.8, 678.1, 384.8};
    vector<long double> smoothness_mean = {0.1184, 0.08474, 0.1096, 0.1425, 0.1003, 0.1278, 0.09463, 0.1189, 0.1273, 0.1186, 0.08206, 0.0971, 0.0974, 0.08401, 0.1131, 0.1139, 0.09867, 0.117, 0.09831, 0.09779, 0.1075, 0.1024, 0.1073, 0.09428, 0.1121, 0.1186, 0.1054, 0.0944, 0.1082, 0.09847, 0.1064, 0.1109, 0.1197, 0.09401, 0.104, 0.0961, 0.09823, 0.08983, 0.09387, 0.1016, 0.08162, 0.1227, 0.09081, 0.1041, 0.09714, 0.1099, 0.086, 0.1158, 0.1031, 0.08752, 0.08637, 0.07685, 0.08261, 0.1148, 0.09056, 0.09524, 0.1053, 0.1137, 0.0806, 0.09752, 0.1134, 0.1243, 0.1049, 0.07721, 0.1122, 0.1172, 0.1044, 0.08139, 0.1066, 0.09831, 0.09009, 0.09783, 0.1071, 0.1007, 0.09172, 0.09168, 0.1291, 0.1065, 0.1286, 0.09934, 0.1102, 0.1078, 0.1063, 0.1215, 0.09723, 0.09874, 0.09444, 0.09029, 0.08772, 0.1132, 0.08974, 0.092, 0.07355, 0.1022, 0.1039, 0.09078, 0.1045, 0.1024, 0.08983, 0.09752, 0.09488, 0.117, 0.08013, 0.1005, 0.09989, 0.1398, 0.1142, 0.08477, 0.1326, 0.08759, 0.1037, 0.09933, 0.07837, 0.1122, 0.115, 0.09768, 0.09462, 0.1162, 0.1155, 0.08402, 0.09373, 0.1054, 0.1447, 0.1101, 0.07115, 0.08785, 0.09258, 0.08217, 0.115, 0.1015, 0.1066, 0.1092, 0.1008, 0.09462, 0.0943, 0.09055, 0.1051, 0.09639, 0.1167, 0.1164};
    vector<long double> compactness_mean = {0.2776, 0.07864, 0.1599, 0.2839, 0.1328, 0.17, 0.109, 0.1645, 0.1932, 0.2396, 0.06669, 0.1292, 0.2458, 0.1002, 0.2293, 0.1595, 0.072, 0.2022, 0.1027, 0.08129, 0.127, 0.06492, 0.2135, 0.1022, 0.1457, 0.2276, 0.1868, 0.1066, 0.1697, 0.1157, 0.1887, 0.1516, 0.1496, 0.1719, 0.1559, 0.1336, 0.1098, 0.03766, 0.05131, 0.1255, 0.06031, 0.1218, 0.219, 0.1436, 0.1047, 0.1686, 0.05943, 0.1231, 0.09092, 0.07698, 0.04966, 0.06059, 0.04751, 0.1485, 0.07081, 0.05473, 0.1267, 0.1365, 0.03789, 0.05272, 0.08061, 0.08963, 0.2008, 0.08751, 0.1262, 0.1479, 0.07773, 0.04701, 0.1413, 0.05234, 0.1029, 0.1531, 0.183, 0.128, 0.06829, 0.08424, 0.1047, 0.2146, 0.3454, 0.09546, 0.09362, 0.1535, 0.2665, 0.1791, 0.07165, 0.1053, 0.09947, 0.1206, 0.09445, 0.1339, 0.08606, 0.1036, 0.05055, 0.08165, 0.1553, 0.1313, 0.07057, 0.05301, 0.07525, 0.1141, 0.08511, 0.07568, 0.04038, 0.09697, 0.08578, 0.1765, 0.1017, 0.06815, 0.2768, 0.06575, 0.08404, 0.1209, 0.2233, 0.1303, 0.08201, 0.07849, 0.1243, 0.1649, 0.1752, 0.06722, 0.06685, 0.11, 0.2867, 0.1099, 0.07325, 0.06136, 0.07862, 0.08028, 0.1807, 0.1589, 0.09509, 0.1223, 0.1284, 0.09462, 0.09709, 0.05761, 0.06095, 0.06889, 0.1305, 0.1136};
    vector<long double> concave_points_mean = {0.1471, 0.07017, 0.1279, 0.1052, 0.1043, 0.08089, 0.074, 0.05985, 0.09353, 0.08543, 0.03323, 0.06606, 0.1118, 0.05364, 0.08025, 0.07364, 0.05259, 0.1028, 0.09498, 0.04781, 0.0311, 0.02076, 0.09756, 0.08632, 0.0917, 0.1401, 0.08783, 0.07731, 0.08751, 0.07953, 0.1244, 0.05182, 0.1203, 0.07593, 0.07752, 0.06018, 0.05598, 0.02923, 0.02899, 0.05439, 0.02031, 0.05669, 0.09961, 0.06158, 0.05252, 0.1009, 0.005917, 0.0734, 0.02749, 0.03384, 0.01115, 0.01723, 0.01349, 0.106, 0.03334, 0.02278, 0.08994, 0.08123, 0.004167, 0.007799, 0.0129, 0.009259, 0.08653, 0.0218, 0.06873, 0.09029, 0.01504, 0.0223, 0.04375, 0.02864, 0.07951, 0.02872, 0.07944, 0.05069, 0.02272, 0.06638, 0.06556, 0.108, 0.1604, 0.02315, 0.02233, 0.06987, 0.1845, 0.1469, 0.01863, 0.08795, 0.04938, 0.08271, 0.03745, 0.07064, 0.02957, 0.07483, 0.02648, 0.0278, 0.08815, 0.08683, 0.02941, 0.007937, 0.0335, 0.05839, 0.04489, 0, 0.0177, 0.03029, 0.01201, 0.09601, 0.03485, 0.01921, 0.1823, 0.01899, 0.01778, 0.06021, 0.07798, 0.03068, 0.01924, 0.02008, 0.02308, 0.08923, 0.09479, 0.05596, 0.02623, 0.08665, 0.2012, 0.05778, 0.028, 0.01141, 0.03085, 0.05627, 0.08534, 0.1149, 0.02882, 0.08087, 0.05613, 0.05933, 0.06847, 0.02704, 0.026, 0.02875, 0.08624, 0.04796};
    vector<long double> fractal_dimension_mean = {0.07871, 0.05667, 0.05999, 0.09744, 0.05883, 0.07613, 0.05742, 0.07451, 0.07389, 0.08243, 0.05697, 0.06082, 0.078, 0.05338, 0.07682, 0.07077, 0.05922, 0.07356, 0.05395, 0.05766, 0.06811, 0.06905, 0.07032, 0.05278, 0.0633, 0.07413, 0.06924, 0.05699, 0.0654, 0.06149, 0.06197, 0.07799, 0.06382, 0.06261, 0.06515, 0.05656, 0.06125, 0.05863, 0.05504, 0.06419, 0.05587, 0.0687, 0.06343, 0.06782, 0.06177, 0.06049, 0.06503, 0.06777, 0.06043, 0.05718, 0.05888, 0.05953, 0.0611, 0.0631, 0.05684, 0.05907, 0.05961, 0.06758, 0.05501, 0.07187, 0.0696, 0.06757, 0.07292, 0.06963, 0.0659, 0.06654, 0.06899, 0.05667, 0.08046, 0.05653, 0.05461, 0.0898, 0.06487, 0.06566, 0.05914, 0.05391, 0.06641, 0.06673, 0.08142, 0.05997, 0.07005, 0.06902, 0.06782, 0.07224, 0.05968, 0.06022, 0.05636, 0.05629, 0.06404, 0.06346, 0.05866, 0.06097, 0.05318, 0.0571, 0.06284, 0.05649, 0.06635, 0.0689, 0.06582, 0.0639, 0.05871, 0.07818, 0.05677, 0.06322, 0.06481, 0.07692, 0.0652, 0.06066, 0.07039, 0.06529, 0.07065, 0.0707, 0.07769, 0.07782, 0.07633, 0.06194, 0.07163, 0.06768, 0.07331, 0.05025, 0.06113, 0.06213, 0.06877, 0.06402, 0.05823, 0.0589, 0.0613, 0.05044, 0.06467, 0.06113, 0.06471, 0.05796, 0.05891, 0.05723, 0.05727, 0.06065, 0.05945, 0.05865, 0.06216, 0.06072};


    // Feature Scaling using Min-Max normalization

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


    // Model Fitting
    // [X][a] = [Y] --> [a] = ([X]^(-1))*[Y] --> [a] = ((([X]^(T))*[X])^(-1))*([X]^(T))*[Y]

    // let [Z] = [inverse_of_X_transpose_multiplied_with_X]*[X_transpose]

    // let [phi] = [Z]*[Y]
    vector<vector<long double>> X(N, vector<long double>(M));
    vector<long double> Y = concavity_mean;
    vector<vector<long double>> X_transpose(M, vector<long double>(N));
    vector<vector<long double>> X_transpose_multiplied_with_X(M, vector<long double>(M));
    vector<vector<long double>> inverse_of_X_transpose_multiplied_with_X(M, vector<long double>(M));
    vector<vector<long double>> Z(M, vector<long double>(N));
    vector<long double> phi(M);


    // generating X

    for (int i = 0; i < N; i++)
    {
        X[i][0] = 1;
        X[i][1] = radius_mean[i] * radius_mean[i];
        X[i][2] = texture_mean[i] * texture_mean[i];
        X[i][3] = perimeter_mean[i] * perimeter_mean[i];
        X[i][4] = area_mean[i];
        X[i][5] = smoothness_mean[i] * smoothness_mean[i];
        X[i][6] = compactness_mean[i];
        X[i][7] = concave_points_mean[i];
        X[i][8] = fractal_dimension_mean[i] * fractal_dimension_mean[i];
    }

    // generating X_transpose
    transpose(X, X_transpose);


    // generating X_transpose_multiplied_with_X
    multiply_X_transpose_and_X(X_transpose, X, X_transpose_multiplied_with_X);

    // generating inverse_of_X_transpose_multiplied_with_X
    inverse(X_transpose_multiplied_with_X, inverse_of_X_transpose_multiplied_with_X);

    // generating [Z]
    multiply_inverse_of_X_transpose_multiplied_with_X_and_X_transpose(inverse_of_X_transpose_multiplied_with_X, X_transpose, Z);

    // generating [phi]
    multiply_Z_and_Y(Z, Y, phi);

    // output regression coefficients
    cout << "Regression coefficients\n";
    for (int i = 0; i < M; i++)
    {
        cout << "a_" << i << " = " << fixed << phi[i] << "\n";
    }


}