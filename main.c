#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_DATA_POINTS 1000
#define MAX_VARIABLES 10
#define MAX_STRING 100

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    char variable_name[MAX_STRING];
    double data[MAX_DATA_POINTS];
    int count;
} Dataset;

typedef struct {
    double mean;
    double median;
    double mode;
    double std_deviation;
    double variance;
    double min;
    double max;
    double range;
    double q1, q2, q3;
    double iqr;
} Statistics;

Dataset datasets[MAX_VARIABLES];
int dataset_count = 0;

void display_main_menu();
void data_input_menu();
void statistical_analysis_menu();
void visualization_menu();
void machine_learning_menu();
void data_export_menu();

void manual_data_entry();
void load_from_file();
void generate_sample_data();
void display_datasets();

Statistics calculate_descriptive_stats(Dataset *dataset);
void correlation_analysis();
void regression_analysis();
void hypothesis_testing();
void confidence_intervals();

void sort_array(double arr[], int n);
double calculate_correlation(double x[], double y[], int n);
void print_statistics(Statistics stats, char *variable_name);
void clear_screen();
void wait_for_input();

double median_of_range(double arr[], int start, int end); // inclusive start, inclusive end

int main() {
    int choice;

    printf("=================================================\n");
    printf("    DATA ANALYSIS & STATISTICS SYSTEM v1.0\n");
    printf("    Professional Data Science Tool in C\n");
    printf("=================================================\n\n");

    do {
        display_main_menu();
        printf("Enter your choice: ");

        if(scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number.\n");
            while(getchar() != '\n'); // Clear input buffer
            wait_for_input();
            continue;
        }

        switch(choice) {
            case 1:
                data_input_menu();
                break;
            case 2:
                statistical_analysis_menu();
                break;
            case 3:
                visualization_menu();
                break;
            case 4:
                machine_learning_menu();
                break;
            case 5:
                data_export_menu();
                break;
            case 6:
                printf("\nThank you for using Data Analysis System!\n");
                printf("Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice! Please enter a number between 1-6.\n");
        }

        if(choice != 6) {
            wait_for_input();
        }

    } while(choice != 6);

    return 0;
}

void display_main_menu() {
    clear_screen();
    printf("\n=================== MAIN MENU ===================\n");
    printf("1. Data Input & Management\n");
    printf("2. Statistical Analysis\n");
    printf("3. Data Visualization\n");
    printf("4. Machine Learning Basics\n");
    printf("5. Export Results\n");
    printf("6. Exit\n");
    printf("================================================\n");
}

void data_input_menu() {
    int choice;

    do {
        clear_screen();
        printf("\n============= DATA INPUT & MANAGEMENT =============\n");
        printf("1. Manual Data Entry\n");
        printf("2. Load Data from File\n");
        printf("3. Generate Sample Data\n");
        printf("4. View Current Datasets\n");
        printf("5. Back to Main Menu\n");
        printf("=================================================\n");
        printf("Enter your choice: ");

        if(scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number.\n");
            while(getchar() != '\n');
            wait_for_input();
            continue;
        }

        switch(choice) {
            case 1:
                manual_data_entry();
                break;
            case 2:
                load_from_file();
                break;
            case 3:
                generate_sample_data();
                break;
            case 4:
                display_datasets();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice! Please enter 1-5.\n");
        }

        if(choice != 5) {
            wait_for_input();
        }

    } while(choice != 5);
}

