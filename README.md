# Data Analysis & Statistics System in C

A console-based **Data Analysis & Statistics System** implemented in **C**. This single-file program provides a menu-driven interface for loading or entering datasets, performing descriptive statistics, correlation and linear regression, simple ASCII visualizations (histogram), and exporting statistical summaries to CSV.

---

## 🔎 What this program does

* Add datasets manually or load from a whitespace/newline-separated numeric file.
* Generate sample datasets (normal, uniform, exponential).
* Display stored datasets and first 10 values.
* Compute descriptive statistics: mean, median, mode (if present), variance, standard deviation, min/max, range, Q1/Q3, IQR.
* Perform correlation analysis between two datasets (Pearson r) and interpret strength/direction.
* Perform simple linear regression (least squares), show equation, R² and example prediction.
* Draw simple ASCII histograms for a selected dataset.
* Export a CSV summary (`<name>.csv`) containing dataset name, count, mean, median, mode (if any), std dev, min, max, range.

---

## 📂 Project structure

```
├── main.c           # Complete program (menus, stats, I/O, visualization)
├── data/            # (optional) place to store dataset files you load
└── README.md        # This file
```

> Note: The program is provided as a single `main.c` file (no additional modules required).

---

## 🛠 Requirements

* **Compiler:** GCC or Clang
* **OS:** Linux, macOS, or Windows (cross-platform clearing and IO handled)
* Standard C library (math.h, stdio.h, stdlib.h, string.h, time.h)

---

## 🚀 Build & Run

Compile with GCC:

```bash
gcc main.c -o data_tool -lm
```

Run:

```bash
./data_tool
```

On Windows use `data_tool.exe`.

---

## 📥 Data file format (for `Load Data from File`)

* Simple text file containing numeric values separated by whitespace or newlines. Example:

```
12.5 15.0 9.8
20.1
7.3 8.2
```

* The loaded dataset will be named after the filename (truncated to the max name length).
* Up to 1000 data points per dataset; up to 10 datasets in memory.

---

## ⚠️ Limitations & Notes

* Mode detection treats values equal within `1e-6` as identical; if all values are unique the mode is reported as absent.
* Variance uses *sample variance* (dividing by n-1).
* Regression and correlation use the overlapping prefix of two datasets (length = min(count_x, count_y)).
* Histogram uses 10 bins and prints up to 50 `*` per bin (extras shown as `...`).
* No advanced statistical tests are implemented (hypothesis testing and CIs are informational only).

---

## 🤝 Contributing

If you want improvements, consider:

* Adding file-based dataset management (save/load named tables).
* Implementing additional visualizations (boxplot) or exporting charts as images (requires external libraries).
* Implementing formal hypothesis tests and confidence-interval calculators.

---

## 📄 License

No license is included in this repository (per project preference). If you want one added later, tell me which license.