void manual_data_entry() {
    if(dataset_count >= MAX_VARIABLES) {
        printf("\nMaximum number of datasets (%d) reached!\n", MAX_VARIABLES);
        return;
    }

    Dataset *current = &datasets[dataset_count];

    printf("\nEnter variable name (no spaces): ");
    if(scanf("%99s", current->variable_name) != 1) {
        printf("Error reading variable name!\n");
        while(getchar() != '\n');
        return;
    }

    printf("How many data points? (max %d): ", MAX_DATA_POINTS);
    if(scanf("%d", &current->count) != 1 || current->count <= 0) {
        printf("Invalid number of data points!\n");
        while(getchar() != '\n');
        return;
    }

    if(current->count > MAX_DATA_POINTS) {
        printf("Too many data points! Setting to maximum (%d).\n", MAX_DATA_POINTS);
        current->count = MAX_DATA_POINTS;
    }

    printf("Enter %d data points:\n", current->count);
    for(int i = 0; i < current->count; i++) {
        printf("Point %d: ", i + 1);
        if(scanf("%lf", &current->data[i]) != 1) {
            printf("Invalid input! Please enter a valid number.\n");
            i--; // Retry this input
            while(getchar() != '\n'); // Clear buffer
        }
    }

    dataset_count++;
    printf("\nDataset '%s' added successfully with %d data points!\n",
           current->variable_name, current->count);
}

void load_from_file() {
    if(dataset_count >= MAX_VARIABLES) {
        printf("\nMaximum number of datasets reached!\n");
        return;
    }

    char filename[100];
    printf("\nEnter filename (with extension): ");
    if(scanf("%99s", filename) != 1) {
        printf("Error reading filename!\n");
        while(getchar() != '\n');
        return;
    }

    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        printf("Error: Could not open file '%s'!\n", filename);
        printf("Make sure the file exists and you have permission to read it.\n");
        return;
    }

    Dataset *current = &datasets[dataset_count];
    strncpy(current->variable_name, filename, MAX_STRING-1);
    current->variable_name[MAX_STRING-1] = '\0';
    current->count = 0;

    double value;
    while(fscanf(file, "%lf", &value) == 1 && current->count < MAX_DATA_POINTS) {
        current->data[current->count] = value;
        current->count++;
    }

    fclose(file);

    if(current->count == 0) {
        printf("No valid data found in file!\n");
        return;
    }

    dataset_count++;
    printf("Successfully loaded %d data points from '%s'\n", current->count, filename);
}

void generate_sample_data() {
    if(dataset_count >= MAX_VARIABLES) {
        printf("\nMaximum number of datasets reached!\n");
        return;
    }

    Dataset *current = &datasets[dataset_count];
    srand((unsigned int)time(NULL));

    printf("\n========= SAMPLE DATA GENERATION =========\n");
    printf("1. Normal Distribution (Sales Data)\n");
    printf("2. Uniform Distribution (Random Numbers)\n");
    printf("3. Exponential Distribution (Wait Times)\n");
    printf("Enter choice: ");

    int type;
    if(scanf("%d", &type) != 1) {
        printf("Invalid input!\n");
        while(getchar() != '\n');
        return;
    }

    current->count = 100; // Generate 100 sample points

    switch(type) {
        case 1:
            strcpy(current->variable_name, "Sales_Data");
            // Generate normal-like distribution using Box-Muller transform
            for(int i = 0; i < current->count; i += 2) {
                double u1 = (double)rand() / RAND_MAX;
                double u2 = (double)rand() / RAND_MAX;

                if(u1 == 0.0) u1 = 1e-10;

                double z0 = sqrt(-2.0 * log(u1)) * cos(2 * M_PI * u2);
                double z1 = sqrt(-2.0 * log(u1)) * sin(2 * M_PI * u2);

                current->data[i] = z0 * 15 + 100; // mean=100, std=15
                if(i + 1 < current->count) {
                    current->data[i + 1] = z1 * 15 + 100;
                }
            }
            break;

        case 2:
            strcpy(current->variable_name, "Random_Numbers");
            for(int i = 0; i < current->count; i++) {
                current->data[i] = (double)rand() / RAND_MAX * 100;
            }
            break;

        case 3:
            strcpy(current->variable_name, "Wait_Times");
            for(int i = 0; i < current->count; i++) {
                double u = (double)rand() / RAND_MAX;
                if(u == 0.0) u = 1e-10; // Avoid log(0)
                current->data[i] = -log(u) * 5.0; // Exponential with lambda = 0.2
            }
            break;

        default:
            printf("Invalid choice! Please select 1-3.\n");
            return;
    }

    dataset_count++;
    printf("\nSample dataset '%s' generated successfully with %d points!\n",
           current->variable_name, current->count);
}

void display_datasets() {
    if(dataset_count == 0) {
        printf("\nNo datasets available. Please add some data first.\n");
        return;
    }

    printf("\n=============== CURRENT DATASETS ===============\n");
    for(int i = 0; i < dataset_count; i++) {
        printf("\nDataset %d: %s\n", i + 1, datasets[i].variable_name);
        printf("Data points: %d\n", datasets[i].count);
        printf("First 10 values: ");

        int limit = (datasets[i].count < 10) ? datasets[i].count : 10;
        for(int j = 0; j < limit; j++) {
            printf("%.2f ", datasets[i].data[j]);
        }
        if(datasets[i].count > 10) printf("...");
        printf("\n");
    }
    printf("===============================================\n");
}

void statistical_analysis_menu() {
    int choice;

    do {
        clear_screen();
        printf("\n============ STATISTICAL ANALYSIS ============\n");
        printf("1. Descriptive Statistics\n");
        printf("2. Correlation Analysis\n");
        printf("3. Linear Regression\n");
        printf("4. Hypothesis Testing (Info)\n");
        printf("5. Confidence Intervals (Info)\n");
        printf("6. Back to Main Menu\n");
        printf("==============================================\n");
        printf("Enter your choice: ");

        if(scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number.\n");
            while(getchar() != '\n');
            wait_for_input();
            continue;
        }

        switch(choice) {
            case 1: {
                if(dataset_count == 0) {
                    printf("\nNo datasets available! Please add data first.\n");
                    break;
                }

                printf("\nSelect dataset for analysis:\n");
                for(int i = 0; i < dataset_count; i++) {
                    printf("%d. %s (%d points)\n", i + 1, datasets[i].variable_name, datasets[i].count);
                }

                int selection;
                printf("Enter choice: ");
                if(scanf("%d", &selection) != 1) {
                    printf("Invalid input!\n");
                    while(getchar() != '\n');
                    break;
                }

                if(selection > 0 && selection <= dataset_count) {
                    Statistics stats = calculate_descriptive_stats(&datasets[selection - 1]);
                    print_statistics(stats, datasets[selection - 1].variable_name);
                } else {
                    printf("Invalid selection! Please choose between 1 and %d.\n", dataset_count);
                }
                break;
            }
            case 2:
                correlation_analysis();
                break;
            case 3:
                regression_analysis();
                break;
            case 4:
                hypothesis_testing();
                break;
            case 5:
                confidence_intervals();
                break;
            case 6:
                return;
            default:
                printf("Invalid choice! Please enter 1-6.\n");
        }

        if(choice != 6) {
            wait_for_input();
        }

    } while(choice != 6);
}

Statistics calculate_descriptive_stats(Dataset *dataset) {
    Statistics stats = {0};
    double sum = 0;
    double sorted_data[MAX_DATA_POINTS];

    if(dataset->count == 0) {
        return stats; // Return zero-initialized stats
    }

    // Copy data for sorting
    for(int i = 0; i < dataset->count; i++) {
        sorted_data[i] = dataset->data[i];
        sum += dataset->data[i];
    }

    // Sort data for median and quartiles
    sort_array(sorted_data, dataset->count);

    // Basic statistics
    stats.mean = sum / dataset->count;
    stats.min = sorted_data[0];
    stats.max = sorted_data[dataset->count - 1];
    stats.range = stats.max - stats.min;

    // Median
    int n = dataset->count;
    stats.median = median_of_range(sorted_data, 0, n - 1);
    stats.q2 = stats.median;

    // Quartiles (median of lower and upper halves)
    if(n >= 2) {
        if(n % 2 == 0) {
            // lower half: 0 .. n/2 - 1, upper half: n/2 .. n-1
            stats.q1 = median_of_range(sorted_data, 0, n/2 - 1);
            stats.q3 = median_of_range(sorted_data, n/2, n - 1);
        } else {
            // odd: lower half: 0 .. n/2 -1, upper half: n/2 +1 .. n-1
            stats.q1 = median_of_range(sorted_data, 0, n/2 - 1);
            stats.q3 = median_of_range(sorted_data, n/2 + 1, n - 1);
        }
    } else {
        stats.q1 = stats.min;
        stats.q3 = stats.max;
    }
    stats.iqr = stats.q3 - stats.q1;

    // Variance and standard deviation (sample variance)
    double sum_sq = 0;
    for(int i = 0; i < dataset->count; i++) {
        double diff = dataset->data[i] - stats.mean;
        sum_sq += diff * diff;
    }

    if(dataset->count > 1) {
        stats.variance = sum_sq / (dataset->count - 1); // Sample variance
        stats.std_deviation = sqrt(stats.variance);
    } else {
        stats.variance = 0;
        stats.std_deviation = 0;
    }

    // Mode (simple: find most frequent grouped value within epsilon)
    double eps = 1e-6;
    double best_val = sorted_data[0];
    int best_count = 1;
    int i = 0;
    while(i < n) {
        int j = i + 1;
        while(j < n && fabs(sorted_data[j] - sorted_data[i]) <= eps) j++;
        int cnt = j - i;
        if(cnt > best_count) {
            best_count = cnt;
            best_val = sorted_data[i];
        }
        i = j;
    }
    // If all counts are 1, we can set mode to NaN to indicate no repeated mode
    if(best_count <= 1) stats.mode = NAN;
    else stats.mode = best_val;

    return stats;
}

void correlation_analysis() {
    if(dataset_count < 2) {
        printf("\nNeed at least 2 datasets for correlation analysis!\n");
        printf("Current datasets: %d\n", dataset_count);
        return;
    }

    printf("\n============ CORRELATION ANALYSIS ============\n");
    printf("Available datasets:\n");
    for(int i = 0; i < dataset_count; i++) {
        printf("%d. %s (%d points)\n", i + 1, datasets[i].variable_name, datasets[i].count);
    }

    int x_idx, y_idx;
    printf("\nSelect first dataset: ");
    if(scanf("%d", &x_idx) != 1) {
        printf("Invalid input!\n");
        while(getchar() != '\n');
        return;
    }
    printf("Select second dataset: ");
    if(scanf("%d", &y_idx) != 1) {
        printf("Invalid input!\n");
        while(getchar() != '\n');
        return;
    }

    x_idx--; y_idx--;

    if(x_idx < 0 || x_idx >= dataset_count || y_idx < 0 || y_idx >= dataset_count) {
        printf("Invalid selection! Please choose valid dataset numbers.\n");
        return;
    }

    if(x_idx == y_idx) {
        printf("Please select two different datasets.\n");
        return;
    }

    int min_count = (datasets[x_idx].count < datasets[y_idx].count) ?
                    datasets[x_idx].count : datasets[y_idx].count;

    if(min_count == 0) {
        printf("One or both datasets are empty!\n");
        return;
    }

    double correlation = calculate_correlation(datasets[x_idx].data, datasets[y_idx].data, min_count);

    printf("\n========== CORRELATION RESULTS ==========\n");
    printf("Variables: %s vs %s\n", datasets[x_idx].variable_name, datasets[y_idx].variable_name);
    printf("Sample size used: %d points\n", min_count);
    printf("Correlation coefficient (r): %.4f\n", correlation);
    printf("Coefficient of determination (r²): %.4f\n", correlation * correlation);

    if(fabs(correlation) > 0.8) {
        printf("Interpretation: Strong correlation\n");
    } else if(fabs(correlation) > 0.5) {
        printf("Interpretation: Moderate correlation\n");
    } else {
        printf("Interpretation: Weak correlation\n");
    }

    if(correlation > 0) {
        printf("Direction: Positive correlation\n");
    } else if(correlation < 0) {
        printf("Direction: Negative correlation\n");
    } else {
        printf("Direction: No linear correlation\n");
    }
}

void regression_analysis() {
    if(dataset_count < 2) {
        printf("\nNeed at least 2 datasets for regression analysis!\n");
        return;
    }

    printf("\n========== LINEAR REGRESSION ANALYSIS ==========\n");
    printf("Available datasets:\n");
    for(int i = 0; i < dataset_count; i++) {
        printf("%d. %s (%d points)\n", i + 1, datasets[i].variable_name, datasets[i].count);
    }

    int x_idx, y_idx;
    printf("\nSelect independent variable (X): ");
    if(scanf("%d", &x_idx) != 1) {
        printf("Invalid input!\n");
        while(getchar() != '\n');
        return;
    }
    printf("Select dependent variable (Y): ");
    if(scanf("%d", &y_idx) != 1) {
        printf("Invalid input!\n");
        while(getchar() != '\n');
        return;
    }

    x_idx--; y_idx--;

    if(x_idx < 0 || x_idx >= dataset_count || y_idx < 0 || y_idx >= dataset_count) {
        printf("Invalid selection!\n");
        return;
    }

    int n = (datasets[x_idx].count < datasets[y_idx].count) ?
            datasets[x_idx].count : datasets[y_idx].count;

    if(n < 2) {
        printf("Need at least 2 data points for regression!\n");
        return;
    }

    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    for(int i = 0; i < n; i++) {
        double x = datasets[x_idx].data[i];
        double y = datasets[y_idx].data[i];
        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_x2 += x * x;
    }

    double denominator = n * sum_x2 - sum_x * sum_x;
    if(fabs(denominator) < 1e-10) {
        printf("Cannot compute regression: X values are too similar (no variance).\n");
        return;
    }

    double slope = (n * sum_xy - sum_x * sum_y) / denominator;
    double intercept = (sum_y - slope * sum_x) / n;
    double correlation = calculate_correlation(datasets[x_idx].data, datasets[y_idx].data, n);

    printf("\n========== REGRESSION RESULTS ==========\n");
    printf("Regression Equation: Y = %.4f + %.4f * X\n", intercept, slope);
    printf("Slope: %.4f\n", slope);
    printf("Y-Intercept: %.4f\n", intercept);
    printf("Correlation coefficient: %.4f\n", correlation);
    printf("R-squared: %.4f\n", correlation * correlation);
    printf("Sample size: %d points\n", n);

    printf("\nPrediction example:\n");
    printf("Enter X value for prediction: ");
    double x_predict;
    if(scanf("%lf", &x_predict) == 1) {
        double y_predict = intercept + slope * x_predict;
        printf("Predicted Y value: %.4f\n", y_predict);
    } else {
        printf("Invalid input for prediction!\n");
        while(getchar() != '\n');
    }
}

void visualization_menu() {
    if(dataset_count == 0) {
        printf("\nNo datasets available for visualization!\n");
        printf("Please add some data first.\n");
        return;
    }

    printf("\n========== DATA VISUALIZATION ==========\n");
    printf("Select dataset to visualize:\n");
    for(int i = 0; i < dataset_count; i++) {
        printf("%d. %s (%d points)\n", i + 1, datasets[i].variable_name, datasets[i].count);
    }

    int selection;
    printf("Enter choice: ");
    if(scanf("%d", &selection) != 1) {
        printf("Invalid input!\n");
        while(getchar() != '\n');
        return;
    }
    selection--;

    if(selection < 0 || selection >= dataset_count) {
        printf("Invalid selection!\n");
        return;
    }

    Dataset *data = &datasets[selection];

    if(data->count == 0) {
        printf("Selected dataset is empty!\n");
        return;
    }

    printf("\n======== HISTOGRAM FOR %s ========\n", data->variable_name);

    // Find min and max values
    double min_val = data->data[0], max_val = data->data[0];
    for(int i = 1; i < data->count; i++) {
        if(data->data[i] < min_val) min_val = data->data[i];
        if(data->data[i] > max_val) max_val = data->data[i];
    }

    if(fabs(max_val - min_val) < 1e-10) {
        printf("All values are the same (%.4f). Cannot create histogram.\n", min_val);
        return;
    }

    int bins = 10;
    int histogram[10] = {0};
    double bin_width = (max_val - min_val) / bins;

    // Count data points in each bin
    for(int i = 0; i < data->count; i++) {
        int bin_index = (int)((data->data[i] - min_val) / bin_width);
        if(bin_index >= bins) bin_index = bins - 1;
        if(bin_index < 0) bin_index = 0;
        histogram[bin_index]++;
    }

    // Display histogram
    for(int i = 0; i < bins; i++) {
        printf("%.2f-%.2f: ", min_val + i * bin_width, min_val + (i + 1) * bin_width);
        for(int j = 0; j < histogram[i] && j < 50; j++) {
            printf("*");
        }
        if(histogram[i] > 50) printf("...");
        printf(" (%d)\n", histogram[i]);
    }

    printf("\nTotal data points: %d\n", data->count);
    printf("Range: %.4f to %.4f\n", min_val, max_val);
}

void machine_learning_menu() {
    printf("\n======== MACHINE LEARNING BASICS ========\n");
    printf("This section demonstrates basic ML concepts:\n\n");
    printf("1. DATA PREPROCESSING:\n");
    printf("   - Data cleaning and validation\n");
    printf("   - Normalization and standardization\n");
    printf("   - Feature scaling\n\n");
    printf("2. DESCRIPTIVE ANALYTICS:\n");
    printf("   - Statistical summaries\n");
    printf("   - Distribution analysis\n");
    printf("   - Outlier detection\n\n");
    printf("3. PREDICTIVE MODELING:\n");
    printf("   - Linear regression implementation\n");
    printf("   - Correlation analysis\n");
    printf("   - Simple prediction algorithms\n\n");
    printf("Note: This system demonstrates the mathematical\n");
    printf("foundations of data science and machine learning.\n");
    printf("Advanced ML requires specialized libraries like\n");
    printf("scikit-learn, TensorFlow, or PyTorch.\n");
}

void data_export_menu() {
    if(dataset_count == 0) {
        printf("\nNo data to export! Please add some datasets first.\n");
        return;
    }

    char filename[100];
    printf("\nEnter filename for export (without extension): ");
    if(scanf("%99s", filename) != 1) {
        printf("Error reading filename!\n");
        while(getchar() != '\n');
        return;
    }

    char full_filename[110];
    sprintf(full_filename, "%s.csv", filename);

    FILE *file = fopen(full_filename, "w");
    if(file == NULL) {
        printf("Error creating export file '%s'!\n", full_filename);
        return;
    }

    fprintf(file, "Dataset,Count,Mean,Median,Mode,Std_Dev,Min,Max,Range\n");

    for(int i = 0; i < dataset_count; i++) {
        Statistics stats = calculate_descriptive_stats(&datasets[i]);
        if(isnan(stats.mode)) {
            fprintf(file, "%s,%d,%.4f,%.4f,,%.4f,%.4f,%.4f,%.4f\n",
                    datasets[i].variable_name, datasets[i].count,
                    stats.mean, stats.median, stats.std_deviation,
                    stats.min, stats.max, stats.range);
        } else {
            fprintf(file, "%s,%d,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f\n",
                    datasets[i].variable_name, datasets[i].count,
                    stats.mean, stats.median, stats.mode, stats.std_deviation,
                    stats.min, stats.max, stats.range);
        }
    }

    fclose(file);
    printf("\nStatistical summary exported to '%s' successfully!\n", full_filename);
    printf("Data includes: Dataset name, count, mean, median, mode (if any), std deviation, min, max, range\n");
}

// Utility functions
void sort_array(double arr[], int n) {
    // Simple bubble sort
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

double calculate_correlation(double x[], double y[], int n) {
    if(n < 2) return 0.0;

    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0, sum_y2 = 0;

    for(int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
        sum_y2 += y[i] * y[i];
    }

    double numerator = n * sum_xy - sum_x * sum_y;
    double denominator = sqrt((n * sum_x2 - sum_x * sum_x) * (n * sum_y2 - sum_y * sum_y));

    return (fabs(denominator) > 1e-10) ? numerator / denominator : 0.0;
}

void print_statistics(Statistics stats, char *variable_name) {
    printf("\n========== DESCRIPTIVE STATISTICS ==========\n");
    printf("Variable: %s\n", variable_name);
    printf("─────────────────────────────────────────────\n");
    printf("Mean:                 %.4f\n", stats.mean);
    printf("Median:               %.4f\n", stats.median);
    if(!isnan(stats.mode)) printf("Mode:                 %.4f\n", stats.mode);
    else printf("Mode:                 (no repeated value)\n");
    printf("Standard Deviation:   %.4f\n", stats.std_deviation);
    printf("Variance:             %.4f\n", stats.variance);
    printf("Minimum:              %.4f\n", stats.min);
    printf("Maximum:              %.4f\n", stats.max);
    printf("Range:                %.4f\n", stats.range);
    printf("First Quartile (Q1):  %.4f\n", stats.q1);
    printf("Third Quartile (Q3):  %.4f\n", stats.q3);
    printf("Interquartile Range:  %.4f\n", stats.iqr);
    printf("═════════════════════════════════════════════\n");
}

void clear_screen() {
    // Cross-platform screen clearing
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void wait_for_input() {
    // Flush any leftover input first
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    printf("\nPress Enter to continue...");
    // Wait for the user to press Enter
    char buf[4];
    if(fgets(buf, sizeof(buf), stdin) == NULL) {
        // nothing — ignore
    }
}

void hypothesis_testing() {
    printf("\n======== HYPOTHESIS TESTING INFO ========\n");
    printf("Common hypothesis tests and their applications:\n\n");
    printf("1. ONE-SAMPLE T-TEST:\n");
    printf("   - Tests if sample mean differs from population mean\n");
    printf("   - Formula: t = (x̄ - μ) / (s / √n)\n");
    printf("   - Use when: Testing single group against known value\n\n");
    printf("2. TWO-SAMPLE T-TEST:\n");
    printf("   - Compares means of two independent groups\n");
    printf("   - Formula: t = (x̄₁ - x̄₂) / √(s₁²/n₁ + s₂²/n₂)\n");
    printf("   - Use when: Comparing two groups\n\n");
    printf("3. CHI-SQUARE TEST:\n");
    printf("   - Tests independence between categorical variables\n");
    printf("   - Formula: χ² = Σ((O - E)² / E)\n");
    printf("   - Use when: Testing categorical relationships\n\n");
    printf("4. ANOVA (Analysis of Variance):\n");
    printf("   - Compares means across multiple groups\n");
    printf("   - F-statistic = MSB / MSW\n");
    printf("   - Use when: Comparing 3+ groups\n\n");
    printf("Note: Full implementation requires critical value tables\n");
    printf("and degrees of freedom calculations.\n");
}

void confidence_intervals() {
    printf("\n======== CONFIDENCE INTERVALS INFO ========\n");
    printf("Confidence intervals provide range estimates for parameters:\n\n");
    printf("1. CONFIDENCE INTERVAL FOR MEAN:\n");
    printf("   - Formula: x̄ ± t(α/2) * (s / √n)\n");
    printf("   - Where t(α/2) is critical t-value\n");
    printf("   - Common levels: 90%, 95%, 99%\n\n");
    printf("2. CONFIDENCE INTERVAL FOR PROPORTION:\n");
    printf("   - Formula: p̂ ± z(α/2) * √(p̂(1-p̂)/n)\n");
    printf("   - Where p̂ is sample proportion\n");
    printf("   - Use normal approximation when np ≥ 5\n\n");
    printf("3. INTERPRETATION:\n");
    printf("   - 95% CI: 95% of such intervals contain true parameter\n");
    printf("   - Wider intervals = more confidence, less precision\n");
    printf("   - Larger samples = narrower intervals\n\n");
    printf("Example calculation would require:\n");
    printf("- Sample data from current datasets\n");
    printf("- t-distribution critical values\n");
    printf("- Specified confidence level\n");
}

// Helper: median of arr[start..end] inclusive (assumes arr sorted)
double median_of_range(double arr[], int start, int end) {
    int len = end - start + 1;
    if(len <= 0) return 0.0;
    int mid = start + len/2;
    if(len % 2 == 0) {
        return (arr[mid - 1] + arr[mid]) / 2.0;
    } else {
        return arr[mid];
    }
}
